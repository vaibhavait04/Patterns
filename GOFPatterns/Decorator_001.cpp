// Purpose.  Decorator design pattern

// 1. Create a "lowest common denominator" that makes classes interchangeable
// 2. Create a second level base class for optional functionality
// 3. "Core" class and "Decorator" class declare an "isa" relationship
// 4. Decorator class "hasa" instance of the "lowest common denominator"
// 5. Decorator class delegates to the "hasa" object
// 6. Create a Decorator derived class for each optional embellishment
// 7. Decorator derived classes delegate to base class AND add extra stuf
// 8. Client has the responsibility to compose desired configurations

#include <iostream>
using namespace std;

class Widget { public: virtual void draw() = 0; };  // 1. "lowest common denom"

class TextField : public Widget {                   // 3. "Core" class & "isa"
   int width, height;
public:
   TextField( int w, int h ) { width  = w;  height = h; }
   /*virtual*/ void draw() { cout << "TextField: " << width << ", " << height << '\n'; }
};
                                                    // 2. 2nd level base class
class Decorator : public Widget {                   // 3. "isa" relationship
   Widget* wid;                                     // 4. "hasa" relationship
public:
   Decorator( Widget* w )  { wid = w; }
   /*virtual*/ void draw() { wid->draw(); }         // 5. Delegation
};

class BorderDecorator : public Decorator { public:  // 6. Optional embellishment
   BorderDecorator( Widget* w ) : Decorator( w ) { }
   /*virtual*/ void draw() {
      Decorator::draw();                            // 7. Delegate to base class
      cout << "   BorderDecorator" << '\n';         //    and add extra stuff
}  };

class ScrollDecorator : public Decorator { public:  // 6. Optional embellishment
   ScrollDecorator( Widget* w ) : Decorator( w ) { }
   /*virtual*/ void draw() {
      Decorator::draw();                            // 7. Delegate to base class
      cout << "   ScrollDecorator" << '\n';         //    and add extra stuff
}  };

void main( void ) {
   // 8. Client has the responsibility to compose desired configurations
   Widget* aWidget = new BorderDecorator(
                        new BorderDecorator(
                           new ScrollDecorator(
                              new TextField( 80, 24 ))));
   aWidget->draw();
}

// TextField: 80, 24
//    ScrollDecorator
//    BorderDecorator
//    BorderDecorator


