// Purpose.  Inheritance run amok

#include <iostream>
using namespace std;

class A { public:
   virtual void doIt() { cout << 'A'; }
};

class AwithX : public A {
   void doX() { cout << 'X'; }
public:
   /*virtual*/ void doIt() {
      A::doIt();
      doX();
}  };

class AwithY : public A {
protected:
   void doY() { cout << 'Y'; }
public:
   /*virtual*/ void doIt() {
      A::doIt();
      doY();
}  };

class AwithZ : public A {
protected:
   void doZ() { cout << 'Z'; }
public:
   /*virtual*/ void doIt() {
      A::doIt();
      doZ();
}  };

class AwithXY : public AwithX, public AwithY { public:
   /*virtual*/ void doIt() {
      AwithX::doIt();
      AwithY::doY();
}  };

class AwithXYZ : public AwithX, public AwithY, public AwithZ { public:
   /*virtual*/ void doIt() {
      AwithX::doIt();
      AwithY::doY();
      AwithZ::doZ();
}  };

int main( void ) {
   AwithX    anX;
   AwithXY   anXY;
   AwithXYZ  anXYZ;
   anX.doIt();    cout << '\n';
   anXY.doIt();   cout << '\n';
   anXYZ.doIt();  cout << '\n';
}

// AX
// AXY
// AXYZ


