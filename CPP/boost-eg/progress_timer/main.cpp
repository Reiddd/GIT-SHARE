#include <iostream>
#include <boost/progress.hpp>
#include <time.h>

using namespace std;
using namespace boost;

int main()
{
    progress_timer t;

    //boost::progress_timer has same functions as boost::timer
    cout<< "use boost::progress_timer as boost::timer:\nboost::progress_timer::elapsed() returns "
        << t.elapsed() <<endl;

    //boost::progress_timer can also be used in a more easily way
    {
        progress_timer t;
        sleep(4);
        cout<< "with the help of {}, when the progress_timer is destroyed, it will output the time span automaticlly." <<endl;
    }

    sleep(4);
    cout<< "it works even when the main is end:" <<endl;

    return 0;
}

