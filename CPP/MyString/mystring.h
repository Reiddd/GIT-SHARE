#ifndef MYSTRING
#define MYSTRING

#include <iostream>

using namespace std;

class MyString{
private:
    size_t length;
    char* data;
public:
    // constructor
    MyString(const char*);       // constructor by c-string
    MyString(const MyString&);   // constructor by reference
    MyString(const MyString&&);  // constructor by right-value-reference


    // destructor
    ~MyString();


    // methods
    size_t size() const;
    MyString substr(int, int);
    char* c_str() const;
    int find(const char) const;
    bool empty();
    void insert(const size_t, const MyString&);


    // override
    friend bool operator== (const MyString&, const MyString&);
    friend bool operator!= (const MyString&, const MyString&);
    friend bool operator< (const MyString&, const MyString&);
    friend bool operator<= (const MyString&, const MyString&);
    friend bool operator> (const MyString&, const MyString&);
    friend bool operator>= (const MyString&, const MyString&);

    char& operator[](const size_t);

    MyString& operator= (const MyString&);
    MyString& operator+= (const MyString&);

    friend ostream& operator<<(ostream&, MyString&);
};

#endif // MYSTRING

