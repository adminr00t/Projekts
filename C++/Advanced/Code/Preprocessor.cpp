#include <iostream>
using namespace std;

#define PI 3.14159

//function like macros
#define MIN(a, b) (((a) < (b)) ? a : b)

//conditional compilation
#define DEBUG

//the # and ## operators
#define MKSTR(x) #x
#define concat(a, b) a##b

int main()
{
    int i, j;
    int xy = 100;

    i = 100;
    j = 30;

#ifdef DEBUG
    cerr << "Trace: Inside main function" << endl;
#endif

    cout << "PI: " << PI << endl;
    cout << "The minimum is: " << MIN(i, j) << endl;

    cout << MKSTR(HELLO WORLD) << endl;
    cout << concat(x, y);

    //Predefined Macros
    cout << "Line number: " << __LINE__ << endl;
    cout << "File: " << __FILE__ << endl;
    cout << "Date: " << __DATE__ << endl;
    cout << "Time: " << __TIME__ << endl;

#ifdef DEBUG
    cerr << "Trace: Coming out of main function" << endl;
#endif

    return 0;
}