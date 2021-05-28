#include <iostream>
using namespace std;

class printData{
    public:
        void print(int i) {
            cout <<"Printing Integer: " << i << endl;
        }
        void print(double f){
            cout <<"Printing Float: " << f << endl;
        }
        void print(char* c){
            cout <<"printing Character: " << c << endl;
        }
};

class Box{
    public:
        double getVolume(void){
            return length * breadth * height;
        }

        void setLength(double len){
            length = len;
        }

        void setBreadth(double bre){
            breadth = bre;
        }

        void setHeight(double hei){
            height = hei;
        }

        // overload + operator to add two Box objects
        Box operator+(const Box& b){
            Box box;
            box.length = this->length + b.length;
            box.breadth = this->breadth + b.breadth;
            box.height = this->height + b.height;
            return box;
        }

    private:
        double length; 
        double breadth;
        double height;
};



int main(){
    printData pd;

    // Print Int
    pd.print(5);

    // Print Float
    pd.print(69.420);

    // Print Char
    // pd.print("c");

    // Box
    Box box1;
    Box box2;
    Box box3;
    double volume = 0.0;

    // Box 1 specs
    box1.setLength(6);
    box1.setBreadth(7);
    box1.setHeight(5);

    // Box 1 specs
    box2.setLength(12);
    box2.setBreadth(13);
    box2.setHeight(10);

    // box 1 volume
    volume = box1.getVolume();
    cout << "Volume of Box 1: " << volume << endl;

    // Box 2 volume
    volume = box2.getVolume();
    cout << "Volume of Box 2: " << volume << endl;

    // Box 3 Volume 
    box3 = box1 + box2;
    volume = box3.getVolume();
    cout << "Volume of Box 1 and 2: " << volume << endl;


    
    return 0;
}