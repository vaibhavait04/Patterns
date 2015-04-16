// Purpose.  Bridge                     
//
// Discussion.  Even though Date has    
// a clean interface and a well encap-  
// sulated implementation, the client   
// still has to recompile if the class  
// architect changes his/her mind.      
// Instead, create a wrapper (or inter- 
// face) class that contains and dele-  
// gates to a body (or implementation)  
// class.  Client can now specify at    
// run-time exactly what s/he wants.    
                                        
#include <iostream.h>                   
#include <stdio.h>
                                        
class Date {                            
                                        
public:
   Date( int y, int m, int d );         
   void output();                       
                                        
private:                                
                                        
#ifdef OK                               
   int  year_, month_, day_;            
#endif
                                        
#ifdef AA                               
   int        toJulian(int,int,int);    
   char*      fromJulian(void);         
   int        julian_;                  
   int        year_;                    
   static int dayTable_[2][13];         
#endif                                  
                                        
};                                      
                                        
#ifdef OK
void Date::output() {                   
   char buf[20];                        
   int year = year_ - (year_/100*100);  
   sprintf( buf, "%02d%02d%02d",        
      year, month_, day_ );             
   cout << buf << "  "; }               
#endif                                  
                                        
#ifdef AA
void Date::output() {                   
   cout << fromJulian() << "  "; }
#endif                                  
                                        
#include "bridge1.inc"                  
                                        
void main( void )                       
{                                       
   Date  d1( 1996, 2, 29 );             
   Date  d2( 1996, 2, 30 );             
   d1.output();                         
   d2.output();                         
   cout << endl;                        
}                                       

// 960229  960230                       
// 960229  960301                       


