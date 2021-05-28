#include <iostream>
using namespace std;

// base class
class Shape{
    public:
        // pure virtual function giving interface framework
        virtual int getArea() = 0;
        void setWidth(int w) {
            width = w;
        }

        void setHeight(int h){
            height = h;
        }

    protected:
    int width;
    int height;
};

// derived classes
class Rectangle: public Shape{
    public:
        int getArea(){
            return (width * height);
        }
};

class Triangle: public Shape{
    public:
        int getArea(){
            return (width * height)/2;
        }
};

int main (void){
    Rectangle rect;
    Triangle tri;

    rect.setWidth(5);
    rect.setHeight(7);

    // print area
    cout << "Rectangle Area: " << rect.getArea() << endl;


    tri.setWidth(5);
    tri.setHeight(7);

    // print area
    cout << "Triangle Area: " << tri.getArea() << endl;

    return 0;
}