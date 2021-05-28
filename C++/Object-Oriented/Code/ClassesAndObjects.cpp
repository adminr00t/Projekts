#include <iostream>
using namespace std;

class Box {
    public:
    double length; //Length of Box
    double breadth; //Breadth of Box
    double height; // Height of Box
};

int main (){
    // Declare the boxes
    Box box1;
    Box box2; 
    double volume = 0.0; // store the volume of a box

    // Box 1 specs
    box1.height = 9;
    box1.breadth = 10.5;
    box1.length = 13.7;

    // box 2 specs
    box2.length = 20;
    box2.height = 3;
    box2.breadth = 15;

    //Volume of box 1
    volume = box1.height * box1.length * box1.breadth;
    cout << "Volume of Box 1: " << volume << endl;

    // Volume of Box 2
    volume = box2.height * box2.length * box2.breadth;
    cout << "Volume of Box 2: " << volume << endl;
    return 0;
}