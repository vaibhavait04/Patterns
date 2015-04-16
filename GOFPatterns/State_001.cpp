#include <iostream>
using namespace std; 

class Boss {
public:
   friend class Disposition;
   Boss();
   void decide();
   void direct();
private:
   Disposition*  moods_[2];
   int           current_;
};

class Disposition {
public:
   virtual void decide( Boss* ) = 0;
   virtual void direct( Boss* ) = 0;
protected:
   void toggle( Boss* b ) {
      b->current_ = ! b->current_; }
};

class DilbertZone :
      public Disposition { public:
   void decide( Boss* b ) {
      cout << "Eenie, meenie, mynie,";
      cout << " moe.\n";  toggle(b); }
   void direct( Boss* b ) {
      cout << "My whim - you're";
      cout << " nightmare.\n";
      toggle(b); }
};
class Sunny :
      public Disposition { public:
   void decide( Boss* b ) {
      cout << "You need it - you got";
      cout << " it.\n";  toggle(b); }
   void direct( Boss* b ) {
      cout << "Follow me.\n";
      toggle(b); }
};

Boss::Boss() {
   moods_[0] = new DilbertZone;
   moods_[1] = new Sunny;
   current_ = 0; }
void Boss::decide() {
   moods_[current_]->decide( this ); }
void Boss::direct() {
   moods_[current_]->direct( this ); }

int main( void )
{
   Boss ph;
   for (int i=0; i < 2; i++) {
      ph.decide();
      ph.decide();
      ph.direct(); }
}
// Eenie, meenie, mynie, moe.
// You need it - you got it.
// My whim - you're nightmare.
// You need it - you got it.
// Eenie, meenie, mynie, moe.
// Follow me.


