#include <iostream>
using namespace std;

int main(){
    int var = 20;
    int var1;
    char var2[10];
    int *ip;

    cout << "Address of Variable 1: " << &var1 << endl;
    cout << "Address of Variable 2: " << &var2 << endl;

    ip = &var;
    cout << "Value of Variable: " << var << endl;
    
    // address of stored variable
    cout << "Address of Variable: " << ip << endl;

    // value of address of variable
    cout << "Value of Variable Address: " << *ip << endl;

    return 0;
}