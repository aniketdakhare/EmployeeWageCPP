#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <unistd.h>

using namespace std;

vector <int> monthlyWages;
fstream fileStream;

void writeFile(string file)
{
    fileStream.open(file, ios::out | ios::trunc);
    if (fileStream.is_open())
    {
        fileStream << "Employee, Monthly Wage\n";
        for (int i = 0; i < monthlyWages.size(); i++)
        {
            fileStream << "Employee_" << (i + 1) << ", "<< (monthlyWages[i]) << "\n";        
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
    }
    return totalEmpHrs;
}

int main()
{
    const int EMP_RATE_PER_HOUR = 20;
    int totalEmployees;
    cout << "\nEnter total number of employees. \n";
    cin >> totalEmployees;
    
    for (int i = 0; i < totalEmployees; i++)
    {
        sleep(2);
        int empWage = getWorkingHours() * EMP_RATE_PER_HOUR;
        monthlyWages.push_back(empWage);
        cout << "Monthly Wage for Employee_" << (i + 1) << " = " << empWage << endl;
    }
    writeFile("EmployeeWageDetails.csv");
}