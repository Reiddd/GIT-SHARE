#include <iostream>
#include <boost/xpressive/xpressive.hpp>

using namespace std;

int main()
{
    cout << "basic_regex constructs regex objects" <<endl
         << "typedef basic_regex<string::const_iterator> sregex" <<endl
         << "typedef basic_regex<char const *> cregex\n" <<endl;


    boost::xpressive::sregex pattern1 = boost::xpressive::sregex::compile("^[0-9]{3}-[0-9]{4}-[0-9]{4}$");
    boost::xpressive::smatch result1;
    bool matched1 = boost::xpressive::regex_match((string)"137-7617-1091", result1, pattern1);
    cout<< "1. boost::xpressive::regex_match(\"137-7617-1091, pattern1\") == "
        << matched1 <<'\n'
        << "2. boost::xpressive::regex_match(\"137-7617-1091\", result1, pattern1) == "
        << matched1 <<'\n'
        << "matched result is "
        << result1[0]
        <<'\n'<<endl;


    boost::xpressive::sregex pattern2 = boost::xpressive::sregex::compile((string)"([0-9]{3}) ([0-9]{4}) ([0-9]{4})");
    boost::xpressive::smatch result2;
    bool matched2 = boost::xpressive::regex_search((string)"this is my phone number: 137 7617 1091", result2, pattern2);
    cout<< "1. boost::xpressive::regex_search(\"this is my phone number: 137 7617 1091\", pattern2) == "
        << matched2 <<'\n'
        << "2. boost::xpressive::regex_search(\"this is my phone number: 137 7617 1091\", result2, pattern2) == "
        << matched2 <<'\n'
        << "matched result is "
        << result2[0] <<'\n'
        << "it could even access sub matches:\n"
        << '\t' << result2[1] << '\n'
        << '\t' << result2[2] << '\n'
        << '\t' << result2[3] << '\n'
        <<endl;


    cout<< "boost::xpressive::regex_replace:\n\t"
        << boost::xpressive::regex_replace((string)"this is my phone number: 137 7617 1091", pattern2, "xxx-xxxx-xxxx")
        <<endl;

    return 0;
}

