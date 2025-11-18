#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<iostream>

using namespace std;

class Employee
{
public:
    Employee();
    ~Employee();

    Employee(string& id,string& name,string& designation);

    Employee(const Employee& emp);

    void operator =(const Employee& emp);



    string getEmployId() const;
    void setEmployId(const string& newEmployId);

    string getEmployName() const;
    void setEmployName(const string& newEmployName);

    string getEmployDesignation() const;
    void setEmployDesignation(const string& newEmployDesignation);

private:

    string m_employId;
    string m_employName;
    string m_employDesignation;


};

#endif // EMPLOYEE_H

