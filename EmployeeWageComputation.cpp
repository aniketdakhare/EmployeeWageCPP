#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

vector <int> dailyWorkingHours;
fstream fileStream;

void writeFile(string file, int empRate)
{
    fileStream.open(file, ios::out | ios::trunc);
    if (fileStream.is_open())
    {
        fileStream << "Day, Daily Wage\n";
        for (int i = 0; i < dailyWorkingHours.size(); i++)
        {
            fileStream << "Day_" << (i + 1) << ", "<< (dailyWorkingHours[i] * empRate) << "\n";        
        }
    }
    fileStream.close();
}

int getWorkingHours()
{
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    const int NUM_OF_WORKING_DAYS = 20;
    const int MAX_HRS_IN_MONTH = 100;
    int empHrs = 0;
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
                empHrs = 4;
                break;
            case IS_FULL_TIME:
                empHrs = 8;
                break;
            default:
                empHrs = 0;
        }
        totalEmpHrs += empHrs;
        dailyWorkingHours.push_back(empHrs);
    }
    return totalEmpHrs;
}

int main()
{
    const int EMP_RATE_PER_HOUR = 20;
    int empWage = getWorkingHours() * EMP_RATE_PER_HOUR;
    writeFile("EmployeeWageDetails.csv", EMP_RATE_PER_HOUR);
    cout << "Employee Wage Per Month = " << empWage << endl;    
}