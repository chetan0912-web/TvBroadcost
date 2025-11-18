#include "Employee.h"

Employee::Employee()
{
    cout << "Employ Constructer is called" << endl;
}

Employee::~Employee()
{
    cout << "Employee distructer is called" << endl;

}

Employee::Employee(string &id, string &name, string &designation)
{
    cout << "parametarized employ constructer is called" << endl;
    setEmployId(id);
    setEmployName(name);
    setEmployDesignation(designation);

}

Employee::Employee(const Employee& emp)
{
    cout<<"Employee copy Constructor"<<endl;
}

void Employee::operator =(const Employee& emp)
{
    cout << "assign Opperater is called" << endl;
}

string Employee::getEmployId() const
{
    return m_employId;
}

void Employee::setEmployId(const string& newEmployId)
{
    m_employId = newEmployId;
}

string Employee::getEmployName() const
{
    return m_employName;
}

void Employee::setEmployName(const string& newEmployName)
{
    m_employName = newEmployName;
}

string Employee::getEmployDesignation() const
{
    return m_employDesignation;
}

void Employee::setEmployDesignation(const string& newEmployDesignation)
{
    m_employDesignation = newEmployDesignation;
}
