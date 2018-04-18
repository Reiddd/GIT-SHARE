#include <iostream>
#include <boost/timer.hpp>

using namespace std;
using namespace boost;

int main()
{
    timer t;

    //timer::elapsed_max()'s unit is hour.
    cout<< "max time span: " << t.elapsed_max() << "h" <<endl;

    //timer::elapsed_min()'s unit is second.
    cout<< "min time span: " << t.elapsed_min() << "s" <<endl;

    //timer::elapsed()'s unit is second.
    cout<< "current elapsed time: " << t.elapsed() << "s" <<endl;

    return 0;
}

