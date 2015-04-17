#include "smart_ptr.h"

struct foo{
    int a;
};

template<typename pointer_t>
class bar{
    pointer_t f_;

public:
    bar(foo *f)
        :f_(f)
    {}

    void set(int a){
        f_->a = a;
    }
};

int main()
{
    foo *f = new foo;

    typedef smart_pointer<foo> ptr_t;
//    typedef boost::shared_ptr<foo> ptr_t;
//    typedef foo* ptr_t;

    bar<ptr_t> b(f);
    for (unsigned int i = 0; i<300000000; ++i)
        b.set(i);

//    delete f;
    return 0;
}

