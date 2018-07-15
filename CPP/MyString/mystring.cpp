#include "mystring.h"
#include <string.h>
#include <assert.h>

// constructor
MyString::MyString(const char* str=0){
    length = strlen(str);
    data = new char[length+1];
    data[length] = '\0';
    strcpy(data, str);
}


MyString::MyString(const MyString& str){
    length = str.size();
    data = new char[str.size()+1];
    data[length] = '\0';
    strcpy(data, str.c_str());
}


MyString::MyString(const MyString&& str){
    length = str.size();
    data = new char[str.size()+1];
    data[length] = '\0';
    strcpy(data, str.c_str());
}

// -------------
// -------------

// destructor
MyString::~MyString(){
    delete[] data;
}

// -------------
// -------------

// methods
size_t MyString::size() const{
    return length;
}


MyString MyString::substr(int begin, int len=-1){
    if(len == -1){
        if(begin >= length)
            return MyString();
        len = length - begin;
    }

    if(begin+len >= length)
        len = length - begin;

    char* temp = new char[len+1];
    temp[len] = '\0';
    for(int i=0;i<len;i++)
        temp[i] = data[begin+i];

    return MyString(temp);
}


char* MyString::c_str() const{
    return data;
}


int MyString::find(const char c)const{
    for(int i=0;i<length;i++)
        if(data[i] == c)
            return i;
    return -1;
}


bool MyString::empty(){
    return length == 0;
}


void MyString::insert(const size_t index, const MyString& source){
    assert(index>=0 && index<=length);

    length += source.size();

    char* temp1 = (this->substr(0, index)).c_str();
    char* temp2 = (this->substr(index)).c_str();
    delete[] data;
    data = new char[length+1];
    data[length] = '\0';

    strcpy(data, temp1);
    strcat(data, source.c_str());
    strcat(data, temp2);
}

// -------------
// -------------

// override
bool operator==(const MyString& left, const MyString& right){
    return strcmp(left.data, right.data) == 0;
}


bool operator!=(const MyString& left, const MyString& right){
    return strcmp(left.data, right.data) != 0;
}


bool operator<(const MyString& left, const MyString& right){
    return strcmp(left.data, right.data) < 0;
}


bool operator<=(const MyString& left, const MyString& right){
    return strcmp(left.data, right.data) <= 0;
}


bool operator>(const MyString& left, const MyString& right){
    return strcmp(left.data, right.data) > 0;
}


bool operator>=(const MyString& left, const MyString& right){
    return strcmp(left.data, right.data) >= 0;
}


char& MyString::operator[](const size_t index){
    assert(index>=0 && index<length);

    return data[index];
}


MyString& MyString::operator=(const MyString& str){
    delete[] data;
    data = new char[str.size()+1];
    data[str.size()] = '\0';
    strcpy(data, str.c_str());

    return *this;
}


MyString& MyString::operator+=(const MyString& str){
    length += str.size();
    char* temp = data;
    delete[] data;
    data = new char[length];
    strcpy(data, temp);
    strcat(data, str.c_str());
}


ostream& operator<<(ostream& os, MyString& str){
    os<<str.c_str();
    return os;
}
