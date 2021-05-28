#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main(){

    // C-Style Character String
    char greeting[6] = {'H', 'e','l','l','o','\0'};
    cout << "Greeting message: ";
    cout << greeting << endl;

// for C-Style
    // char str1[10] = "hello";
    // char str2[10] = "world";
    // char str3[10];
    // int len;

    // copying str1 into str3
    // strcpy(str3, str1);
    // cout << "String 3: " << str3 << endl;

    // link string 1 and 2
    // strcat(str1, str2);
    // cout << "String 1 and 2: " << str1 << endl;

    // length of string 1 after linking
    // len = strlen(str1);
    // cout << "Length of String 1 after linking String 2: " << len << endl;

// using String Class

    // for String Class
    string str1 = "Hello";
    string str2 = "World";
    string str3;
    int len;

    // copy str1 into str3
    str3 = str1;
    cout << "String 3 is: " << str3 << endl;

    // link String 1 and String 2
    str3 = str1 + str2;
    cout << "String 3 is: " << str3 << endl;

    // Total Legnth of String 3
    len = str3.size();
    cout << "String 3 Length is: " << len << endl;

    return 0;

}