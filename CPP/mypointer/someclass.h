#ifndef SOMECLASS
#define SOMECLASS

#include "mypointer.h"
#include <iostream>

using namespace std;

class SomeClass:public RefCount{
public:
    SomeClass(){ cout<< "Construct a class object." <<endl; }
    ~SomeClass(){ cout<< "descruct a class object." <<endl; }
};

#endif // SOMECLASS

