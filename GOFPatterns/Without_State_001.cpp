// Purpose.  State                      
//
// Discussion.  The boss's behavior is  
// "morphing" radically as a function   
// of his mood.  Operations have large  
// "case" constructs that depend on     
// this "state" attribute.  Like large  
// procedures, large conditional stmts  
// are undesirable.  They're monolith-  
// ic, and tend to make maintenance     
// very difficult.  The State pattern   
// models individual states with de-    
// rived classes of an inheritance
// hierarchy, and front-ends this       
// hierarchy with an "interface"        
// object that knows its "current"      
// state.  This partitions and local-   
// izes all state-specific responsi-    
// bilities; allowing for a cleaner     
// implementation of dynamic behavior   
// that must change as internal state   
// changes.
                                        
class Boss {                            
public:                                 
   Boss() {                             
      mood_ = DilbertZone;              
   }                                    
   void decide() {                      
      if (mood_ == DilbertZone) {       
         cout << "Eenie, meenie,";      
         cout << " mynie, moe.\n";      
      }                                 
      else if (mood_ == Sunny) {        
         cout << "You need it - you";   
         cout << " got it.\n";          
      }                                 
      toggle();                         
   }                                    
   void direct() {                      
      if (mood_ == DilbertZone) {       
         cout << "My whim - you're";
         cout << " nightmare.\n";       
      }                                 
      else if (mood_ == Sunny)          
         cout << "Follow me.\n";        
      toggle();                         
   }                                    
private:                                
   enum Disposition { Sunny,            
                      DilbertZone};
   Disposition  mood_;                  
   void toggle() { mood_ = ! mood_; }   
};                                      
                                        
void main( void )                       
{                                       
   Boss ph;                             
   for (int i=0; i < 2; i++)            
   {                                    
      ph.decide();                      
      ph.decide();                      
      ph.direct();                      
   }                                    
}                                       


