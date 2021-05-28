#include <iostream>
using namespace std;

// variable declaration
extern int a, b;
extern int c;
extern float f;

// global variable definintion
int e;

int main(){
    // local variable definition
    int a, b;
    int c;
    float f;

    // actual initialization
    a = 10;
    b = 20;
    c = a + b;

    cout << c << endl;

    f = 70.0/30.0;
    cout << f << endl;
    return 0;

}