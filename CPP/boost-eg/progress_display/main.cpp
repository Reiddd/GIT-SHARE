#include <iostream>
#include <vector>
#include <time.h>
#include <boost/progress.hpp>

using namespace std;
using namespace boost;

int main()
{
    vector<short> container(100,0);
    progress_display pd(container.size());

    for(int i=0;i<container.size();i++){
        container[i] = i;
        sleep(1);
        ++pd;
    }

    return 0;
}

