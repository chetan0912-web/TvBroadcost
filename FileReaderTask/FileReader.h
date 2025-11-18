#ifndef FILEREADER_H
#define FILEREADER_H
#include <fstream>
#include <vector>
#include <iomanip>
#include "FileReader.h"
#include "Employee.h"

using namespace std;

class FileReader
{
public:

    FileReader();

    virtual ~FileReader();

    virtual void readFile(const string& filename)= 0;

    vector< Employee* > getEmployees();

    void setEmployees(Employee* e);

     void display();

private:

    vector< Employee* > employees;

};












#endif // FILEREADER_H
