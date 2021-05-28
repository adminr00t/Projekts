#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    char str[] = "Hello C++";
    char name[50];
    char str2[] = "Unable to read...";
    int x = 17;
    int y = 7;
    float z = 7623.9674;
    x %=y;

    // Standard Output Stream
    cout << "Value of str is: " << str << endl;

    // Standard Output Stream
    cout << "Please enter your name: ";
    // cin >> name;
    cout << "Your name is; " << name << endl;

    // Standard Error Stream
    cerr << "Error Message: " << str2 << endl;

    // Standard Log Stream (clog)
    clog << "Error Message: " << str2 << endl;

    cout << fixed << showpoint;
    cout << setprecision(2);
    cout << x << " " << '\n' << y << " " << z << endl;

    return 0;
}