#include <iostream>
// using namespace std;

// function declaration 
void func(void);
int count;
extern void write_extern();

// static int count = 10; //global variable


main(){
    // auto storage class
    // int mount;
    // auto int month; can only be used in functions

    // register storage class
    // register int miles;

    // First Function
    // while(count--){
    //     func();
    // }

    // Second Function
    count = 5;
    write_extern();

    // return 0;   
}

void func( void ) {
   static int i = 5; // local static variable
   i++;
   std::cout << "i is " << i ;
   std::cout << " and count is " << count << std::endl;
}