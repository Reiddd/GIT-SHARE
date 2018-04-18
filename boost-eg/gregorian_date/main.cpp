#define BOOST_ERROR_CODE_HEADER_ONLY

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost::gregorian; // be careful about the namespace

int main()
{
    // construct an date object
    date d1;
    cout<< "boost::gregorian::date() returns a 'not_a_date_time' object:\nd1 == "
        << d1
        <<"\n"<<endl;


    date d2(2018, 3, 7);
    cout<< "boost::gregorian::date(2018, 3, 7) constructs from int:\nd2 == "
        << d2
        <<"\n"<<endl;


    date d3(2018, Jan, 7);
    cout<< "boost::gregorian::date(2018, Mar, 7) constructs from int+enum:\nd3 == "
        << to_iso_extended_string(d3)
        <<"\n"<<endl;


    date d4(d2);
    cout<< "boost::gregorian::date(another_date_object) constructs from copy:\nd4 == "
        << to_iso_extended_string(d4)
        <<"\n"<<endl;


    date d5 = from_string("2018-3-7");
    cout<< "boost::gregorian::date = from_string(\"YYYY-MM-DD\") constructs from from_string() 1:\nd5 == "
        << to_iso_extended_string(d5)
        <<"\n"<<endl;


    date d6 = from_string("2018/3/7");
    cout<< "boost::gregorian::date = from_string(\"YYYY/MM/DD\") constructs from from_string() 2:\nd6 == "
        << to_iso_extended_string(d6)
        <<"\n"<<endl;


    cout<< "construct special date:\n\t"
        << "boost::gregorian::date(neg_infin) == " << date(neg_infin) <<"\n\t"
        << "boost::gregorian::date(pos_infin) == " << date(pos_infin) <<"\n\t"
        << "boost::gregorian::Date(not_a_date_time) == " << date(not_a_date_time) <<"\n\t";

// --------------

    // boost::gregorian::day_clock::local_clock()
    // boost::gregorian::day_clock::universal_clock()
    cout<< "boost::gregorian::day_clock::local_clock() == "
        << day_clock::local_day()
        <<"\n"<<endl;
    cout<< "boost::gregorian::day_clock::universal_day() == "
        << day_clock::universal_day()
        <<"\n"<<endl;

// --------------

    cout<< "boost::gregorian::date::year(): "
        << d2.year()
        <<'\n'<<endl;

    cout<< "boost::gregorian::date::month(): "
        << d2.month()
        <<'\n'<<endl;

    cout<< "boost:gregorian::date::day(): "
        << d2.day()
        <<'\n'<<endl;

    return 0;
}

