#include <iostream>
using namespace std;

// input variables
double hours;
double hourlyRate;
double days;
int payCycle;

// output variables
double dailyPay;
double totalPay;

// functions
double payPerDay(double, double);
double payPerCycle(double, double);


int main()
{
    cout << "Enter hourly pay rate: ";
    cin >> hourlyRate;
    cout << "Enter hours worked per day: ";
    cin >> hours;
    cout << "Enter days worked: ";
    cin >> days;
    cout << "Pay per day: " << payPerDay(hours, hourlyRate) << endl;
    cout << "Total Pay: " << payPerCycle(dailyPay, days) << endl;
}

double payPerDay(double h, double hR)
{
    //h = hours hR = hourly rate
    dailyPay = h * hR;
    return dailyPay;
}

double payPerCycle(double pPd, double d)
{
    //pPd = pay per day d = days
    totalPay = pPd * d;
    return totalPay;
}