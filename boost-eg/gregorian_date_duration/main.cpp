#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;

int main()
{
    cout<< "boost::gregorian::date_duration has some more useful typedef: \n"
        << "\tboost::gregorian::days(3) returns " << boost::gregorian::days(3) <<'\n'
        << "\tboost::gregorian::weeks(3)" <<'\n'
        << "\tboost::gregorian::years(3)" <<'\n'
        <<endl;


    cout<< "boost::gregorian::date_duration supports +, -, *, / : \n"
        << "\tboost::gregorian::days(1) + boost::gregorian::days(2) == " << boost::gregorian::days(1) + boost::gregorian::days(2) <<'\n'
        << "\tboost::gregorian::weeks(1) + boost::gregorian::days(1) == " << boost::gregorian::weeks(1) + boost::gregorian::days(1) <<'\n';
    
    
    boost::gregorian::months m = boost::gregorian::months(6);
    boost::gregorian::years y = boost::gregorian::years(6);
    cout<< "m.number_of_months() == " << m.number_of_months() <<'\n'
        << "y.number_of_years() == " <<y.number_of_years() <<'\n'
        <<endl;
    
    
    boost::gregorian::date d = boost::gregorian::day_clock::local_day();
    boost::gregorian::days duration = boost::gregorian::weeks(1) + boost::gregorian::days(4);
    cout<< "boost::gregorian::date_duration + boost::gregorian::date : \n"
        << d + duration
        <<endl;

    return 0;
}

