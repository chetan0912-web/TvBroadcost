#include "PersonDetails.h"

PersonDetails::PersonDetails() {}

PersonDetails::PersonDetails(string& Id, string& password, string& name, string& phoneNo)
{
    setName(name);
    setPhoneNo(phoneNo);
    setPassword(password);
    setPersonId(Id);
}

PersonDetails::~PersonDetails() {}

string PersonDetails::getPersonId() const
{
    return m_personId;
}

void PersonDetails::setPersonId(const string &newPersonId)
{
    m_personId = newPersonId;
}

string PersonDetails::getName() const
{
    return m_name;
}

void PersonDetails::setName(const string &newName)
{
    m_name = newName;
}

string PersonDetails::getPhoneNo() const
{
    return m_PhoneNo;
}

void PersonDetails::setPhoneNo(const string &newPhoneNo)
{
    m_PhoneNo = newPhoneNo;
}

string PersonDetails::getPassword() const
{
    return m_password;
}

void PersonDetails::setPassword(const string & newPassword)
{
    m_password = newPassword;
}
