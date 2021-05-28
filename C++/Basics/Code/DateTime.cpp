#include <iostream>
#include <ctime>
using namespace std;

int main(){
    // current date/time based on current system
    time_t now = time(0);

    // convert now to srting form
    char* dt = ctime(&now);

    cout << "Local Date and Time: " << dt << endl;

    // convert now to tm struct for UTC
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    cout << "UTC Date/Time: " << dt << endl;

    // using tm structure
    cout << "Seconds since Jan 1 1970: " << now << endl;

    tm *ltm = localtime(&now);

    // print various components of tm strucutre
    cout << "Year: " << 1900 + ltm->tm_year << endl;
    cout << "Month: " << 1 + ltm->tm_mon<< endl;
    cout << "Day: " << ltm->tm_mday << endl;
    cout << "Time: " << 5+ltm->tm_hour << ":";
    cout << ltm->tm_sec << endl;

    return 0;
}