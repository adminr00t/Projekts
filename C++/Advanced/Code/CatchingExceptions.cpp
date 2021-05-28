#include <iostream>
#include <exception>
using namespace std;

//defining new exception
struct CustomException: public exception{
    const char * what() const throw(){
        return "custom exception";
    }
};

double division(int a, int b){
    if (b == 0){
        throw "Division by Zero Condition!";
    }
    return (a/b);
}

int main(){
    int x = 50;
    int y = 0;
    double z = 0;

    try{
        z  = division(x,y);
        cout << z << endl;
    }catch (const char* msg){
        cerr << msg << endl;
    }

    //catching custom exception
    try{
        throw CustomException(); 
    } catch(CustomException& e){
        std::cout << "Custom Exception Caught" << std::endl;
        std::cout << e.what() << std::endl;
    } catch(std::exception& e){
        // other 
    }

    return 0;

}