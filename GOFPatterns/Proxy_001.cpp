// Purpose.  Direct coupling, lots of start-up and shut-down overhead

#include <iostream>
#include <string>
using namespace std;

class Image {
   int        id;
   static int next;
public:
   Image() { id = next++;  cout << "   $$ ctor: "<< id << '\n'; }
   ~Image()              { cout << "   dtor: " << id << '\n'; }
   void draw()           { cout << "   drawing image " << id << '\n'; }
};
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

//    $$ ctor: 1
//    $$ ctor: 2
//    $$ ctor: 3
//    $$ ctor: 4
//    $$ ctor: 5
// Exit[0], Image[1-5]: 2
//    drawing image 2
// Exit[0], Image[1-5]: 4
//    drawing image 4
// Exit[0], Image[1-5]: 2
//    drawing image 2
// Exit[0], Image[1-5]: 0
//    dtor: 5
//    dtor: 4
//    dtor: 3
//    dtor: 2
//    dtor: 1



