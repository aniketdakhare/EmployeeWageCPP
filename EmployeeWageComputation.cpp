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
    int totalEmployees;
    int totalMonths;

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
        cout << "\nEnter total number of employees. \n";
        cin >> totalEmployees;
        cout << "\nEnter nunber of Months. \n";
        cin >> totalMonths;
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
    vector <CompanyDetails> companyWages;
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

void wageloader(EmployeeWageBuilder employeeWageBuilder, int numberOfCompanies)
{
    for (int companies = 0; companies < numberOfCompanies; companies++)
    {
        int totalEmployees = employeeWageBuilder.companyWages[companies].totalEmployees;
        int totalMonths = employeeWageBuilder.companyWages[companies].totalMonths;
        for (int employee = 0; employee < totalEmployees; employee++)
        {
            vector <int> monthlyWages;
            for (int month = 0; month < totalMonths; month++)
            {
                sleep(1.9);
                int empWage = employeeWageBuilder.getEmployeeWage(employeeWageBuilder.companyWages[companies]);
                monthlyWages.push_back(empWage);
                cout << "Monthly Wage for Employee_" << (employee + 1) << " = " << empWage << endl;   
            }
            writeFile("EmployeeWageDetails.csv", totalMonths, employee, monthlyWages, employeeWageBuilder.companyWages[companies].companyName);
        }
    }
}

int main()
{
    
    int numberOfCompanies;
    cout << "\n Enter number of companies for calculating employee wage\n";
    cin >> numberOfCompanies;
    struct EmployeeWageBuilder employeeWageBuilder;
    for (int i = 0; i < numberOfCompanies; i++)
    {
        struct CompanyDetails company;
        employeeWageBuilder.companyWages.push_back(company);
    }
    wageloader(employeeWageBuilder, numberOfCompanies);
}