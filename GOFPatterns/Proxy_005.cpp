// Purpose.  Simulate a Persistent Object Pointer

template <typename TBD>
class POP {          // Persistent Object Pointer
   string oid;
   TBD*   ptr;
public:
   POP( string id )  { oid = id;  ptr = 0; }
   ~POP()            { delete ptr; }
   TBD* operator->() {
      if ( ! ptr)
         // simulate the persistence mechanism
         ptr = new TBD( oid );
      return ptr;
}  };

class Person {
   string name;
   int    age;
public:
   Person( string n ) { name = n; }
   string getName()   { return name; }
   int    getAge()    { return 32; }
};

void main( void ) {
   POP<Person> ph( "Tom" );
   cout << "policy holder is " << ph->getName() << ", age is " << ph->getAge() << '\n';
}

// policy holder is Tom, age is 32


