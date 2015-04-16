// Purpose.  State design pattern - an FSM with two states and two events
// (distributed transition logic - logic in the derived state classes)

// State\Event     Suck up money      Drive through
//
// RedLight          you're a            you're   
//                    victim,             dead,
//                 maybe change       change to RED
//                   to GREEN
//
// GreenLight        you're an         you're free
//                     idiot           but you're
//                                  still a victim,
//                                   change to RED

#include <iostream>
#include <ctime>
using namespace std;

class FSM {
   class State* current;
public:
   FSM();
   void setCurrent( State* s ) { current = s; }
   void suckUpMoney( int );
   void carDrivesThrough();
};

class State {
   int total;
protected:
   int getTotal() { return total; }
public:
   State() { total = 0; }
   virtual void suckUpMoney( int in, FSM* fsm ) {
      total += in;
      cout << "total is " << total << '\n';
   }
   virtual void carDrivesThrough( FSM* fsm ) = 0;
};

class GreenLight : public State {
public:
   GreenLight() { cout << "GREEN light\n"; }
   void suckUpMoney( int in, FSM* fsm ) {
      cout << "      You're an idiot, ";
      State::suckUpMoney( in, fsm );
   }
   void carDrivesThrough( FSM* fsm );
};

class RedLight : public State {
public:
   RedLight() { cout << "RED light\n"; }
   void suckUpMoney( int in, FSM* fsm ) {
      cout << "      ";
      State::suckUpMoney( in, fsm );
      if (getTotal() >= 50) {
         fsm->setCurrent( new GreenLight );
         delete this;
   }  }
   void carDrivesThrough( FSM* fsm ) {
      cout << "Sirens!!  Heat-seeking missile!!  Confiscate net worth!!\n";
      fsm->setCurrent( new RedLight );
      delete this;
}  };

FSM::FSM() {
   current = new RedLight();
}
void FSM::suckUpMoney( int in ) {
   current->suckUpMoney( in, this );
}
void FSM::carDrivesThrough() {
   current->carDrivesThrough( this );
}
void GreenLight::carDrivesThrough( FSM* fsm ) {
   cout << "Good-bye sucker!!\n";
   fsm->setCurrent( new RedLight );
   delete this;
}

int getCoin() {
   static int choices[3] = { 5, 10, 25 };
   return choices[rand() % 3];
}

int main( void ) {
   srand( time(0) );
   FSM fsm;
   int ans;
   while (true) {
      cout << "   Shell out (1), Drive thru (2), Exit (0): ";
      cin >> ans;
      if      (ans == 1) fsm.suckUpMoney( getCoin() );
      else if (ans == 2) fsm.carDrivesThrough();
      else break;
}  }


