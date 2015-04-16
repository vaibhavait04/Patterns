#include <iostream> 

using namespace std; 

class Throwable{
public: 
void checkExistence() {cout << "I am alive" << endl; }
~Throwable() { throw "wrong way"; }
};

int main()
{
try {
Throwable* t = new Throwable(); 
t->checkExistence();
t->~Throwable(); 
}
catch(...)
{
cout << " caught " << endl; 
}

}
