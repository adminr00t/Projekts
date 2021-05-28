#include <iostream>
using namespace std;

class Shape{
    protected:
        int width, height;
    
    public:
        Shape(int a = 0, int b = 0){
            width = a;
            height = b;
        }
        virtual int area(){
            cout << "Parent Shape Area: " << endl;
            return 0;
        }
};

class Rectangle: public Shape{
    public:
        Rectangle(int a = 0, int b = 0):Shape(a,b){}

        int area(){
            cout << "Rectangle Area: " << endl;
            return (width * height);
        }
};

class Triangle: public Shape{
    public:
        Triangle(int a = 0, int b = 0):Shape(a,b){}

        int area(){
            cout << "Triangle Area: " << endl;
            return ((width * height)/2);
        }
};

int main(){
    Shape *shape;
    Rectangle rec(10,7);
    Triangle tri(10,5);

    // store address of Rectangle
    shape = &rec;

    // call rectangle area
    shape->area();

    // sotre address of Triangle
    shape = &tri;

    // call Triangle Area
    shape->area();

    return 0;
}
