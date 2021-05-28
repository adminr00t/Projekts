#include <iostream>

extern int count;

void write_extern(void){
    std::cout << "count is " << count << std::endl;
}

// to write exe for two files:
// cmd: g++ file1.cpp file2.cpp -o exeName
