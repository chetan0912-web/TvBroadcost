#ifndef EMPLOYEEDBREADER_H
#define EMPLOYEEDBREADER_H
#include<iostream>
#include "FileReader.h"
#include "Employee.h"

class EmployeeDbReader:public FileReader
{
public:

    EmployeeDbReader();

    ~EmployeeDbReader();

    void operator =(const EmployeeDbReader& emp);


    EmployeeDbReader(const EmployeeDbReader& emp);

    void readFile(const string& filename) override;

};

#endif // EMPLOYEEDBREADER_H
