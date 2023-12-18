//
// Created by oleks on 09.12.2023.
//

#ifndef LAB4TEST_CSTRING_H
#define LAB4TEST_CSTRING_H


#include <iostream>
#include <string>

using namespace std;

class CString {
private:
    string value;
public:
    CString();
    CString(string newValue);
    void operator=(const CString& other);
    void operator=(const string& other);
    bool operator==(const string& other);
    bool operator==(const CString& other);
    CString operator+(const CString& other);
    CString operator-(const CString& other);
    CString operator*(const CString& other);
    CString operator/(const CString& other);
    string toString();
};



#endif //LAB4TEST_CSTRING_H
