#ifndef EMPLOYEECSVREADER_H
#define EMPLOYEECSVREADER_H
#include<iostream>
#include "FileReader.h"
#include "Employee.h"

class EmployeeCSVReader : public FileReader {

public:

    EmployeeCSVReader();

    ~EmployeeCSVReader();

    void operator =(const EmployeeCSVReader& emp);

    EmployeeCSVReader(const EmployeeCSVReader& emp);

    void readFile(const string& filename) override;

};

#endif // EMPLOYEECSVREADER_H
