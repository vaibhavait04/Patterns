#include <iostream>

using namespace std; 

class H {
public:
   H( H* next = 0 ) {
      id_   = count_++;
      busy_ = 0;
      next_ = next;
   }
   ~H() {
      cout << id_<<" dtor" << endl;
      // don't get into a loop
      if (next_->next_) {
         H* t = next_;
         next_ = 0;
         delete t;
   }  }
   void setNext( H* next ) {
      next_ = next;
   }
   void handle() {
      if (busy_ = ! busy_)
         cout << id_ << " handles"
            << endl;
      else {
         cout << id_ << " is busy"
            << endl;
         next_->handle();
   }  }
private:
   int        id_, busy_;
   H*         next_;
   static int count_;
};
int H::count_ = 1;

H* setUpList() {
   H* first = new H;
   H* last = new H(first);
   first->setNext( last );
   return first;
}

int main( void ) {
   H* head = setUpList();

   for (int i=0; i < 6; i++)
      head->handle();

   delete head;
}

// 1 handles
// 1 is busy
// 2 handles
// 1 handles
// 1 is busy
// 2 is busy
// 1 handles
// 1 is busy
// 2 handles
// 1 handles
// 1 dtor
// 2 dtor


