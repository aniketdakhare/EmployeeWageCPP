#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int getWorkingHours()
{
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;   
    int empHrs = 0;
    srand(time(0));
    int empCheck = rand() % 3;
    switch(empCheck)
    {
        case IS_PART_TIME:
            empHrs = 4;
            break;
        case IS_FULL_TIME:
            empHrs = 8;
            break;
        default:
            empHrs = 0;
    }
    return empHrs;
}

int main()
{
    const int EMP_RATE_PER_HOUR = 20;
    int empWage = getWorkingHours() * EMP_RATE_PER_HOUR;
    cout << "Employee Wage Per Day = " << empWage << endl;    
}