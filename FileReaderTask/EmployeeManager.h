#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H
#include <iostream>
#include <map>
#include "FileReader.h"
#include "EmployeeCSVReader.h"
#include "EmployeeTextReader.h"
#include "EmployeeDbReader.h"


using namespace std;

class EmployeeManager
{
public:
    EmployeeManager();

    ~EmployeeManager();

    void operator =(const EmployeeManager& empManager);

    EmployeeManager(const EmployeeManager& empManager);

    void display();

    void menu();

    void ReadMenu();

private:

    map < int,FileReader* > m_fileReaderType;

    map<int, string> m_fileMap;

    enum fileReader
    {
        READ_FROM_CSV=1,
        READ_FROM_TEXT,
        READ_FROM_DB,
        EXIT,
    };

    enum display
    {
        DISP_FROM_CSV=1,
        DISP_FROM_TEXT,
        DISP_FROM_DB
    };
};

#endif // EMPLOYEEMANAGER_H
