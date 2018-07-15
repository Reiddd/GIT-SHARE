#include <iostream>
#include <boost/pool/object_pool.hpp>

using namespace std;

struct demo_class
{
public:
    int a, b, c;
    demo_class(int x, int y, int z):a(x), b(y), c(z){}
};

int main()
{
    boost::object_pool<demo_class> pool;

    auto p = pool.malloc();
    cout << "pool.is_from(p) == "
         << pool.is_from(p)
         <<'\n'<<endl;


    cout<< "boost::object_pool<elem_type>::malloc return elem_type*, but it hasn't be initialized.\n"<<endl;


    p = pool.construct(7, 8, 9);
    cout<< "boost::object_pool<elem_type>::construct initialize an instance\n"
        << "\tp->a == 7 is " << (p->a == 7) <<'\n'
        << "\tp->b == 8 is " << (p->b == 8) <<'\n'
        << "\tp->c == 9 is " << (p->c == 9) <<'\n'
        << endl;

    return 0;
}

