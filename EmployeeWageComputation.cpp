#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int getWorkingHours()
{
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    const int NUM_OF_WORKING_DAYS = 20;    
    int empHrs = 0;
    int totalEmpHrs = 0;
    srand(time(0));
    for(int day = 0; day < NUM_OF_WORKING_DAYS; day++)
    {
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
        totalEmpHrs += empHrs;
    }
    return totalEmpHrs;
}

int main()
{
    const int EMP_RATE_PER_HOUR = 20;
    int empWage = getWorkingHours() * EMP_RATE_PER_HOUR;
    cout << "Employee Wage Per Month = " << empWage << endl;    
}