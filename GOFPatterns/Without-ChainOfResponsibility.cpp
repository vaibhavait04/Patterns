// Purpose.  Chain of Responsibility.
//
// Discussion.  Instead of the client
// having to know about the number of
// "handlers", and manually map re-  
// quests to available handlers; de- 
// sign the handlers into an "intel- 
// ligent" chain.  Clients "launch   
// and leave" requests with the head 
// of the chain.                     
                                     
#include <iostream> 
#include <cstdio> 
#include <cstdlib> 
               
using namespace std;                                      
class H {                            
public:                              
   H() {                             
      id_ = count_++;                
      busy_ = 0;                     
   }                                 
   ~H() {                            
      cout << id_ << " dtor" << endl;
   }                                 
   int handle() {                    
      if (busy_ = ! busy_) {         
         cout << id_ << " handles"   
            << endl;                 
         return 1;                   
      } else {                       
         cout << id_ << " is busy"   
            << endl;                 
         return 0;                   
   }  }                              
private:                             
   int        id_, busy_;            
   static int count_;                
};
int H::count_ = 1;                   
                                     
void main( void ) {                  
   const int TOTAL = 2;              
   H* list[TOTAL] = { new H, new H };
                                     
   for (int i=0; i < 6; i++)
      for (int j=0; 1 ;              
               j = (j + 1) % TOTAL)  
         if (list[j]->handle())
            break;                   
                                     
   for (int k=0; k < TOTAL; k++)
      delete list[k];                
}                                    

// 1 handles                         
// 1 is busy                         
// 2 handles                         
// 1 handles                         
// 1 is busy                         
// 2 is busy                         
// 1 handles                         
// 1 is busy                         
// 2 handles                         
// 1 handles                         
// 1 dtor                            
// 2 dtor                            

