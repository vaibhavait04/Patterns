// Purpose.  Mediator
//
// Discussion.  On the left: Node objs  
// interact directly with each other,
// recursion is required, removing a    
// Node is hard, and it is not possi-   
// ble to remove the first node.  On    
// the right: a "mediating" List class  
// focuses and simplifies all the ad-   
// ministrative responsibilities, and   
// the recursion (which does not scale  
// up well) has been eliminated.
                                        
#include <iostream>                   
using namespace std; 

class Node {                            
public:                                 
   Node( int v, Node* n ) {             
      val_ = v;                         
      next_ = n;                        
   }                                    
   void traverse() {                    
      cout << val_ << "  ";             
      if (next_)                        
         next_->traverse();             
      else                              
         cout << endl;                  
   }                                    
   void removeNode( int v ) {           
      Node*  ptr = (Node*) 1;           
      removeNode_( v, &ptr );           
   }                                    
private:                                
   int    val_;                         
   Node*  next_;                        
   void removeNode_(int v, Node** n) {  
      if (val_ == v)                    
         *n = next_;                    
      else                              
      {                                 
         next_->removeNode_( v, n );    
         if (*n != (Node*) 1)           
         {                              
            next_ = *n;
            *n = (Node*) 1;             
         }                              
      }                                 
   }                                    
};                                      
                                        
int main( void )                       
{                                       
   Node  fou( 44, 0 );                  
   Node  thr( 33, &fou );               
   Node  two( 22, &thr );               
   Node  one( 11, &two );               
   one.traverse();                      
   one.removeNode( 44 );                
   one.traverse();                      
   one.removeNode( 22 );
   one.traverse();                      
}                                       
                                        
// 11  22  33  44
// 11  22  33
// 11  33



