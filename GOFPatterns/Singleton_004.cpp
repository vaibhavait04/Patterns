// Purpose.  Singleton design pattern

// 1. Define a private static attribute in the "single instance" class
// 2. Define a public static accessor function in the class
// 3. Do "lazy initialization" (creation on demand) in the accessor function
// 4. Define all constructors to be protected or private
// 5. Clients may only use the accessor function to manipulate the Singleton
// 6. Inheritance can be supported, but static functions may not be overridden.
//    The base class must be declared a friend of the derived class (in order
//    to access the protected constructor).

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio> 
using namespace std;

class Number {
public:
   static  Number* instance();      // 2. Define a public static accessor func
   static  void setType( string t ) { type = t;  delete inst;  inst = 0;}
   virtual void setValue( int in )  { value = in; }
   virtual int  getValue()          { return value; }
protected:
   int value;
   Number() { cout << ":ctor: "; }  // 4. Define all ctors to be protected
private:
   static string  type;
   static Number* inst;             // 1. Define a private static attribute
};

string  Number::type = "decimal";
Number* Number::inst = 0;

class Octal : public Number {       // 6. Inheritance can be supported
public:
   friend class Number;
   void setValue( int in ) {
      char buf[10];
      sprintf( buf, "%o", in );
      sscanf( buf, "%d", &value );
   }
protected:
   Octal() { }
};

Number* Number::instance() {
   if ( ! inst)
      // 3. Do "lazy initialization" in the accessor function
      if (type == "octal") inst = new Octal();
      else                 inst = new Number();
   return inst;
}

int main( void ) {
   // Number  myInstance; --- error: cannot access protected constructor
   // 5. Clients may only use the accessor function to manipulate the Singleton
   Number::instance()->setValue( 42 );
   cout << "value is " << Number::instance()->getValue() << endl;
   Number::setType( "octal" );
   Number::instance()->setValue( 64 );
   cout << "value is " << Number::instance()->getValue() << endl;
}

// :ctor: value is 42
// :ctor: value is 100


