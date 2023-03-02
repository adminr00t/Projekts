#include <iostream>
using namespace std;

int main(){
    int n;
    int F0 = 0;
    int F1 = 1;
    int numThree;
    string suffix;

    cout << "Enter nth number: " << endl;
    cin >> n;

    if (n % 10 == 1){
        suffix = "st";
    }else if (n % 10 == 2){
        suffix = "nd";
    }else if (n % 10 == 3){
        suffix = "rd";
    }else{
        suffix = "th";
    }

    cout << "Fibonacci Sequence to the " << n << suffix << " number\n" << endl;

    for(int i = 0; i < n; i++){
       if(i == 0){
        cout << F0 << ", ";
        continue;
       }
       if(i == 1){
        cout << F1 << ", ";
        continue;
       }


       numThree = F0 + F1;
       F0 = F1;
       F1 = numThree;

       if(i == n - 1){
        cout << numThree << endl;
       }else{ 
        cout << numThree << ", ";
       }
    }
}