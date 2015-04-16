
// Purpose.  Iterator using operators instead of methods
//
// Discussion.  John Lakos suggests the GOF and STL iterator interfaces are:
// error-prone (possibility of misspelling method names), clumsy, and require
// too much typing.  This design uses nothing but "intuitive" operators.
// Notice also that no createIterator() was specified.  The user creates these
// iterators as local variables, and no clean-up is necessary.

#include <iostream>
using namespace std;

class Stack {
   int items[10];
   int sp;
public:
   friend class StackIter;
   Stack()             { sp = -1; }
   void push( int in ) { items[++sp] = in; }
   int  pop()          { return items[sp--]; }
   bool isEmpty()      { return (sp == -1); }
};

class StackIter {
   const Stack& stk;
   int index;
public:
   StackIter( const Stack& s ) : stk( s ) { index = 0; }
   void operator++() { index++; }
   bool operator()() { return index != stk.sp+1; }
   int  operator*()  { return stk.items[index]; }
};

bool operator==( const Stack& l, const Stack& r ) {
   StackIter itl( l ), itr( r );
   for ( ; itl(); ++itl, ++itr)
      if (*itl != *itr) break;
   return ! itl() && ! itr();
}

int main( void ) {
   Stack  s1;   int  i;
   for (i=1; i < 5; i++) s1.push(i);
   Stack  s2( s1 ), s3( s1 ), s4( s1 ), s5( s1 );
   s3.pop();       s5.pop();
   s4.push( 2 );   s5.push( 9 );
   cout << "1 == 2 is "<< (s1 == s2) << endl;
   cout << "1 == 3 is "<< (s1 == s3) << endl;
   cout << "1 == 4 is "<< (s1 == s4) << endl;
   cout << "1 == 5 is "<< (s1 == s5) << endl;
}

// 1 == 2 is 1
// 1 == 3 is 0
// 1 == 4 is 0
// 1 == 5 is 0



