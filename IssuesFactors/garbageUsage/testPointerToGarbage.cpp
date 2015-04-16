#include <iostream> 
using namespace std; 

class A{
public: 
void fun(){cout << "hello from fun" << endl; }
};

int main()
{
A* p= NULL; 
p->fun(); 

}
