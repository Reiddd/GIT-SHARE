#include <iostream>
#include <boost/pool/pool.hpp>

using namespace std;

int main()
{
    // the argument is the size of the object not the pool.
    boost::pool<> pool(sizeof(int));

    // boost::pool::malloc return a void* pointer, so we need to cast it.
    // static_cast
    int *p = static_cast<int*>(pool.malloc());

    if(p == nullptr)
        cout<<"your malloc failed."<<endl;
    else
        cout<<"your malloc is successful."<<endl;

    return 0;
}

