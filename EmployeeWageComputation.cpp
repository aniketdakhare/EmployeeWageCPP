#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int getWorkingHours()
{
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    const int NUM_OF_WORKING_DAYS = 20;
    const int MAX_HRS_IN_MONTH = 100;
    int totalEmpHrs = 0;
    int totalWorkingDays = 0;
    srand(time(0));
    while(totalEmpHrs <= MAX_HRS_IN_MONTH && totalWorkingDays <= NUM_OF_WORKING_DAYS)
    {
        totalWorkingDays++;
        int empCheck = rand() % 3;
        switch(empCheck)
        {
            case IS_PART_TIME:
                totalEmpHrs += 4;
                break;
            case IS_FULL_TIME:
                totalEmpHrs += 8;
                break;
            default:
                totalEmpHrs += 0;
        }
    }
    return totalEmpHrs;
}

int main()
{
    const int EMP_RATE_PER_HOUR = 20;
    int empWage = getWorkingHours() * EMP_RATE_PER_HOUR;
    cout << "Employee Wage Per Month = " << empWage << endl;    
}