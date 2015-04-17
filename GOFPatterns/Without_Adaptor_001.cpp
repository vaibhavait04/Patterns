// Purpose.  Adapter
//
// Discussion.  The Adapter pattern
// discusses how to "wrap" the old in-
// terface of a legacy component, so
// that it can continue to contribute
// in a new system.  It is about "im-   
// pedance matching" an old dog with    
// new tricks (to mix metaphors).  On   
// the left, WimpyTime "hasa" in-
// stance of the legacy component,      
// and delegates the "heavy lifting"    
// to it.  On the right, private        
// derivation is used to accomplish     
// the same result.                     
 
#include <iostream> 
#include <cstdio> 
#include <string.h> 
using namespace std; 
                                       
class ManlyTime {                       
public:                                 
   char* getTime() {                    
      static char buf[30];              
      time_t  lt;                       
      tm*     ltStruct;                 
      time( &lt );                      
      ltStruct = localtime(&lt);
      strftime( buf, 30, "%H%M",        
         ltStruct );                    
      return buf;                       
   }                                    
};                                      
                                        
class WimpyTime {                       
public:                                 
   char* getTime() {                    
      static char buf[30];              
      char *ptr, mi[3], am[3];          
      int  hr;                          
      ptr = imp_.getTime();             
      cout << "old interface time is "  
         << ptr << endl;                
      strcpy( mi, &(ptr[2]) );          
      ptr[2] = '\0';                    
      sscanf( ptr, "%d", &hr );         
      strcpy( am, "AM" );               
      if (hr > 12) {                    
         hr -= 12;                      
         strcpy( am, "PM" ); }          
      sprintf( buf, "%d:%s %s",
         hr, mi, am );                  
      return buf;                       
   }                                    
private:                                
   ManlyTime  imp_;                     
};                                      
                                        
int main( void )                       
{
   WimpyTime  newT;                     
   char*      ptr;                      
   ptr = newT.getTime();
   cout << "new interface time is "
      << ptr << endl;
}

// old interface time is 1709
// new interface time is 5:09 PM



