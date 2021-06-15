#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    // Storage Arrays
    string names[6];
    string courses[6];
    string grades[6];
    string trashArray[6];
    float marks[6];

    //Declarations
    ifstream fileRead;

    //open file
    fileRead.open("data.txt");

    // Data Extraction
    for (int j = 0; j < 6; j++)
    {
        getline(fileRead, names[j]);
        getline(fileRead, courses[j]);
        fileRead >> marks[j];
        getline(fileRead, trashArray[j]);
        fileRead.ignore(2, '\n');
    }

    // file close
    fileRead.close();

    // Grade Calculation
    for (int i = 0; i < 6; i++)
    {
        if (marks[i] >= 85.0)
        {
            grades[i] = "HD";
        }
        else if (75.0 <= marks[i] && marks[i] < 85.0)
        {
            grades[i] = "A";
        }
        else if (65.0 <= marks[i] && marks[i] < 75.0)
        {
            grades[i] = "B";
        }
        else if (50.0 <= marks[i] && marks[i] < 65.0)
        {
            grades[i] = "C";
        }
        else if (marks[i] < 50.0)
        {
            grades[i] = "F";
        }
    }

    // Top Scale
    cout << "123456789012345678901234567890123456789012345" << endl;

    // Final Output
    for (int i = 0; i < 6; i++)
    {
        cout << right << setw(14) << names[i] << setw(10) << courses[i] << setw(10) << marks[i] << setw(10) << grades[i] << setw(10) << endl;
    }

    // Bottom Scale
    cout << "123456789012345678901234567890123456789012345" << endl;

    return 0;
};