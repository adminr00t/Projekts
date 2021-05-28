#include <iostream>
using namespace std;

class Box {
    public:
        Box(){
            cout << "Constructor Called" << endl;
        }
        ~Box(){
            cout << "Destructor Called" << endl;
        }
};

int main(){
    //dynamic allocation for simpple data types
    double* pvalue = NULL; //Pointer initialized with null
    pvalue = new double;

    *pvalue = 29494.99; //Stores value at requested address

    cout << "Value of pvalue: " << *pvalue << endl;

    delete pvalue;

    //dynamic allocation for objects
    Box* myBoxArray = new Box[4];
    delete [] myBoxArray;


    return 0;
}