#include <iostream>
using namespace std;

// using #define
// #define LENGTH 10
// #define WIDTH 5
// #define NEWLINE '\n'

int main(){
    // using const
    const int LENGTH = 10;
    const int WIDTH = 5;
    const char NEWLINE = '\n';
    int area;

    area = LENGTH * WIDTH;
    cout << area;
    cout << NEWLINE;
    return 0;
}