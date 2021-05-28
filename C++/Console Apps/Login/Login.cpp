#include <iostream>
using namespace std;

int main() {
    char str[] = "Hello C++";
    char name[50];
    char str2[] = "Unable to read...";

    // Standard Output Stream
    cout << "Value of str is: " << str << endl;

    // Standard Output Stream
    cout << "Please enter your name: ";
    cin >> name;
    cout << "Your name is; " << name << endl;

    // Standard Error Stream
    cerr << "Error Message: " << str2 << endl;

    // Standard Log Stream (clog)
    clog << "Error Message: " << str2 << endl;

    return 0;
}