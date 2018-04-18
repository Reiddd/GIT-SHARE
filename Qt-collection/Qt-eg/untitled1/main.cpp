#include <iostream>

using namespace std;

int main()
{
    for(int i=0;i<10;i++){
        static int j = i;
        cout<<j<<endl;
    }
}

