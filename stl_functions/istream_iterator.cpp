#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

template<typename T>
size_t wordcount(T &is){
    return distance(istream_iterator<string>(is), {});
}

int main(int argc, char** argv)
{
    size_t word_count;

    if(argc == 2){
        ifstream ifs{argv[1]};
        word_count = wordcount(ifs);
    }
    else
        word_count = wordcount(cin);

    cout<< "there are " << word_count << "words." <<endl;

    return 0;
}
