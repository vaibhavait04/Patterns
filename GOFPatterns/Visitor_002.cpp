// Purpose.  Visitor (double dispatch)
//
// Discussion.  On the left, the State derived classes must query the type of
// the Cmd objects they receive, in order to identify what the next course of
// action is.  "case" stmts are always a maintenance headache.  On the right,
// we have recognized that what we really want to do is "dispatch" based on
// the type of TWO objects, (a State object and a Cmd object).  The call to
// accept() discriminates the type of the State object that is being messaged,
// and then the call to visit() discriminates the type of the Cmd object
// (while passing the type of the State object).  If new Cmd classes are
// added, no change whatsoever is necessary in the code of the State classes.
// If new State classes are added, then every Cmd class must be changed, and
// Visitor is NOT the right approach to take.

#include <iostream>
using namespace std; 

int  current = 0;
class One;  class Two;

class Cmd { public:
   virtual void visit( One* ) {
      cout << "ERROR\n"; }
   virtual void visit( Two* ) {
      cout << "ERROR\n"; }
};
class On : public Cmd { public:
   void visit( One* ) {
      current = 1;
      cout << "One,On => Two\n"; }
   void visit( Two* t ) {
      Cmd::visit( t ); }
};
class Off : public Cmd { public:
   void visit( One* o ) {
      Cmd::visit( o ); }
   void visit( Two* ) {
      current = 0;
      cout << "Two,Off => One\n"; }
};

class State { public:
   virtual void accept( Cmd* c ) = 0;
};
class One : public State { public:
   void accept( Cmd* c ) {
      c->visit( this ); }
};
class Two : public State { public:
   void accept( Cmd* c ) {
      c->visit( this ); }
};

State* states[] = { new One, new Two };

int main( void )
{
   Cmd* c[] = { new Off,
        new On, new Off, new Off, 0 };
   for (int i=0; c[i]; i++)
      states[current]->accept( c[i] );
}

// ERROR
// One,On => Two
// Two,Off => One
// ERROR


