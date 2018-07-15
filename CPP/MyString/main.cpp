#include <iostream>
#include "mystring.h"

using namespace std;

int main()
{
    char str[4] = {'1','2','3','\0'};
    MyString s1(str);
    MyString s2(str);


    cout<< "s1 == " << s1
        << '\n'
        << "s2 == " << s2
        << endl;


    cout<< "length = " << s1.size()
        << '\n'
        << "s1 == s2 is " << (s1 == s2)
        << '\n'<<endl;


    s1.insert(2, s2);
    cout<<"s1.insert(1, s2) returns: " << s1<<'\n'<<endl;


    s2 = s1.substr(2, 2);
    cout<<"s1.substr() returns: " << s2<<endl;

    return 0;
}

