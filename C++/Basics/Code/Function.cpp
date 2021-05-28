#include <iostream> 
using namespace std;

// function declaration
int max(int num1, int num2);

// main function of the program
int main(){
 max(200, 331);
 return 0;
}


// function returning max of 2 numbers
int max(int num1, int num2) {
    int result;
    if (num1 > num2){
        result = num1;
    }
    else
    {
        result = num2;
    }
    
    cout << "Max value is: " << result << endl;
    return 0;
}