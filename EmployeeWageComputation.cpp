#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <unistd.h>

using namespace std;

struct CompanyDetails
{
    string companyName;
    int NUM_OF_WORKING_DAYS;
    int MAX_HRS_IN_MONTH;
    int EMP_RATE_PER_HOUR;
    CompanyDetails()
    {
        cout << "\nEnter Company Name. \n";
        cin >> companyName;
        cout << "\nEnter total number of working days per month. \n";
        cin >> NUM_OF_WORKING_DAYS;
            cout << "\nEnter maximum working hours per month. \n";
        cin >> MAX_HRS_IN_MONTH;
            cout << "\nEnter employee rate per hour. \n";
        cin >> EMP_RATE_PER_HOUR;
    }
};

void writeFile(string file, int totalMonths, int employee, vector <int> wages, string companyName)
{
    fstream fileStream;
    fileStream.open(file, ios::out | ios::app);
    fileStream.seekg(0, ios::end);
    if (fileStream.is_open())
    {
        if (fileStream.tellp() == 0)
        {
            fileStream << "Company Name, Employee";
            for (int month = 0; month < 12 ;month++)
            {
                fileStream << ", Month_" << (month + 1);
            }
        }
        fileStream.seekg(0, ios::beg);
        fileStream << "\n" << companyName << ", Employee_" << (employee + 1);
        for (int month = 0; month < totalMonths; month++)
        {
            fileStream << ", " << wages[month];
        }
    }
    fileStream.close();
}

struct EmployeeWageBuilder
{
    int getWorkingHours(CompanyDetails);
    int getEmployeeWage(CompanyDetails company)
    {
        return getWorkingHours(company) * company.EMP_RATE_PER_HOUR;
    }
};

int EmployeeWageBuilder :: getWorkingHours(CompanyDetails company)
{
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    int NUM_OF_WORKING_DAYS = company.NUM_OF_WORKING_DAYS;
    int MAX_HRS_IN_MONTH = company.MAX_HRS_IN_MONTH;
   
    int empHrs = 0;
    int totalEmpHrs = 0;
    int totalWorkingDays = 0;
    srand(time(0));
    
    while(totalEmpHrs <= MAX_HRS_IN_MONTH && totalWorkingDays < NUM_OF_WORKING_DAYS)
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

void wageloader()
{
    struct CompanyDetails company;
    struct EmployeeWageBuilder employeeWageBuilder;
    int totalEmployees;
    cout << "\nEnter total number of employees. \n";
    cin >> totalEmployees;

    int totalMonths;
    cout << "\nEnter nunber of Months. \n";
    cin >> totalMonths;
    
    for (int i = 0; i < totalEmployees; i++)
    {
        vector <int> monthlyWages;
        for (int i = 0; i < totalMonths; i++)
        {
            sleep(1.9);
            int empWage = employeeWageBuilder.getEmployeeWage(company);
            monthlyWages.push_back(empWage);
            cout << "Monthly Wage for Employee_" << (i + 1) << " = " << empWage << endl;   
        }
        writeFile("EmployeeWageDetails.csv", totalMonths, i, monthlyWages, company.companyName);
    }
}

int main()
{
    while (true)
    {
        int select;
        cout << "\n Select your choice. \n1: Calculate Employee wage for your company. \n2: Exit\n";
        cin >> select;
        switch(select)
        {
            case 1:
                wageloader();
                break;
            case 2:
                exit(0);    
        }
    }
}