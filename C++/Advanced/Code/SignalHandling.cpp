#include <iostream>
#include <csignal>
#include <Windows.h>
using namespace std;

void signalHandler(int signum){
    //clean up and close
    cout << "Interupt signal (" << signum << ") received.\n";

    // terminate
    exit(signum);
}

int main(){
    int i = 0;
    //register signal SIGINT and signal handeler
    signal(SIGINT, signalHandler);

    while(++i){
        cout << "Goint to sleep..." << endl;
        if (i == 3){
            raise(SIGINT);
        }
        Sleep(1000);
    }
    return 0;
}