#include <iostream>
using namespace std;

// first namespace
namespace first{
    void func(){
        cout << "Inside first namespace" << endl;
    }


// second namespace
namespace second{
    void func(){
        cout << "Inside second namespace" << endl;
    }
}
}

// avoid using this
using namespace first::second;

int main(){
    // calls from first namespace
    // first::func();

    // calls from second namespace
    // second::func();

    func();
    return 0;
}