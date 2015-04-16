// Purpose.  Fairly reusable iterator for step-wise recursive descent
//
// Discussion.  The Composite/Component/Leaf code is one of the previous
// Composite demos.  Methods added were: Component::outputValue() and
// Composite::createIterator().

#include <iostream>
#include <vector>
using namespace std;

class Component { public:
   virtual void traverse() = 0;
   virtual void outputValue() { }
};

class Leaf : public Component {
   int value;
public:
   Leaf( int val ) { value = val; }
   /*virtual*/ void traverse() { cout << value << ' '; }
   /*virtual*/ void outputValue() { traverse(); }
};

class Composite : public Component {
   vector<Component*> children;
public:
   friend class Iterator;
   void add( Component* ele ) { children.push_back( ele ); }
   /*virtual*/ void traverse() {
      for (int i=0; i < children.size(); i++)
         children[i]->traverse();
   }
   Iterator* createIterator();
};

class Memento {
public:
   struct MgrIdx {
      MgrIdx( Composite* m=0, int i=0 ) { mgr = m;  idx = i; }
      Composite* mgr;
      int        idx;
   };
   void initialize( Composite* root ) {
      vec.resize( 0 );
      vec.push_back( MgrIdx( root, 0 ) );
   }
   bool isEmpty()         { return vec.size() == 0; }
   void push( MgrIdx ds ) { vec.push_back( ds ); }
   MgrIdx top()           { return vec.back(); }
   MgrIdx pop() {
      MgrIdx ds = vec.back();
      vec.pop_back();
      return ds;
   }
private:
   vector<MgrIdx> vec;
};

// Dependencies on actual class playing the role of "Composite":
//    Composite class name, children attribute name
class Iterator {
   Composite* root;
   Memento    memento;
   bool       done;
public:
   Iterator( Composite* rooot ) { root = rooot; }
   void first() {
      memento.initialize( root );
      done = false;
   }
   void next() {
      Memento::MgrIdx ds = memento.pop();
      ds.idx++;
      // if (and while) you are at end-of-composite, go up
      while (ds.idx == ds.mgr->children.size()) {
         if (memento.isEmpty()) { done = true;  return; }
         ds = memento.pop();
         ds.idx++;
      }
      memento.push( ds );
      Composite* compo;
      if (compo = dynamic_cast<Composite*>(ds.mgr->children[ds.idx]))
         memento.push( Memento::MgrIdx( compo, 0 ) );
   }
   Component* currentItem() {
      Memento::MgrIdx ds = memento.top();
      return ds.mgr->children[ds.idx];
   }
   bool isDone() { return done; }
};

Iterator* Composite::createIterator() { return new Iterator( this ); }

void main( void ) {
   Composite containers[4];
   for (int i=0; i < 4; i++)
      for (int j=0; j < 3; j++)
         containers[i].add( new Leaf( i * 3 + j ) );
   for (i=1; i < 4; i++) containers[0].add( &(containers[i]) );
   cout << "traverse: ";
   containers[0].traverse();

   Iterator* it = containers[0].createIterator();
   cout << "\niterator: ";
   for (it->first(); ! it->isDone(); it->next())
      it->currentItem()->outputValue();
   cout << '\n';
   cout << "iterator: ";
   for (it->first(); ! it->isDone(); it->next())
      it->currentItem()->outputValue();
   cout << '\n';
   delete it;
}

// traverse: 0 1 2 3 4 5 6 7 8 9 10 11
// iterator: 0 1 2 3 4 5 6 7 8 9 10 11
// iterator: 0 1 2 3 4 5 6 7 8 9 10 11


