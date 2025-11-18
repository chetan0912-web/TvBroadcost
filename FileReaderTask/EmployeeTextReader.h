#ifndef EMPLOYEETEXTREADER_H
#define EMPLOYEETEXTREADER_H
#include<iostream>
#include "FileReader.h"
#include "Employee.h"

using namespace std;

class EmployeeTextReader : public FileReader
{

public:
    EmployeeTextReader();

    ~EmployeeTextReader();

    void operator =(const EmployeeTextReader& emp);


    EmployeeTextReader(const EmployeeTextReader& emp);



    void readFile(const string& filename) override;

};

#endif // EMPLOYEETEXTREADER_H
