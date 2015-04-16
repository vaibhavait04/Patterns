#include <iostream.h>

const int X = 6;
const int Y = 10;

class Gazillion {
public:
   Gazillion( int in ) {
      val1_ = in;
      cout << "ctor: "<< val1_<<endl; }
   ~Gazillion() {
      cout << val1_ << ' '; }
   void report( int in ) {
      cout << val1_ << in << ' '; }
private:
   int  val1_;
};

class Factory {
public:
   static Gazillion* getFly(int in) {
      if ( ! pool_[in])
         pool_[in] =
                 new Gazillion( in );
      return pool_[in];
   }
   static void cleanUp() {
      cout << "dtors: ";
      for (int i=0; i < X; i++)
         if (pool_[i])
            delete pool_[i];
      cout << endl;
   }
private:
   static Gazillion*  pool_[X];
};

Gazillion*  Factory::pool_[]  = {
                         0,0,0,0,0,0 };

void main( void )
{
   for (int i=0; i < X; i++)
   {
      for (int j=0; j < Y; j++)
         Factory::getFly(i)->report(j);
      cout << endl;
   }
   Factory::cleanUp();
}

// ctor: 0
// 00 01 02 03 04 05 06 07 08 09
// ctor: 1
// 10 11 12 13 14 15 16 17 18 19
// ctor: 2
// 20 21 22 23 24 25 26 27 28 29
// ctor: 3
// 30 31 32 33 34 35 36 37 38 39
// ctor: 4
// 40 41 42 43 44 45 46 47 48 49
// ctor: 5
// 50 51 52 53 54 55 56 57 58 59
// dtors: 0 1 2 3 4 5


