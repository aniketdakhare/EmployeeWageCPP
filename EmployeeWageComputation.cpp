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
    int monthlyWage;
    int perDayWage;
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
        cout << "\nEnter Company Name:  ";
        cin >> companyName;
        cout << "\nEnter total number of working days per month:  ";
        cin >> NUM_OF_WORKING_DAYS;
        cout << "\nEnter maximum working hours per month:  ";
        cin >> MAX_HRS_IN_MONTH;
        cout << "\nEnter employee rate per hour:  ";
        cin >> EMP_RATE_PER_HOUR;
        cout << "\nEnter total number of employees:  ";
        cin >> totalEmployees;
        cout << "\nEnter nunber of Months:  ";
        cin >> totalMonths;
    }
};

vector<string> split(const string& line, char delimiter);
list <EmployeeWageDetails> readFile();

struct EmployeeWageBuilder
{
    vector <int> getDailyWages(CompanyDetails);
    void displayByCompany();
};

vector <int> EmployeeWageBuilder :: getDailyWages(CompanyDetails company)
{
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    int NUM_OF_WORKING_DAYS = company.NUM_OF_WORKING_DAYS;
    int MAX_HRS_IN_MONTH = company.MAX_HRS_IN_MONTH;
   
    int empHrs = 0, totalEmpHrs = 0, totalWorkingDays = 0;
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
    return dailyWages;
}

void EmployeeWageBuilder :: displayByCompany()
{
    string givenCompany;
    cout << "\nEnter Company name:  ";
    cin >> givenCompany;
    
    int totalWage = 0;
    list <EmployeeWageDetails> employeeDetails = readFile();

    for(list <EmployeeWageDetails> :: iterator employee = employeeDetails.begin(); employee != employeeDetails.end(); employee++)
    {
        if ((*employee).companyName == givenCompany)
        {
            totalWage += (*employee).perDayWage;
        }
    }

    cout<< "\n----------------------------------------------------------------------------------" << endl;
    cout << "\nTotal Wage of " << givenCompany << " Company is: " << totalWage << endl;
}

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
        string line, word;
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
                employeeDetails.perDayWage = stoi(details[4]);
                employeeWages.push_back(employeeDetails);
            }
        }
    }
    fileStream.close();   
    return employeeWages;
} 

void writeFile(string file, vector <int> wages,EmployeeWageDetails employeeWageDetails)
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
            fileStream << "\n" << employeeWageDetails.companyName  << employeeWageDetails.employee;
            fileStream << employeeWageDetails.month << ",Day_" << (day + 1) << "," << wages[day];
        }
    }
    fileStream.close();
}

void wageloader(list <CompanyDetails> companyWages)
{
    struct EmployeeWageBuilder employeeWageBuilder;
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
                struct EmployeeWageDetails employeeWageDetails;
                employeeWageDetails.companyName = (*companies).companyName;
                employeeWageDetails.month = ",Month_" + to_string(month + 1);
                employeeWageDetails.employee = ",Employee_" + to_string(employee + 1);
                writeFile("EmployeeWageDetails.csv", employeeWageBuilder.getDailyWages(*companies), employeeWageDetails);
            }
        }
    }
}

vector <EmployeeWageDetails> getSortedList(vector <EmployeeWageDetails> detailsList, int sortType)
{
    for (int i = 0; i < detailsList.size(); i++)
    {
        for (int j = 0; j < (detailsList.size() - i); j++)
        {
            switch (sortType)
            {
                case 1:
                    if (detailsList[j].monthlyWage < detailsList[j + 1].monthlyWage)
                    {
                        swap(detailsList[j], detailsList[j + 1]);
                    }
                    break;
                case 2:
                    if (detailsList[j].perDayWage < detailsList[j + 1].perDayWage)
                    {
                        swap(detailsList[j], detailsList[j + 1]);
                    }
                break;
            }
        }
    }
    return detailsList;
}

vector <EmployeeWageDetails> getMonthlyWagesList(list <CompanyDetails> companyWages)
{
    list <EmployeeWageDetails> employeeDetails = readFile();
    vector <EmployeeWageDetails> monthlyWagesList;
    list <CompanyDetails> :: iterator companies;
    for (companies = companyWages.begin(); companies != companyWages.end(); companies++)
    {
        for(int empCount = 1; empCount <= companies->totalEmployees; empCount++)
        {
            for(int monthCount = 1; monthCount <= companies->totalMonths; monthCount++)
            {
                int monthlySalary = 0;
                string month = ("Month_" + to_string(monthCount));
                string employeeName = ("Employee_" + to_string(empCount));
                struct EmployeeWageDetails employeeWageDetails;

                for(list <EmployeeWageDetails> :: iterator employee = employeeDetails.begin(); employee != employeeDetails.end(); employee++)
                {
                    if (companies->companyName == employee->companyName && employee->month == month && employee->employee == employeeName)
                    {
                        monthlySalary += employee->perDayWage;
                    } 
                }
                employeeWageDetails.companyName = companies->companyName;
                employeeWageDetails.employee = employeeName;
                employeeWageDetails.month = month;
                employeeWageDetails.monthlyWage = monthlySalary;
                monthlyWagesList.push_back(employeeWageDetails);
            }
        }
    }
    return monthlyWagesList;
}

void display(EmployeeWageDetails employeeWageDetails)
{
    cout << "\nCompany Name: " << employeeWageDetails.companyName << "\nEmployee Name: " << employeeWageDetails.employee;
    cout << "\nMonth: " << employeeWageDetails.month << "\nDay: " << employeeWageDetails.day;
    cout << "\nWage Per Day: " << employeeWageDetails.perDayWage << endl;
    cout << "\n----------------------------------------------------------------------------------" << endl;
}

void displayByWagePerHour(list <CompanyDetails> companyWages)
{
    int wagePerHour;
    cout << "\nEnter Wage per Hour:  ";
    cin >> wagePerHour;

    list <EmployeeWageDetails> employeeDetails = readFile();

    list <CompanyDetails> :: iterator companies;
    for (companies = companyWages.begin(); companies != companyWages.end(); companies++)
    {
        if (companies->EMP_RATE_PER_HOUR == wagePerHour)
        {
            for(list <EmployeeWageDetails> :: iterator employee = employeeDetails.begin(); employee != employeeDetails.end(); employee++)
            {
               if (companies->companyName == employee->companyName)
                {
                    display((*employee));
                } 
            }
        }
        
    }
}    

void sortByDaillyWage()
{
    list <EmployeeWageDetails> employeeDetails = readFile();
    vector <EmployeeWageDetails> dailyWagesList(employeeDetails.begin(), employeeDetails.end());
    vector <EmployeeWageDetails> sortedDailyWagesList = getSortedList(dailyWagesList, 2);
    for(int employeeCount = 0; employeeCount < sortedDailyWagesList.size(); employeeCount++)
    {
        display(sortedDailyWagesList[employeeCount]);
    }
}

void sortByMonthlyWage(list <CompanyDetails> *companyWages)
{
    vector <EmployeeWageDetails> monthlyWagesList = getMonthlyWagesList(*companyWages);
    vector <EmployeeWageDetails> sortedMonthlyWagesList = getSortedList(monthlyWagesList, 1);
    for(int employeeCount = 0; employeeCount < sortedMonthlyWagesList.size(); employeeCount++)
    {
        cout << "\nCompany Name: " << sortedMonthlyWagesList[employeeCount].companyName << "\nEmployee Name: " << sortedMonthlyWagesList[employeeCount].employee;
        cout << "\nMonth: " << sortedMonthlyWagesList[employeeCount].month << "\nWage per month: " << sortedMonthlyWagesList[employeeCount].monthlyWage << endl;
        cout<< "\n----------------------------------------------------------------------------------" << endl;
    }
}

void insert(list <CompanyDetails> *companyWages)
{
    struct CompanyDetails company;
    companyWages->push_back(company);
    wageloader(*companyWages);
}

void selectOptions()
{
    struct EmployeeWageBuilder employeeWageBuilder;
    list <CompanyDetails> companyWages;
    while (true)
    {
        int select;
        cout << "\nSelect your choice. \n1: Calculate Employee wage for your company. \n2: Display Total wage by company. ";
        cout << "\n3: Display sorted list by monthly wages. \n4: Display sorted list by Daily wages.";
        cout << "\n5: Display Employee Details as per given wage per hour.  \n6: Exit\n";
        cin >> select;
        switch(select)
        {
            case 1:
                insert(&companyWages);
                break;
            case 2:
                employeeWageBuilder.displayByCompany();
                break;
            case 3:
                sortByMonthlyWage(&companyWages);
                break;
            case 4:
                sortByDaillyWage();
                break;
            case 5:
                displayByWagePerHour(companyWages);
                break;
            case 6:
                exit(0);
                break;
            default:
                cout << "\nInvalid Input." << endl;   
        }
        cout<< "\n----------------------------------------------------------------------------------" << endl;
    }
}

int main()
{
    selectOptions();
}