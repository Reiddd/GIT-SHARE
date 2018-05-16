#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // vector<bool> test1{4, false};     error : constant expression evaluates to 4 which cannot be narrowed to type 'bool' [-Wc++11-narrowing]
    vector<bool> test2(4, false);
    for(auto elem : test2)
        cout<< elem << '\t';
    cout<< endl;

    long double pi = 3.1415926536;
    // int a{pi};     error : narrowing conversion required
    int a(pi);
    cout<< a;

    return 0;
}
