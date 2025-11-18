#include "EmployeeCSVReader.h"

EmployeeCSVReader::EmployeeCSVReader()
{
    cout << "CSV constructer is called" << endl;
}


EmployeeCSVReader::~EmployeeCSVReader()
{
    cout << "CSV Distructer is called" << endl;
}

void EmployeeCSVReader::operator =(const EmployeeCSVReader& emp)
{
    cout << "CSV assign constructer is called" << endl;
}

EmployeeCSVReader::EmployeeCSVReader(const EmployeeCSVReader& emp)
{
    cout << "CSV copy constructer is called" << endl;
}

void EmployeeCSVReader::readFile(const string& filename)
{

    string id, name, designation;

    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening CSV file!" << endl;
        return;
    }


    while(getline(file,id,',') && getline(file,name,',') && getline(file,designation))
    {
        Employee* e = new Employee(id, name, designation);
        setEmployees(e);
    }

}
