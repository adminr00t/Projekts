#include <iostream>
using namespace std;

// Base Shape Class
class shape{
    public:
        void setWidth(int w){
            width = w;
        }
        void setHeight(int h){
            height = h;
        }

        protected:
        int width;
        int height;
};

// Base PaintCost Class
class paintCost {
    public:
    int getCost(int area){
        return area * 70;
    }
};

// Derived Class
class Rectangle: public shape, public paintCost{
    public:
        int getArea(){
            return (width * height);
        }
};

int main(void){
    Rectangle rect;
    int area;

    rect.setWidth(5);
    rect.setHeight(7);
    area = rect.getArea();

    cout << "Rectangle Area: " << rect.getArea() << endl;
    cout << "Cost of Paint: $" << rect.getCost(area) << endl;

    return 0;
}