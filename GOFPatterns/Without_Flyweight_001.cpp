// Purpose.  Flyweight                
//
// Discussion.  Trying to use objects 
// at very low levels of granularity  
// is nice, but the overhead may be
// prohibitive.  Flyweight suggests   
// removing the non-shareable state   
// from the class, and having the cli-
// ent supply it when methods are     
// called.  This places more respon-  
// sibility on the client, but, con-  
// siderably fewer instances of the   
// Flyweight class are now created.   
// Sharing of these instances is fa-  
// cilitated by introducing a Factory 
// class that maintains a "cache" of  
// existing Flyweights.               
//
// In this example, the "X" state is  
// considered shareable (within each  
// row anyways), and the "Y" state has
// been externalized (it is supplied  
// by the client when report() is     
// called).                           
                                      
#include <iostream.h>                 
                                      
const int X = 6;                      
const int Y = 10;                     
                                      
class Gazillion {                     
public:                               
   Gazillion() {                      
      val1_ = num_ / Y;               
      val2_ = num_ % Y;               
      num_++;                         
   }
   void report() {                    
      cout << val1_ << val2_ << ' ';  
   }
private:                              
   int    val1_;                      
   int    val2_;                      
   static int num_;                   
};                                    
                                      
int Gazillion::num_ = 0;              
                                      
void main( void )                     
{                                     
   Gazillion  matrix[X][Y];
   for (int i=0; i < X; i++)          
   {                                  
      for (int j=0; j < Y; j++)       
         matrix[i][j].report();       
      cout << endl;                   
   }                                  
}                                     
                                      
// 00 01 02 03 04 05 06 07 08 09      
// 10 11 12 13 14 15 16 17 18 19      
// 20 21 22 23 24 25 26 27 28 29      
// 30 31 32 33 34 35 36 37 38 39      
// 40 41 42 43 44 45 46 47 48 49      
// 50 51 52 53 54 55 56 57 58 59


