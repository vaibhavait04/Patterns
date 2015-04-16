#include <iostream>
using namespace std; 

class Node {
public:
   Node( int v ) { val_ = v; }
   int getVal()  { return val_; }
private:
   int  val_;
};

class List {
public:
   List() {
      for (int i=0; i < 10; i++)
         arr_[i] = 0;
         num_ = 0;
   }
   void addNode( Node* n ) {
      arr_[num_++] = n;
   }
   void traverse() {
      for (int i=0; i < num_; i++)
         cout << arr_[i]->getVal()
            << "  ";
      cout << endl;
   }
   void removeNode( int v ) {
      int  i, j;
      for (i=0; i < num_; i++)
         if (arr_[i]->getVal() == v)
         {
            for (j=i; j < num_; j++)
               arr_[j] = arr_[j+1];
            num_--;
            break;
         }
   }
private:
   Node*  arr_[10];
   int    num_;
};

int main( void )
{
   List  lst;
   Node  one( 11 ),  two( 22 );
   Node  thr( 33 ),  fou( 44 );
   lst.addNode( &one );
   lst.addNode( &two );
   lst.addNode( &thr );
   lst.addNode( &fou );
   lst.traverse();
   lst.removeNode( 44 );
   lst.traverse();
   lst.removeNode( 11 );
   lst.traverse();
}

// 11  22  33  44
// 11  22  33
// 22  33




