// Purpose.  Facade                     
//                                      
// Discussion.  Class Compute models    
// a decimal digit adder module.  An
// entire "subsystem" can be configur-  
// ed by linking as many of these       
// modules as the desired precision     
// requires.  The "subsystem" being     
// modeled in main() is complex and     
// burdensome to use.  Wrapping this    
// subsystem inside of a Facade that    
// exports a simple interface is        
// desirable.                           
                                        
#include <iostream>                   
#include <string.h>                     
#define sl strlen
using namespace std;                
class Compute {                         
public:                                 
   char add( char a, char b, int& c) {  
      int result = a + b + c - 96;      
      c = 0;                            
      if (result > 9) {                 
         result -= 10;                  
         c = 1;                         
      }                                 
      return result + 48;               
   }                                    
};                                      
                                        
int main( void ) {                     
   Compute  tens, ones;                 
   char     a[9], b[9], c, d;           
   int      cary;                       
while (1) {                             
   cout << "Enter 2 nums: ";            
   cin >> a >> b;                       
   cout << "   sum is ";                
   cary = 0;                            
   if ((sl(a) > 1) && (sl(b) > 1)) {    
      c = ones.add( a[1], b[1], cary);  
      d = tens.add( a[0], b[0], cary);  
   } else if (sl(a) > 1) {              
      c = ones.add( a[1], b[0], cary);  
      d = tens.add( a[0],  '0', cary);
   } else if (sl(b) > 1) {              
      c = ones.add( b[1], a[0], cary);  
      d = tens.add( b[0],  '0', cary);  
   } else {                             
      c = tens.add( a[0], b[0], cary);  
      d = 'x';                          
   }                                    
   if (cary) cout << '1';               
   if (d != 'x') cout << d;             
   cout << c << endl;
}  }                                    
                                        
// Enter 2 nums: 99 99                  
//    sum is 198                        
// Enter 2 nums: 38 83                  
//    sum is 121                        
// Enter 2 nums: 5 6
//    sum is 11


