#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    int isPresent = 1;
    srand(time(0));
    int empCheck = rand() % 2;
    if (empCheck == 1)
        cout << "Employee is Present" << endl;
    else
        cout << "Employee is Absent" << endl;
}