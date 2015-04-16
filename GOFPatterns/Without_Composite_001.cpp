// Purpose.  Composite                  
#include <iostream> 
#include <string.h>
using namespace std; 
                     
enum NodeType { FileT, DirT };          
int  g_indent = 0;                      
                                        
class File {                            
public:                                 
   File( char* n ) { type_ = FileT;
      strcpy( name_, n ); }             
   NodeType getType() { return type_; } 
   void ls() {                          
      for (int i=0; i < g_indent; i++)  
         cout << ' ';                   
      cout << name_ << endl; }          
private:                                
   NodeType  type_;                     
   char      name_[20];
};                                      
                                        
class Dir {                             
public:                                 
   Dir( char* n ) { type_ = DirT;       
      strcpy( name_, n ); total_ = 0; } 
   NodeType getType() { return type_; } 
   void add( File* f ) {                
      files_[total_++] = f;             
   }
   void ls() {                          
      for (int i=0; i < g_indent; i++)  
         cout << ' ';                   
      cout << name_ << ":" << endl;     
      g_indent += 3;                    
      for (int i=0; i < total_; i++)    
         if (files_[i]->getType()       
               == DirT)                 
            ((Dir*) files_[i])->ls();   
         else                           
            files_[i]->ls();            
      g_indent -= 3; }                  
private:                                
   NodeType  type_;                     
   char      name_[20];                 
   File*     files_[10];                
   int       total_;                    
};                                      

int main( void )                       
{                                       
   Dir   one("1"), two("2"), thr("3");  
   File  a("a"), b("b"), c("c"),        
         d("d"), e("e");                
   one.add( &a );                       
   one.add( (File*) &two );             
   one.add( &b );                       
   two.add( &c );                       
   two.add( &d );                       
   two.add( (File*) &thr );             
   thr.add( &e );                       
   one.ls();                            
}                                       

// 1:          //       d               
//    a        //       3:              
//    2:       //          e            
//       c     //    b                  



