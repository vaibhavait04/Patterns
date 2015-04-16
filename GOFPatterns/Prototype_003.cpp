#include <iostream>
#include <cstdlib> 
using namespace std;

class Stooge {
public:
   virtual Stooge* clone() = 0;
   virtual void slapStick() = 0;
};

class Factory {
public:
   static Stooge* create( int i );
private:
   static Stooge* prototypes_[4];
};

int main( void ) {
   Stooge*  roles[10];
   int      in, j, i = 0;

   cout << "vlh L(1) M(2) C(3) Go(0): ";
   cin >> in;
   while (in) {
      roles[i++] = Factory::create(in);
      cout << "L(1) M(2) C(3) Go(0): ";
      cin >> in;
   }

   for (j=0; j < i; j++)
      roles[j]->slapStick();

   for (j=0; j < i; j++)
      delete roles[j];
      
   system( "pause" );
}

class Larry : public Stooge {
public:
   Stooge* clone() { return new Larry; }
   void slapStick() {
      cout << "Larry: poke eyes" << endl; }
};
class Moe : public Stooge {
public:
   Stooge* clone() { return new Moe; }
   void slapStick() {
      cout << "Moe: slap head" << endl; }
};
class Curly : public Stooge {
public:
   Stooge* clone() {return new Curly;}
   void slapStick() {
      cout << "Curly: suffer abuse" << endl; }
};

Stooge* Factory::prototypes_[] = { 0, new Larry, new Moe, new Curly };
Stooge* Factory::create( int i ) { return prototypes_[i]->clone(); }

