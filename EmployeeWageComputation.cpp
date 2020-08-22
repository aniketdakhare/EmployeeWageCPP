#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <sstream>

using namespace std;

struct EmployeeWageDetails
{
    string companyName;
    string employee;
    string month;
    string day;
    int wages;
};

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

list <CompanyDetails> companyWages;

vector<string> split(const string& line, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(line);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

list <EmployeeWageDetails> readFile() 
{ 
    
    fstream fileStream; 
    fileStream.open("EmployeeWageDetails.csv", ios::in); 

    list <EmployeeWageDetails> employeeWages; 

    if (fileStream.is_open())
    {
        vector <string> details;
        string line;
        string word;
        getline(fileStream, line); 

        while (!fileStream.eof()) 
        { 
            details.clear(); 
            getline(fileStream, line); 
            stringstream s(line);
            while (getline(s, word))
            { 
                details = split(word, ',');
                EmployeeWageDetails employeeDetails;
                employeeDetails.companyName = details[0];
                employeeDetails.employee = details[1];
                employeeDetails.month = details[2];
                employeeDetails.day = details[3];
                employeeDetails.wages = stoi(details[4]);
                employeeWages.push_back(employeeDetails);
            }
        }
    }
    fileStream.close();   
    return employeeWages;
} 

void writeFile(string file, int month, int employee, vector <int> wages, string companyName)
{
    fstream fileStream;
    fileStream.open(file, ios::out | ios::app);
    fileStream.seekg(0, ios::end);
    if (fileStream.is_open())
    {
        if (fileStream.tellp() == 0)
        {
            fileStream << "Company Name,Employee,Month,Day,Wages";
        }
        fileStream.seekg(0, ios::beg);
        for (int day = 0; day < wages.size(); day++)
        {
            fileStream << "\n" << companyName << ",Employee_" << (employee + 1) << ",Month_" << month << ",Day_" << (day + 1) << "," << wages[day];
        }
    }
    fileStream.close();
}

struct EmployeeWageBuilder
{
    vector <int> getDailyWages(CompanyDetails);
};

vector <int> EmployeeWageBuilder :: getDailyWages(CompanyDetails company)
{
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    int NUM_OF_WORKING_DAYS = company.NUM_OF_WORKING_DAYS;
    int MAX_HRS_IN_MONTH = company.MAX_HRS_IN_MONTH;
   
    int empHrs = 0;
    int totalEmpHrs = 0;
    int totalWorkingDays = 0;
    vector <int> dailyWages;
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
        dailyWages.push_back(empHrs * company.EMP_RATE_PER_HOUR);
        totalEmpHrs += empHrs;
    }
            // cout << (totalEmpHrs * company.EMP_RATE_PER_HOUR) << endl;
    return dailyWages;
}

void wageloader(EmployeeWageBuilder employeeWageBuilder, int numberOfCompanies)
{
    list <CompanyDetails> :: iterator companies;
    for (companies = companyWages.begin(); companies != companyWages.end(); companies++)
    {
        int totalEmployees = (*companies).totalEmployees;
        int totalMonths = (*companies).totalMonths;
        for (int employee = 0; employee < totalEmployees; employee++)
        {
            for (int month = 0; month < totalMonths; month++)
            {
                sleep(1.9);
                writeFile("EmployeeWageDetails.csv", (month + 1), employee, employeeWageBuilder.getDailyWages(*companies), (*companies).companyName);
            }
        }
    }
}

void insert()
{
    int numberOfCompanies;
    cout << "\n Enter number of companies for calculating employee wage\n";
    cin >> numberOfCompanies;
    struct EmployeeWageBuilder employeeWageBuilder;
    for (int i = 0; i < numberOfCompanies; i++)
    {
        struct CompanyDetails company;
        companyWages.push_back(company);
    }
    wageloader(employeeWageBuilder, numberOfCompanies);
}

CompanyDetails fetchCompanyDetails(string givenCompany)
{
    CompanyDetails companyDetails;
    
    return companyDetails;
}

void displayByCompany()
{
    string givenCompany;
    cout << "\n Enter Company name.\n";
    cin >> givenCompany;
    
    int totalEmployees;
    int totalMonths;
    int totalDays;
    vector <int> monthlySalary;

    list <EmployeeWageDetails> employeeDetails = readFile();
    if(employeeDetails.size() != 0)
    {
        for(list <CompanyDetails> :: iterator company = companyWages.begin(); company != companyWages.end(); company++)
        {
            if ((*company).companyName == givenCompany)
            {
                totalEmployees = (*company).totalEmployees;
                totalMonths = (*company).totalMonths;
                totalDays = (*company).NUM_OF_WORKING_DAYS;
            }
        }

        int count =0;
        for(list <EmployeeWageDetails> :: iterator employee = employeeDetails.begin(); count < employeeDetails.size(); employee++)
        {
            if ((*employee).companyName == givenCompany)
            {
                int totalSalary = 0;
                for(int day = 0; day < totalDays; day++)
                {
                    totalSalary += (*employee).wages;
                    if (day < (totalDays - 1))
                    {
                        employee++;
                        count++;
                    } 
                }
                monthlySalary.push_back(totalSalary);
            }
            else
            {
                count++;
            } 
        }

        for (int emp = 0; emp < totalEmployees; emp++)
        {
            for (int month = 0;month < totalMonths; month++)
            {
                cout << "\nCompany Name: " <<  givenCompany << "\nEmployee Name: "<<  "Employee_" << (emp + 1) << "\nMonth: " << (month + 1) << "\nMonthly Salary: " << monthlySalary[month] << "\n";
            }
        }
    }
    else
    {
        cout << "Company not present." << endl;
    }
}

int main()
{
    while (true)
    {
        int select;
        cout << "\n Select your choice. \n1: Calculate Employee wage for your company. \n2: Display Employee's monthly wage details by company. \n3: Exit\n";
        cin >> select;
        switch(select)
        {
            case 1:
                insert();
                break;
            case 2:
                displayByCompany();
                break;
            case 3:
                exit(0);    
        }
    }
}