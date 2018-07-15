#ifndef MYPOINTER
#define MYPOINTER

#include <iostream>

using namespace std;

// smart pointer.
template<typename T>
class MyPointer{
private:
    T* pointer;

public:
    // constructor
    MyPointer();
    MyPointer(T*);
    MyPointer(const MyPointer&);

    // destructor
    ~MyPointer();

    // override
    MyPointer& operator=(const MyPointer&);
};


// ==============


// default constructor.
template<typename T>
MyPointer<T>::MyPointer():
    pointer(nullptr)
{
    cout<< "You created an unknown smart pointer.\n" <<endl;
}


// constructor accepting different pointer types.
template<typename T>
MyPointer<T>::MyPointer(T* p):
    pointer(p)
{
    cout<< "You created a smart pointer at "
        << static_cast<const void*>(p)
        <<'\n'<<endl;

    if(pointer)
        pointer->incRefCount();
}


// copy constructor
template<typename T>
MyPointer<T>::MyPointer(const MyPointer<T>& sp):
    pointer(sp.pointer)
{
    cout<< "Copy smart pointer at "
        << static_cast<const void*>(sp.pointer)
        <<'\n'<<endl;

    if(pointer)
        pointer->incRefCount();
}


/*
--------------
*/


// destructor
template<typename T>
MyPointer<T>::~MyPointer(){
    cout<< "release the smart pointer at "
        << static_cast<const void*>(pointer)
        << '\n'<<endl;

    if(pointer && pointer->decRefCount() == 0)
        delete pointer;
}


/*
--------------
*/

// override operator=
template<typename T>
MyPointer<T>& MyPointer<T>::operator=(const MyPointer<T>& sp){
    /* if this == &sp and we delete pointer, sp.pointer is deleted too,
       which means pointer will point to a released resource.*/
    if(this == &sp)
        return *this;

    sp.pointer->incRefCount();
    if(pointer && pointer->decRefCount == 0)
        delete pointer;
    pointer = sp.pointer;

    cout<< "Assign smart pointer at "
        << static_cast<const void*>(sp.pointer)
        <<'\n'<<endl;

    return *this;
}


// ==============
// ==============


// reference count.
class RefCount{
private:
    int rcount;
public:
    RefCount(): rcount(0){}

    void incREfCount(){ rcount++; }
    int decRefCount(){ return --rcount; }
    int getRefCount(){ return rcount; }

     virtual ~RefCount(){}
};

#endif // MYPOINTER

