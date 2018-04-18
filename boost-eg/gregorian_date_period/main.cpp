#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;

int main()
{
    cout<< "boost::preporian::date_period is in [begin, end) form\n"<<endl;
    
    
    boost::gregorian::date_period dp = boost::gregorian::date_period(boost::gregorian::day_clock::local_day(),
                                                                     boost::gregorian::days(4));
    cout<< "boost::gregorian::date_period(boost::gregorian::day_clock::local_day(), boost::gregorian::days(4))"
        << dp
        <<'\n'<<endl;

    
    boost::gregorian::day_iterator it_d = boost::gregorian::day_iterator(boost::gregorian::day_clock::local_day());
    cout<< "boost::gregorian::day_iterator overload operator++, but only ++it, not it++"<<endl;
    for(int i=0;i<5;i++){
        cout<< "\t" << *it_d << '\n';
        ++it_d;
    }
    cout<<'\n';


    boost::gregorian::week_iterator it_w = boost::gregorian::week_iterator(boost::gregorian::day_clock::local_day());
    cout << "and boost::gregorian::week_iterator" <<endl;
    for(int i=0;i<5;i++){
        cout<< '\t' <<*it_w << '\n';
        ++it_w;
    }
    cout<<'\n';
    
    return 0;
}

