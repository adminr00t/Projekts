#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    // Storage Arrays
    string firstNames[6];
    string lastNames[6];
    string courses[6];
    string grades[6] = {"HD", "F", "HD", "A", "F", "C"};
    float marks[6];

    // Data Collection
    for (int i = 0; i < 6; i++)
    {
        cout << "Please enter student name:" << endl;

        // Stores input into names array
        cin >> firstNames[i] >> lastNames[i];

        cout << "Please enter Course and Mark (one decimal point):" << endl;

        // Stores the Course into courses array and marks into marks array
        cin >> courses[i] >> marks[i];
    }

    // Top Scale
    cout << "123456789012345678901234567890123456789012345" << endl;

    // Final Output
    for (int i = 0; i < 6; i++)
    {
        cout << left << setprecision(1
        ) << fixed << setw(14) << firstNames[i] + " " + lastNames[i] << setw(10) << courses[i] << setw(10) << marks[i] << setw(10) << grades[i] << setw(10) << endl;
    }

    // Bottom Scale
    cout << "123456789012345678901234567890123456789012345" << endl;

    return 0;
};