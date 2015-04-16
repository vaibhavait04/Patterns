#include <iostream> 
using namespace std; 

class A{
int x; 
public: 
void fun(){cout << "hello from fun value: " << x << endl; }
};

int main()
{
A* p= NULL; 
p->fun(); 

}
