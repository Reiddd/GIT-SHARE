#include <iostream>
#include <vector>
#include <future>
#include <boost/lexical_cast.hpp>
#include <chrono>
#include "threadpool.h"

using namespace std;

int main()
{
    ThreadPool pool(4);
    vector<future<string>> futures;

    for(int i=0;i<10;i++)
        futures.push_back(pool.post(
                              [](int i){
            cout<<"function "<<i<<" executing.\n"<<endl;
            return "function "+boost::lexical_cast<string>(i)+" done.";},
        i));

    this_thread::sleep_for(chrono::milliseconds(1000));

    for(int i=0;i<futures.size();i++){
        cout<<futures[i].get()<<'\n'<<endl;
    }

    return 0;
}

