#include <iostream> 
#ifndef __SMART_PTR
#define __SMART_PTR

template<typename T>
class smart_pointer{
    T* pointer;
    std::size_t *refs;

    void clear(){
        if (!--*refs){
            delete pointer;
            delete refs;
        }
    }

public:
    smart_pointer(T* p = NULL)
        : pointer(p), refs(new std::size_t(1))
    {}

    smart_pointer(const smart_pointer<T>& other)
        : pointer(other.pointer), refs(other.refs)
    {
        ++*refs;
    }
    ~smart_pointer(){
        clear();
    }

    smart_pointer<T>& operator=(const smart_pointer<T>& other){
        if (this != &other){
            clear();

            pointer = other.pointer;
            refs    = other.refs;
            ++*refs;
        }
        return *this;
    }

    smart_pointer<T>& operator=(T* p){
        if (pointer != p){
            pointer = p;
            *refs = 1;
        }
        return *this;
    }

    T& operator*(){
        return *pointer;
    }

    const T& operator*() const{
        return *pointer;
    }

    T* operator->(){
        return pointer;
    }

    const T* operator->() const{
        return pointer;
    }

    std::size_t getCounts(){
        return *refs;
    }
};

#endif 
