#define VERSION 3.03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

// vars for program function/s
string selectedInput;
int registrationNumber;

//universal vars
string inputPhone;
string inputAddress;
string inputName;

//vars for student
string inputProgram;
float inputGpa;

// vars for staff
int inputSalary;
string inputSchool;

// Function Declaration
void studentData();
void staffData();

// Class Definition
class person
{
public:
    //Assign a name to name
    void setName(string userName)
    {
        name = userName;
        return;
    };

    // Retrieve the value of name
    string getName() { return name; };

    // Assign a phone no. to phone
    void setPhone(string userPhone)
    {
        phone = userPhone;
        return;
    };

    // Retrieve the value of phone
    string getPhone() { return phone; };

    // Assign a value to address
    void setAddress(string userAddress)
    {
        address = userAddress;
        return;
    };

    // Retrieve the value of address
    string getAddress() { return address; };

    // Print values of all private members
    void print();

private:
    string name;
    string phone;
    string address;
};

class studentRegistration : public person
{
public:
    // Assigns program name to progam
    void setProgram(string userProgram)
    {
        program = userProgram;
        return;
    };

    // Returns program string
    string getProgram() { return program; };

    void setGpa(float userGpa)
    {
        gpa = userGpa;
        return;
    };

    // Returns GPA
    float getGpa() { return gpa; };

    void printStudent();

private:
    string program;
    float gpa;
};

class staffRegistration : public person
{
public:
    //Sets user school
    void setSchool(string userSchool)
    {
        school = userSchool;
        return;
    }

    //Returns school name
    string getSchool() { return school; };

    // Sets User Salary
    void setSalary(int userSalary)
    {
        salary = userSalary;
        return;
    }

    // Retunrs salary
    int getSalary() { return salary; };

    void printStaff();

private:
    string school;
    int salary;
};

int main()
{

    // Start
    cout << "USQ Registration Software ver " << VERSION << endl;
    cout << "How many staff/students would you like to register?" << endl;
    cin >> registrationNumber;
    cout << "Please select \"staff\" or \"student\" to begin registration process" << endl;
    cin >> selectedInput;

    // Not exactly looping back, but it gets the job done, sort of...
    for (int i = 0; i < registrationNumber; i++)
    {
        // Student Registration
        if (selectedInput == "student" || selectedInput == "Student")
        {
            studentData();
        }
        else if (selectedInput == "staff" || selectedInput == "Staff")
        {
            staffData();
        }
        else
        {
            cout << "Thanks for using the Program!" << endl;
            return 1;
        }
    }

    cout << "Thanks for using the program!" << endl;

    return 0;
}

// Functions Below

void studentData()
{
    studentRegistration student;

    //Defining Name
    cout << "Please enter students name: " << endl;
    // cin >> name;
    cin.ignore();
    getline(cin, inputName);
    student.setName(inputName);

    // debug print
    // cout << student.getName() << endl;

    //Defining Phone
    cout << "Please enter students phone number: " << endl;
    // cin.ignore();
    getline(cin, inputPhone);
    student.setPhone(inputPhone);

    //Defining Address
    cout << "Please enter students address: " << endl;
    // cin.ignore();
    getline(cin, inputAddress);
    student.setAddress(inputAddress);

    // Defining Program
    cout << "Please enter student program: " << endl;
    // cin.ignore();
    getline(cin, inputProgram);
    student.setProgram(inputProgram);

    //Defining GPA
    cout << "Please enter student GPA: " << endl;
    // cin.ignore();
    cin >> inputGpa;
    student.setGpa(inputGpa);

    // test print
    // cout << "Student GPA: " << student.getGpa() << endl;

    student.printStudent();
}

void staffData()
{
    staffRegistration staff;

    //Defining Name
    cout << "Please enter staffs name: " << endl;
    // cin >> name;
    cin.ignore();
    getline(cin, inputName);
    staff.setName(inputName);

    // debug print
    // cout << staff.getName() << endl;

    //Defining Phone
    cout << "Please enter staff phone number: " << endl;
    // cin.ignore();
    getline(cin, inputPhone);
    staff.setPhone(inputPhone);

    //Defining Address
    cout << "Please enter staff address: " << endl;
    // cin.ignore();
    getline(cin, inputAddress);
    staff.setAddress(inputAddress);

    // Defining School
    cout << "Please enter staff school: " << endl;
    // cin.ignore();
    getline(cin, inputSchool);
    staff.setSchool(inputSchool);

    //Defining Salary
    cout << "Please enter staff salary: " << endl;
    // cin.ignore();
    cin >> inputSalary;
    staff.setSalary(inputSalary);

    // test print, weird things happen letters are inputted
    // cout << "Staff Salary: " << staff.getSalary() << endl;

    staff.printStaff();
}

void studentRegistration::printStudent()
{
    // Prints to cli
    cout << right << setw(10) << "Name:  " << getName() << "\n"
         << setw(10) << "Phone:  " << getPhone() << "\n"
         << "Address:  " << getAddress() << "\n"
         << "Program:  " << getProgram() << "\n"
         << setw(10) << "GPA:  " << getGpa() << endl;

    // Prints to file
    ofstream studentFile;
    studentFile.open("StudentRegister.txt", ios::app);

    studentFile << "Name:  " << getName() << "\n"
                << "Phone:  " << getPhone() << "\n"
                << "Address:  " << getAddress() << "\n"
                << "Program:  " << getProgram() << "\n"
                << "GPA:  " << getGpa() << "\n"
                << endl;

    studentFile.close();
}

void staffRegistration::printStaff()
{
    // prints to cli
    cout << right << setw(10) << "Name:  " << getName() << "\n"
         << setw(10) << "Phone:  " << getPhone() << "\n"
         << "Address:  " << getAddress() << "\n"
         << setw(10)
         << "School:  " << getSchool() << "\n"
         << setw(10) << "Salary:  " << getSalary() << endl;

    // prints to file
    ofstream staffFile;
    staffFile.open("StaffRegister.txt", ios::app);

    staffFile << "Name:  " << getName() << "\n"
              << "Phone:  " << getPhone() << "\n"
              << "Address:  " << getAddress() << "\n"
              << "School:  " << getSchool() << "\n"
              << "Salary:  " << getSalary() << "\n"
              << endl;

    staffFile.close();
}
