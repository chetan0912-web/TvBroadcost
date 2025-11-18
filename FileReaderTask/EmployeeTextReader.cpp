#include "EmployeeTextReader.h"

EmployeeTextReader::EmployeeTextReader()
{
    cout << "TEXT constructer is called" <<endl;
}

EmployeeTextReader::~EmployeeTextReader()
{
    cout << "TEXT distructer is called"  << endl;
}

void EmployeeTextReader::operator =(const EmployeeTextReader& emp)
{
    cout << "TEXT Assign constructer is called" << endl;
}

EmployeeTextReader::EmployeeTextReader(const EmployeeTextReader& emp)
{
    cout << "TEXT copy constructer is called" << endl;
}



void EmployeeTextReader::readFile(const string& filename)
{
    string id, name, designation;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening CSV file!" << endl;
        return;
    }


    while(getline(file,id,' ') && getline(file,name,' ') && getline(file,designation))
    {
        Employee* e = new Employee(id, name, designation);
         setEmployees(e);
    }
}
