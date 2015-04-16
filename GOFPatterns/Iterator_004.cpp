
// Purpose.  Simple implementation of an Iterator (uses parallel dynamic array)
//
// Discussion.  Instead of having to write an involved stack-like solution to
// handle step-wise recursive descent, use a little extra memory to maintain a
// sequential representation of the original hierarchical data.  The replicated
// data are not Node objects, they are lightweight pointers.  The array is
// initialized using a recursive method similar to traverse(Node*).

#include <iostream>
#include <ctime>
using namespace std;

class BST {
   friend class Iterator;
   struct Node {
      Node( int );
      int value;
      Node* left;
      Node* rite;
   };
   Node* root;
   int   size;
   void add( Node**, int );
   void traverse( Node* );
public:
   BST() { root = 0;  size = 0; }
   void add( int );
   void traverse();
   Iterator* createIterator() const;
};

class Iterator {
   const BST* tree;
   BST::Node** array;
   int index;
   void populateArray( BST::Node* current ) {
      if (current->left) populateArray( current->left );
      array[index++] = current;
      if (current->rite) populateArray( current->rite );
   }
public:
   Iterator( const BST* s ) {
      tree = s;
      array = 0;  index = 0;
   }
   ~Iterator() { delete [] array; }
   void first() {
      delete [] array;
      array = new BST::Node*[tree->size];
      index = 0;
      populateArray( tree->root );
      index = 0;
   }
   void next()              { index++; }
   bool isDone()            { return index == tree->size; }
   BST::Node* currentItem() { return array[index]; }
};

int main( void ) {
   srand( time( 0 ) );
   BST  tree;
   for (int i=0; i < 20; i++) tree.add( rand() % 20 + 1 );
   cout << "traverse: ";
   tree.traverse();
   cout << "\niterator: ";
   Iterator* it = tree.createIterator();
   for (it->first(); ! it->isDone(); it->next())
      cout << it->currentItem()->value << ' ';
   cout << "\niterator: ";
   for (it->first(); ! it->isDone(); it->next())
      cout << it->currentItem()->value << ' ';
   cout << '\n';
}

// traverse: 1 2 3 7 8 9 9 10 11 11 13 14 14 14 15 17 18 19 19 20
// iterator: 1 2 3 7 8 9 9 10 11 11 13 14 14 14 15 17 18 19 19 20
// iterator: 1 2 3 7 8 9 9 10 11 11 13 14 14 14 15 17 18 19 19 20

BST::Node::Node( int v ) { value = v;  left = rite = 0; }

void BST::add( Node** n, int v ) {
   if ( ! *n)                 { *n = new Node( v );  size++; }
   else if (v <= (*n)->value) add( &((*n)->left), v );
   else                       add( &((*n)->rite), v );
}

void BST::add( int v ) { add( &root, v ); }
void BST::traverse() { traverse( root ); }

void BST::traverse( Node* n ) {
   if (n->left) traverse( n->left );
   cout << n->value << ' ';
   if (n->rite) traverse( n->rite );
}

Iterator* BST::createIterator() const { return new Iterator( this ); }


