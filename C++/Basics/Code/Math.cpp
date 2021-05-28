#include <iostream> // allows input/output
#include <cmath> //math functions
#include <cstdlib> //c standard library, srand, rand
#include <time.h> // time

using namespace std;

int main() {

    // number definition
    short s;
    int i;
    long l;
    float f;
    double d;

    // number assignments
    s = 10;
    i = -90;
    l = 100;
    f = 420.6969;
    d = 696969.420;

    // number printing
    cout << "Short is: " << s << endl;
    cout << "Int is: " << i << endl;
    cout << "Long is: " << l << endl;
    cout << "Float is: " << f << endl;
    cout << "Double is: " << d << endl;
    cout << "\n" << endl;

    cout << "The Sine of d is: " << sin(d) << endl;
    cout << "Absolute Value of i is: " << abs(i) << endl;
    cout << "Floor of d is: " << floor(d) << endl;
    cout << "The Square Root of F is: " << sqrt(f) << endl;
    cout << "D to the Power of 2 is: " << pow(d,2) << endl;

    // random number generator
    int x, j;

    // set the seed
    srand((unsigned)time(NULL));

    // generate 10 rando numbers
    for(x = 0; x < 10; x++){
        j = rand();
        cout << "Random Number is: " << j << endl;
    }

    return 0;
}