#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std; 

class SortImp;

class Stat {
public:
   Stat();
   void upGrade();
   void downGrade();
   void readVector( int[], int );
   int getMin() { return min_; }
   int getMax() { return max_; }
   int getMed() { return med_; }
private:
   int min_, max_, med_;
   SortImp*  imp_;
};

class SortImp { public:
   virtual void sort( int[], int ) = 0;
};

class SortBubble : public SortImp {
public:
   void sort( int v[], int n );
};

class SortShell : public SortImp {
public:
   void sort( int v[], int n );
};

#include "strategy2.inc"

Stat::Stat() { imp_ = new SortBubble; }
void Stat::upGrade()   { delete imp_;
   imp_ = new SortShell; }
void Stat::downGrade() { delete imp_;
   imp_ = new SortBubble; }
void Stat::readVector(int v[], int n) {
   imp_->sort( v, n );
   min_ = v[0];   max_ = v[n-1];
   med_ = v[n/2]; }

int main( void )
{
   const int NUM = 9;
   int       array[NUM];
   time_t    t;
   srand((unsigned) time(&t));
   cout << "Vector: ";
   for (int i=0; i < NUM; i++) {
      array[i] = rand() % 9 + 1;
      cout << array[i] << ' '; }
   cout << endl;

   Stat  obj;
   obj.upGrade();
   obj.readVector( array, NUM );
   cout << "min is " << obj.getMin()
      << ", max is " << obj.getMax()
      << ", median is " << obj.getMed()
      << endl;
}


