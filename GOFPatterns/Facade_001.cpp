#include <iostream.h>
#include <string.h>
#define sl strlen

class Compute {
public:
   char add( char a, char b, int& c ) {
      int result = a + b + c - 96;
      c = 0;
      if (result > 9) {
         result -= 10;
         c = 1;
      }
      return result + 48;
   }
};

class Facade {
public:
char* add( char* a, char* b ) {
   int cary = 0, i = 0;
   char c, d;
   if ((sl(a) > 1) && (sl(b) > 1)) {
      c = ones.add( a[1], b[1], cary );
      d = tens.add( a[0], b[0], cary );
   } else if (sl(a) > 1) {
      c = ones.add( a[1], b[0], cary );
      d = tens.add( a[0],  '0', cary );
   } else if (sl(b) > 1) {
      c = ones.add( b[1], a[0], cary );
      d = tens.add( b[0],  '0', cary );
   } else {
      c = tens.add( a[0], b[0], cary );
      d = 'x';
   }
   if (cary) ans[i++] = '1';
   if (d != 'x') ans[i++] =  d;
   ans[i++] = c;
   ans[i] = '\0';
   return ans;
}
private:
   Compute  tens, ones;
   char     ans[9];
};

void main( void ) {
   Facade  f;
   char    a[9], b[9];
   while (1) {
      cout << "Enter 2 nums: ";
      cin >> a >> b;
      cout <<"   sum is "<< f.add(a,b)
         << endl;
}  }

// Enter 2 nums: 9 13
//    sum is 22
// Enter 2 nums: 19 8
//    sum is 27
// Enter 2 nums: 3 99
//    sum is 102


