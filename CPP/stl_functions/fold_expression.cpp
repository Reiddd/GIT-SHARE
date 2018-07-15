#include <iostream>

using namespace std;

template<typename... T>
auto add(T... t)->decltype((t + ...)){
    return (t + ...);
}

int main()
{
    cout<< "add(1, 2, 3, 4, 5, 6 ,7, 8) == "
        << add(1, 2, 3, 4, 5, 6, 7, 8)
        <<endl;

    cout<< "add(\"str1 \", \"str2 \", \"str3 \") == "
        << add(string("str1 "), string("str2 "), string("str3 "))
        <<endl;

    return 0;
}
