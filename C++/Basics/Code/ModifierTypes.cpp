#include <iostream>
using namespace std;

// shows the difference between short and unsigned ints
int main(){
    short int i; //short signed int
    short unsigned int j; //short unsigned int

    j = 50000;
    i=j;

    cout << i << " " << j;

    return 0;
    // difference due to bit pattern of short unsigned int is interpreted as -15,536
}