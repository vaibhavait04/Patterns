#include <iostream> 

using namespace std; 

class Throwable{
int a; 
public: 
Throwable():a(0){}
void checkExistence() {cout << "I am alive" << endl; }
~Throwable() { throw "wrong way"; }
};

int main()
{
try {
try {
Throwable t; 
t.checkExistence();
throw 5; 
}
catch(...)
{
cout << " caught " << endl; 
}
}catch (...)
{
cout << " caught in second " << endl; 
}

}
