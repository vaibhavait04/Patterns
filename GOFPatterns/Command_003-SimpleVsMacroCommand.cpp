// Purpose.  Simple and "macro" commands
// 
// Discussion.  Encapsulate a request as an object.  SimpleCommand
// maintains a binding between a receiver object and an action stored as a
// pointer to a member function.  MacroCommand maintains a sequence of
// Commands.  No explicit receiver is required because the subcommands
// already define their receiver.  MacroCommand may contain MacroCommands.

#include <iostream>
#include <vector>
using namespace std;

class Number { public:
   void dubble( int& value ) { value *= 2; }
};

class Command { public: virtual void execute( int& ) = 0; };

class SimpleCommand : public Command {
   typedef void (Number::* Action)(int&);
   Number* receiver;
   Action  action;
public:
   SimpleCommand( Number* rec, Action act ) {
      receiver = rec;
      action = act;
   }
   /*virtual*/ void execute( int& num ) { (receiver->*action)( num ); }
};

class MacroCommand : public Command {
   vector<Command*> list;
public:
   void add( Command* cmd ) { list.push_back( cmd ); }
   /*virtual*/ void execute( int& num ) {
   	for (int i=0; i < list.size(); i++)
         list[i]->execute( num );
}  };

int main( void ) {
   Number object;
   Command* commands[3];
   commands[0] = new SimpleCommand( &object, &Number::dubble );

   MacroCommand two;
   two.add( commands[0] );   two.add( commands[0] );
   commands[1] = &two;

   MacroCommand four;
   four.add( &two );   four.add( &two );
   commands[2] = &four;

   int num, index;
   while (true) {
   	cout << "Enter number selection (0=2x 1=4x 2=16x): ";
      cin >> num >> index;
      commands[index]->execute( num );
      cout << "   " << num << '\n';
}  }

// Enter number selection (0=2x 1=4x 2=16x): 3 0
//    6
// Enter number selection (0=2x 1=4x 2=16x): 3 1
//    12
// Enter number selection (0=2x 1=4x 2=16x): 3 2
//    48
// Enter number selection (0=2x 1=4x 2=16x): 4 0
//    8
// Enter number selection (0=2x 1=4x 2=16x): 4 1
//    16
// Enter number selection (0=2x 1=4x 2=16x): 4 2
//    64



