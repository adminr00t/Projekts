#include <iostream>
#include <fstream>
using namespace std;

int main(){
    char data[100];

    // open a file in write mode
    ofstream outfile;
    outfile.open("Credentials.dat");

    cout << "Writing to File..." << endl;
    cout << "Enter Username: ";
    cin.getline(data,100);

    // Writ inputted data into the file
    outfile << data << endl;

    cout << "Enter Password: ";
    cin >> data;
    cin.ignore();

    // write inputted data into file
    outfile << data << endl;

    // close the file
    outfile.close();

    // open a file in read mode
    ifstream infile;
    infile.open("Credentials.dat");

    cout << "Reading from file..." << endl;
    infile >> data;

    // write data to screen
    cout << data << endl;

    // wrtie data to screen
    infile >> data;
    cout << data << endl;

    // Close file
    infile.close();

    return 0;
}