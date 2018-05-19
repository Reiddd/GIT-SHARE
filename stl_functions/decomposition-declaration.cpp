#include <iostream>
#include <tuple>
#include <vector>
#include <array>
#include <utility>
#include <boost/lexical_cast.hpp>

struct S{
    S(int i, double f, std::string str): I(i), F(f), STR(str){}
    int I;
    double F;
    std::string STR;
};

/* 1. auto [a1, a2, ... , an] == <pair, tuple, array, vector, struct>, the number of arguments must matches exactly the number of arguments in the container.
   2. can't be auto constexpr [a1, a2, ... , an] */

int main()
{
    // decomposition declaration with std::pair.
    {
        std::cout<< "from pair : " <<std::endl;
        auto const [a1, a2] = std::pair<int, float>{1, 3.14};
        std::cout<< "a1, a2 == " << a1 << ", " << a2 <<std::endl;
        std::cout<< '\n';
    }


    // decomposition declaration with std::tuple.
    {
        std::cout<< "from tuple : " << std::endl;
        auto [a1, a2, a3] = std::tuple<int, float, std::string>{1, 3.14, "string_in_tuple"};
        std::cout<< "a1, a2, a3 == " << a1 << ", " << a2 << ", " << a3 <<std::endl;
        std::cout<< '\n';
    }

    {
        std::cout<< "from array : " <<std::endl;
        auto const [a1, a2, a3] = std::array<int, 3>{1, 2, 3};
        std::cout<< "a1, a2, a3 == " << a1 << ", " << a2 << ", " << a3 <<std::endl;
        std::cout<< '\n';
    }


    // decomposition declaration with self-designed struct.
    {
        std::cout<< "from struct : " <<std::endl;
        std::vector<S> vec; vec.reserve(5);
        for(int i=0; i<5; i++)
            vec.emplace_back(S{i, (double)(100-i)/10.0, "string-"+boost::lexical_cast<std::string>(i)});
        for(auto const& [I, F, STR] : vec)
            std::cout<< "I, F, STR == " << I << ", " << F << ", " << STR <<std::endl;
        std::cout<< '\n';
    }

    return 0;
}
