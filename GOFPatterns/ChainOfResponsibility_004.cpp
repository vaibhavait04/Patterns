// Purpose.  Chain of Responsibility - links bid on job, chain assigns job
//
// 1. Base class maintains a "next" pointer
// 2. Each "link" does its part to handle (and/or pass on) the request
// 3. Client "launches and leaves" each request with the chain
// 4. The current bid and bidder are maintained in chain static members
// 5. The last link in the chain assigns the job to the low bidder

#include <iostream>
#include <ctime>
#include <cstdlib> 
using namespace std;

class Link {
   int   id;
   Link* next;                       // 1. "next" pointer
   static int   theBid;              // 4. Current bid and bidder
   static Link* bidder;
public:
   Link( int num ) { id = num;  next = 0; }
   void addLast( Link* l ) {
      if (next) next->addLast( l );  // 2. Handle and/or pass on
      else      next = l; 
   }
   void bid() {
      int num = rand() % 9;
      cout << id << '-' << num << "  ";
      if (num < theBid) {
         theBid = num;               // 4. Current bid and bidder
         bidder = this;
      }
      if (next) next->bid();         // 2. Handle and/or pass on
      else      bidder->execute();   // 5. The last 1 assigns the job
   }
   void execute() {
      cout << id << " is executing\n";
      theBid = 999;
}  };
int   Link::theBid = 999;            // 4. Current bid and bidder
Link* Link::bidder = 0;

int main( void ) {
   Link chain( 1 );
   for (int i=2; i < 7; i++)
      chain.addLast( new Link( i ) );
   srand( time( 0 ) );
   for (int i=0; i < 10; i++)
      chain.bid();                   // 3. Client "launches & leaves"
}

// 1-1  2-6  3-0  4-3  5-1  6-0  3 is executing
// 1-1  2-1  3-1  4-0  5-7  6-1  4 is executing
// 1-0  2-1  3-0  4-6  5-1  6-2  1 is executing
// 1-6  2-3  3-8  4-0  5-1  6-4  4 is executing
// 1-8  2-0  3-5  4-8  5-4  6-2  2 is executing
// 1-1  2-0  3-8  4-8  5-7  6-0  2 is executing
// 1-1  2-1  3-3  4-1  5-6  6-2  1 is executing
// 1-2  2-1  3-0  4-3  5-6  6-8  3 is executing
// 1-7  2-5  3-4  4-2  5-1  6-2  5 is executing
// 1-3  2-6  3-7  4-7  5-6  6-0  6 is executing

