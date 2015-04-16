// Purpose.  Proxy design pattern

// 1. Design an "extra level of indirection" wrapper class
// 2. The wrapper class holds a pointer to the real class
// 3. The pointer is initialized to null
// 4. When a request comes in, the real object is created "on first use"
//    (aka lazy intialization)
// 5. The request is always delegated

#include <iostream> 

using namespace std; 

class RealImage {
   int  id;
public:
   RealImage( int i ) { id = i;  cout << "   $$ ctor: "<< id << '\n'; }
   ~RealImage()                { cout << "   dtor: " << id << '\n'; }
   void draw()                 { cout << "   drawing image " << id << '\n'; }
};

// 1. Design an "extra level of indirection" wrapper class
class Image {
   // 2. The wrapper class holds a pointer to the real class
   RealImage* theRealThing;
   int        id;
   static int next;
public:
   Image()  { id = next++;  theRealThing = 0; }  // 3. Initialized to null
   ~Image() { delete theRealThing; }
   void draw() {
      // 4. When a request comes in, the real object is created "on first use"
      if ( ! theRealThing) theRealThing = new RealImage( id );
      // 5. The request is always delegated
      theRealThing->draw();
}  };
int Image::next = 1;

int main( void ) {
   Image images[5];
   int   i;

   cout << "Exit[0], Image[1-5]: ";
   cin >> i;
   while (i) {
      images[i-1].draw();
      cout << "Exit[0], Image[1-5]: ";
      cin >> i;
}  }

// Exit[0], Image[1-5]: 2
//    $$ ctor: 2
//    drawing image 2
// Exit[0], Image[1-5]: 4
//    $$ ctor: 4
//    drawing image 4
// Exit[0], Image[1-5]: 2
//    drawing image 2
// Exit[0], Image[1-5]: 4
//    drawing image 4
// Exit[0], Image[1-5]: 0
//    dtor: 4
//    dtor: 2



