#include <iostream>
#include <iomanip> //IO manipulation
using namespace std;
using std::setw; //sets field width to be used on output operations

int main(){
    int n[10]; // array with 10 elements

    // initialize elements of array n to 0
    for(int i = 0; i < 10; i++){
        n[i] = i + 100; //set element at location i to i + 100
    }
    cout << "Element" << setw(13) << "Value" << endl;

    // output each array element
    for (int j = 0; j < 10; j++){
        cout << setw(7) << j << setw(13) << n[j] << endl;
    }

    return 0;


}




