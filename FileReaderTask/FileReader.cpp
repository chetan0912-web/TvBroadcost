#include "FileReader.h"

std::vector<Employee *> FileReader::getEmployees()
{
    return employees;
}

void FileReader::setEmployees(Employee *e)
{
    employees.push_back(e);
}

void FileReader::display()
{
    cout << "\nslno\t   Name\t\t      Designation\n" << endl;
    for(Employee *data : employees)
    {
        cout << " " << left << setw(8) << data->getEmployId()
        << left << setw(20) << data->getEmployName()
        << data->getEmployDesignation() << endl;
    }
}

FileReader::~FileReader()
{
    cout << "File Distructer is called" << endl;
    for(auto Data : employees)
    {
        delete Data;
    }

}

FileReader::FileReader()
{
    cout << "File Constructer is called" << endl;
}
