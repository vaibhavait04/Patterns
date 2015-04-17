// Purpose.  Composite, Builder, Iterator, Memento, Visitor demo
//
// Discussion.  Composite is a fairly fundamental pattern - it uses, or is
// used by, many other patterns.  Iterator can be used to traverse a
// Composite [GOF, p173].  Visitor can be used to apply an operation over
// an object structure defined by Composite [GOF, p344].  Builder often
// builds a Composite [GOF, p106].  Iterator can use Memento to capture
// the state of an iteration [GOF, p271].
//
// Input (composit.dat):
//    a 1 2 b 6 d 13 14 15 d 7 8 b 3 4 5 c 9 10 11
//    e 16 17 g 20 g 18 e 12 f 19 f c a
//
// In-memory structures:
//    a:   1   2  ^b   3   4   5  ^c
//    b:   6  ^d   7   8   
//    c:   9  10  11  ^e  12  ^f
//    d:  13  14  15                   
//    e:  16  17  ^g  18
//    f:  19
//    g:  20
//
// Output:
//    1 2 6 13 14 15 7 8 3 4 5 9 10 11 16 17 20 18 12 19 
//    a 1 2 b 6 d 13 14 15 7 8 3 4 5 c 9 10 11 e 16 17 g 20 18 12 f 19 
//    composites = 7.  primitives = 20.  total value = 210.  average value = 10

#include <stdio.h>
#include <iostream.h>
#include <fstream.h>

class Composite;
class Primitive;

class Visitor {
public:
   virtual void visit( Composite* ) = 0;
   virtual void visit( Primitive* ) = 0;
};

class ListVisitor : public Visitor {
public:
   /* virtual */ void visit( Composite* );
   /* virtual */ void visit( Primitive* );
};

class TotalVisitor : public Visitor {
public:
   TotalVisitor() { totalComposites = totalPrimitives = totalValue = 0; }
   /* virtual */ void visit( Composite* c ) { totalComposites++; }
   /* virtual */ void visit( Primitive* );
   void reportTotals()  {
      cout << "composites = " << totalComposites
         << ".  primitives = " << totalPrimitives
         << ".  total value = " << totalValue 
         << ".  average value = " << totalValue / totalPrimitives << endl; }
private:
   int  totalComposites;
   int  totalPrimitives;
   int  totalValue;
};

class Iterator;

class Component {
public:
   enum ComponentType { PrimitiveT, CompositeT };
   virtual void traverse()         = 0;
   virtual void add( Component* )  { }
   virtual ComponentType getType() = 0;
   virtual void accept( Visitor& ) = 0;
};

class Primitive : public Component {
public:
   Primitive( int _value )                 { value_ = _value; }
   void traverse()                         { cout << value_ << " "; }
   ComponentType getType()                 { return PrimitiveT; }
   int getValue()                          { return value_; }
   /* virtual */ void accept( Visitor& v ) { v.visit( this ); }
private:
   int    value_;
};

class Composite : public Component {
public:
   friend Iterator;
   Composite( char _name )                 { name_ = _name;  index_ = 0; }
   void add( Component* ele )              { children_[index_++] = ele; }
   ComponentType getType()                 { return CompositeT; }
   void printName()                        { cout << name_ << " "; }
   /* virtual */ void accept( Visitor& v ) { v.visit( this ); }
   void traverse();
   Iterator*  createIterator();
private:
   char        name_;
   int         index_;
   Component*  children_[99];
};

void Composite::traverse() {
   for (int i=0; i < index_; i++)
      children_[i]->traverse(); }

/* virtual */ void ListVisitor::visit( Composite* c ) { c->printName(); }
/* virtual */ void ListVisitor::visit( Primitive* p ) { p->traverse(); }
/* virtual */ void TotalVisitor::visit( Primitive* p ) {
   totalPrimitives++;
   totalValue += p->getValue(); }

class Memento {
public:
   void initialize( Composite* _root ) {
      compArr_[0] = _root;
      indxArr_[0] = -1;
      index_ = 0; }
   void pushCurrent( Composite* _composite, int _index ) {
      compArr_[index_+1] = _composite;
      indxArr_[++index_] = _index; }
   int popCurrent() {
      if (index_ == 0) return 1;
      index_--;
      return 0; }
   void getAndIncrement( Composite** _composite, int* _index ) {
      *_composite = compArr_[index_];
      *_index = indxArr_[index_];
      (*_index)++;
      indxArr_[index_]++; }
private:
   Composite*  compArr_[10];
   int         indxArr_[10];
   int         index_;
};

class Iterator {
public:
   Iterator( Composite* _root ) {
      root_ = _root;
      isDone_= 0; }
   Component* first() {
      isDone_= 0;
      memento_.initialize( root_ );
      return root_; }
   Component* next() {
      Composite* comp;
      int        indx;
      memento_.getAndIncrement( &comp, &indx );
      // if (and while) you are at end-of-composite, go back up
      while (indx == comp->index_)
      {
         int ret = memento_.popCurrent();
         if (ret) {
            isDone_ = 1;
            return 0; }
         memento_.getAndIncrement( &comp, &indx );
      }
      if (comp->children_[indx]->getType() == Component::CompositeT)
         memento_.pushCurrent( (Composite*) comp->children_[indx], -1 );
      return comp->children_[indx]; }
   int isDone() { return isDone_; }
private:
   Composite*  root_;
   Memento     memento_;
   int         isDone_;
};

Iterator*  Composite::createIterator() {
   return new Iterator( this ); }

class Builder;

class Reader {
public:
   Reader( Builder* _builder ) {
      builder_ = _builder;
      nextSlot_ = 0; }
   void construct();
private:
   Builder*  builder_;
   char      compNames_[20];
   int       nextSlot_;
   int isLower_( char ch ) {
      if ((ch >= 'a') && (ch <= 'z')) return 1;
      else return 0; }
   int findName_( char ch ) {
      for (int i=0; i < nextSlot_; i++)
         if (compNames_[i] == ch) return 1;
      compNames_[nextSlot_++] = ch;
      return 0; }
};

class Builder {
public:
   /**/ Builder()         { nextSlot_ = 0; }
   void buildComposite( char _name ) {
      // cout << _name << " at level " << nextSlot_ << endl;
      stack_[nextSlot_] = new Composite( _name );
      if (nextSlot_)
         stack_[nextSlot_ - 1]->add( stack_[nextSlot_] );
      nextSlot_++; }
   void buildPrimitive( int _value ) {
      stack_[nextSlot_ - 1]->add( new Primitive( _value ) ); }
   void closeComposite()  { nextSlot_--; }
   Composite* getResult() { return stack_[0]; }
private:
   Composite* stack_[20];
   int        nextSlot_;
};

void Reader::construct() {
   char      buf[20];
   int       value;
   ifstream  inFile( "composit.dat", ios::in );

   while ( inFile >> buf )
   {
      if (isLower_( buf[0] ))
         if (findName_( buf[0] ))
            builder_->closeComposite();
         else
            builder_->buildComposite( buf[0] );
      else
      {
         sscanf( buf, "%d", &value );
         builder_->buildPrimitive( value );
      }
   }
}

void main( void ) {
   Builder       builder;
   Reader        reader( &builder );
   Composite*    root;
   Iterator*     it;
   ListVisitor   listV;
   TotalVisitor  totalV;

   reader.construct();
   root = builder.getResult();

   // Composite can traverse itself, but Composite nodes get "lost"
   root->traverse();   cout << endl;

   // If you don't want Composite nodes "lost", use an Iterator for traversal
   it = root->createIterator();
   for (Component* c = it->first(); ! it->isDone(); c = it->next())
      c->accept( listV );
   cout << endl;

   // Visitors can be designed to accumulate state over a Composite
   for (c = it->first(); ! it->isDone(); c = it->next())
      c->accept( totalV );
   totalV.reportTotals();
}

// ListVisitor replaces the following code:
// for (Component* c = it->first(); ! it->isDone(); c = it->next()) {
//    if (c->getType() == Component::PrimitiveT)
//       ((Primitive*) c)->traverse();
//    else
//       ((Composite*) c)->printName(); }


