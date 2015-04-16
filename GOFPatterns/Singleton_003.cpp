// New design.  "globalObj" is now a
// static variable in the inst() ac-
// cessor method.  The single inst-
// ance is enforced by declaring the
// ctor non-public.  [The dtor must
// be public because of the static
// variable instance.]  Global
// access is provided by the static
// inst() method.  The object is al-
// located on first demand by C++,
// and it is de-allocated automati-
// cally by C++.

#include <iostream>
using namespace std; 

class GlobalClass {
public:
   int  getValue() {
      return value_; }
   void setValue( int v ) {
      value_ = v; }
   static GlobalClass& inst() {
      static GlobalClass globalObj;
      return globalObj; }
   ~GlobalClass() {
      cout << ":dtor:" << endl; }
protected:
   GlobalClass( int v=0 ) {
      cout << ":ctor: ";
      value_ = v; }
private:
   int  value_;
};

void foo( void )
{
   GlobalClass::inst().setValue( 1 );
   cout << "foo: globalObj is " <<
      GlobalClass::inst().getValue()
      << endl;
}

void bar( void )
{
   GlobalClass::inst().setValue( 2 );
   cout << "bar: globalObj is " <<
      GlobalClass::inst().getValue()
      << endl;
}

int main( void )
{
   cout << "main: globalObj is " <<
      GlobalClass::inst().getValue()
      << endl;
   foo();
   bar();
   cout << "main: end" << endl;
}

// main: globalObj is :ctor: 0
// foo: globalObj is 1
// bar: globalObj is 2
// main: end
// :dtor:





