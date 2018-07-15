#include <iostream>
#include <utility>      // std::piecewise_construct
#include <tuple>

using namespace std;

struct Foo{
    Foo(tuple<int, float>){
        cout<< "construct a Foo from a tuple." <<endl;
    }

    Foo(int, float){
        cout<< "construct a Foo from an int and a float." <<endl;
    }
};

int main()
{
    tuple<int, float> parameters(1, 3.14);
    pair<Foo, Foo> p1(t, t);
    pair<Foo, Foo> p2(piecewise_construct, t, t);

    return 0;
}
