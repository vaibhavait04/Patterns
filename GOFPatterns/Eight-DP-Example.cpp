// Purpose.  File system with 8 GoF patterns

// Composite --------------- directories that contain files, each of which could
//                           be a directory
// Proxy ------------------- Unix logical link
// Chain of Responsibility - pointer back to the parent directory to create
//                           "fully qualified path name"
// Iterator ---------------- use iterator to control the traversal of a Composite
// Visitor ----------------- create a recursive Unix "du" utility without
//                           modifying the original Composite hierarchy
// Observer ---------------- register one-to-many "listeners" for File write()
//                           events
// Command ----------------- register one-to-one callback object for File write()
//                           events
// Decorator --------------- create an optional Encryption wrapper

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

class AbsFile {
   string name;
   class Directory* parent;
protected:
   Directory* getParent() { return parent; }
public:
   AbsFile( string n, Directory* p ) : name( n ) { parent = p; }
   virtual ~AbsFile() { }
   virtual string getName() { return name; }
   virtual string getFullName();
   virtual void ls( string = "" ) = 0;
   virtual void populate( vector<AbsFile*>& list ) { list.push_back( this ); }
   virtual void write( string str ) { }
   virtual void streamOut( ostream& = cout ) = 0;
   virtual void accept( class Visitor& ) = 0;
};

class Observer {
public:
   virtual void fileChanged( class File* ) = 0;
};

class Command  {
public:
   virtual void execute( File* ) = 0;
};
class NullCommand : public Command {
public:
   static Command& inst() { static NullCommand nc; return nc; }
   /*virtual*/ void execute(File*) { }
};

class File : public AbsFile {
   stringstream contents;
   static vector<Observer*> observers;
   Command& cmd;
public:
   File( string n, Directory* p, Command& c = NullCommand::inst() )
      : AbsFile( n,p ), cmd( c ) { }
   ~File() { cout << 'X' << getName() << ' '; }
   /*virtual*/ void ls( string s = "" ) {
      if (s == "") cout << getName() << ' ';
      else         cout << getFullName() << '\n';
   }
   /*virtual*/ void write( string str ) {
      contents << str;
      notify();
      cmd.execute( this );
   }
   /*virtual*/ void streamOut( ostream& os = cout ) {
      os << contents.str() << '\n';
   }
   /*virtual*/ void accept( Visitor& v );
   /*virtual*/ int getSize() { return contents.str().size(); }
   static void registerObserver( class Observer* o ) { observers.push_back( o ); }
   void notify() {
      for (int i=0; i < observers.size(); i++)
         observers[i]->fileChanged( this );
   }
};
vector<Observer*> File::observers;

class Directory : public AbsFile {
   vector<AbsFile*> children;
   string name;
public:
   Directory( string n, Directory* p=0 ) : AbsFile( n,p ) { }
   ~Directory() {
      cout << 'X' << getName() << ' ';
      for (int i=0; i < children.size(); i++)
         delete children[i];
   }
   void add( AbsFile* ele ) { children.push_back( ele ); }
   /*virtual*/ void ls( string s = "" ) {
      if (s == "") cout << getName() << "/ ";
      else         cout << getFullName() << '\n';
      for (int i=0; i < children.size(); i++)
         children[i]->ls( s );
   }
   /*virtual*/ string getFullName() { return AbsFile::getFullName() + '/'; }
   class Iterator* createIterator();
   /*virtual*/ void populate( vector<AbsFile*>& list ) {
      AbsFile::populate( list );
      for (int i=0; i < children.size(); i++)
         children[i]->populate( list );
   }
   /*virtual*/ void streamOut( ostream& os = cout ) {
      os << "directory - " << getName() << '\n';
   }
   /*virtual*/ void accept( Visitor& v );
};

/*virtual*/ string AbsFile::getFullName() {
   string str;
   Directory* p;
   if (p = getParent()) str = p->getFullName();
   return str + getName();
}

class Link : public AbsFile {
   AbsFile* wrapped;
public:
   Link( string n, AbsFile* w, Directory* p ) : AbsFile(n,p) { wrapped = w; }
   ~Link() { cout << 'X' << getName() << ' '; }
   /*virtual*/ void ls( string s = "" ) {
      if (s == "") {
         cout << getName() << "* ";
         wrapped->ls();
      } else {
         cout << getFullName() << " => ";
         cout << wrapped->getFullName() << '\n';
   }  }
   /*virtual*/ string getFullName() { return AbsFile::getFullName() + '*'; }
   /*virtual*/ void streamOut( ostream& os = cout ) {
      os << "link - " << getName() << '\n';
   }
   /*virtual*/ void accept( Visitor& v );
};

class Iterator {
   Directory* container;
   vector<AbsFile*> list;
   int index;
public:
   Iterator( Directory* c ) { container = c; }
   void first() {
      list.resize( 0 );
      container->populate( list );
      index = 0;
   }
   void     next()        { index++; }
   bool     isDone()      { return index == list.size(); }
   AbsFile* currentItem() { return list[index]; }
};

Iterator* Directory::createIterator() { return new Iterator( this ); }

class Visitor { public:
   virtual void visit( File*      ) = 0;
   virtual void visit( Directory* ) = 0;
   virtual void visit( Link*      ) = 0;
   virtual void visit( class Decorator* ) = 0;
};

/*virtual*/ void File::accept(      Visitor& v ) { v.visit( this ); }
/*virtual*/ void Directory::accept( Visitor& v ) { v.visit( this ); }
/*virtual*/ void Link::accept(      Visitor& v ) { v.visit( this ); }

class DU : public Visitor {
   int numDir, numLink, numFile, numDeco, sizeFile;
public:
   DU() { numDir = numLink = numFile = numDeco = sizeFile = 0; }
   /*virtual*/ void visit( class File* f )    { numFile++;
                                                sizeFile += f->getSize(); }
   /*virtual*/ void visit( class Directory* ) { numDir++; }
   /*virtual*/ void visit( class Link* )      { numLink++; }
   /*virtual*/ void visit( class Decorator* ) { numDeco++; }
   void report() {
      cout << "du: directories-" << numDir << ", links-" << numLink;
      cout << ", files-" << numFile << ", decorators-" << numDeco;
      cout << ", size-" << sizeFile << '\n';
}  };

class NameObserver : public Observer {
public:
   /*virtual*/ void fileChanged( File* f ) {
      time_t  t;
      time( &t );
      string str( asctime(localtime(&t)) );
      str.resize( str.size()-1 );
      cout << f->getName() << " changed - " << str << '\n';
}  };

class ContentObserver : public Observer {
public:
   /*virtual*/ void fileChanged( File* f ) {
      stringstream ss;
      f->streamOut( ss );
      cout << f->getName() << " content - " << ss.str();
}  };

class ContentCommand : public Command {
public:
   static Command& inst() { static ContentCommand cc; return cc; }
   /*virtual*/ void execute( File* f ) {
      stringstream ss;
      f->streamOut( ss );
      cout << "ContentCommand - " << f->getName() << " - " << ss.str();
}  };

class Decorator : public AbsFile {
   File* wrapped;
public:
   Decorator( File* w )   : AbsFile("",0)      { wrapped = w; }
   ~Decorator() {
      cout << 'X' << "deco" << ' ';
      delete wrapped;
   }
   /*virtual*/ string getName()                { return wrapped->getName(); }
   /*virtual*/ string getFullName()            { return wrapped->getFullName(); }
   /*virtual*/ void   ls( string s = "" )      { wrapped->ls( s ); }
   /*virtual*/ void   write( string str )      { wrapped->write( str ); }
   /*virtual*/ void   streamOut( ostream& os = cout ) { wrapped->streamOut( os ); }
   /*virtual*/ int    getSize()                       { return wrapped->getSize(); }
   /*virtual*/ void   accept( Visitor& v ) {
      wrapped->accept( v );
      v.visit( this );
}  };

class EncryptionDecorator : public Decorator {
public:
   EncryptionDecorator( File* w )
      : Decorator(w) { }
   /*virtual*/ void write( string str ) {
      char temp;
      for (int i=0, j=str.size()-1; i < str.size() / 2; i++) {
         temp = str[i];  str[i] = str[j-i];  str[j-i] = temp; }
      Decorator::write( str );
}  };

Directory* initialize() {
   Directory* root = new Directory( "root" );
   root->add( new File( "core", root, ContentCommand::inst() ) );
   Directory* usr = new Directory( "usr", root );
   root->add( usr );
   File* adm = new File( "adm", usr );
   usr->add( new EncryptionDecorator( adm ) );
   Directory* local = new Directory( "local", usr );
   usr->add( local );
   local->add( new File( "bin", local ) );
   usr->add( new File( "var", usr ) );
   Directory* home = new Directory( "home", root );
   root->add( home );
   home->add( new Link( "alias", adm, home ) );
   home->add( new EncryptionDecorator(
      new File( "sam", home, ContentCommand::inst() ) ) );
   home->add( new File( "sue", home ) );
   root->add( new Link( "aka", local, root ) );
   root->add( new File( "end", root ) );
   return root;
}

void main( void ) {
   ////////// Composite, Proxy //////////
   Directory* root = initialize();
   root->ls();        cout << '\n';

   ////////// Chain //////////
   root->ls( "-l" );  cout << '\n';

   ////////// Iterator //////////
   Iterator* it = root->createIterator();
   for (it->first(); ! it->isDone(); it->next())
      cout << it->currentItem()->getName() << ' ';
   delete it;         cout << "\n\n";
   it = root->createIterator();
   for (it->first(); ! it->isDone(); it->next())
      cout << it->currentItem()->getFullName() << '\n';
   delete it;         cout << '\n';

   ////////// Observer //////////
   File::registerObserver( new NameObserver() );
   File::registerObserver( new ContentObserver() );

   ////////// Observer, Command //////////
   it = root->createIterator();
   for (it->first(); ! it->isDone(); it->next())
      if (it->currentItem()->getName() == "core")
         break;
   it->currentItem()->write( "0123456789" );
   it->currentItem()->streamOut();    cout << '\n';

   ////////// Observer, Decorator //////////
   for ( ; ! it->isDone(); it->next())
      if (it->currentItem()->getName() == "adm")
         break;
   it->currentItem()->write( "adm line 1\nadm line 2" );
   it->currentItem()->streamOut();   cout << '\n';

   ////////// Observer, Command, Decorator //////////
   for ( ; ! it->isDone(); it->next())
      if (it->currentItem()->getName() == "sam")
         break;
   it->currentItem()->write( "sam single line" );
   it->currentItem()->streamOut();
   delete it;         cout << '\n';

   ////////// Visitor //////////
   DU duObject;
   it = root->createIterator();
   for (it->first(); ! it->isDone(); it->next())
      it->currentItem()->accept( duObject );
   duObject.report();
   delete it;         cout << '\n';

   delete root;       cout << '\n';
}

// root/ core usr/ adm local/ bin var home/ alias* adm sam sue aka* local/ bin end
//
// root/
// root/core
// root/usr/
// root/usr/adm
// root/usr/local/
// root/usr/local/bin
// root/usr/var
// root/home/
// root/home/alias* => root/usr/adm
// root/home/sam
// root/home/sue
// root/aka* => root/usr/local/
// root/end
//
// root core usr adm local bin var home alias sam sue aka end
//
// root/
// root/core
// root/usr/
// root/usr/adm
// root/usr/local/
// root/usr/local/bin
// root/usr/var
// root/home/
// root/home/alias*
// root/home/sam
// root/home/sue
// root/aka*
// root/end
//
// core changed - Thu Dec 28 13:26:05 2000
// core content - 0123456789
// ContentCommand - core - 0123456789
// 0123456789
//
// adm changed - Thu Dec 28 13:26:05 2000
// adm content - 2 enil mda
// 1 enil mda
// 2 enil mda
// 1 enil mda
//
// sam changed - Thu Dec 28 13:26:05 2000
// sam content - enil elgnis mas
// ContentCommand - sam - enil elgnis mas
// enil elgnis mas
//
// du: directories-4, links-2, files-7, decorators-2, size-46
//
// Xroot Xcore Xusr Xdeco Xadm Xlocal Xbin Xvar Xhome Xalias Xdeco Xsam Xsue
//   Xaka Xend


