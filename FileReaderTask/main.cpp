#include <iostream>
#include "EmployeeManager.h"

using namespace std;

int main()
{

    EmployeeManager *employeeManager = new EmployeeManager;
    employeeManager->menu();
    delete employeeManager;
    return 0;
}
