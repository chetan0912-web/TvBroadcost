#ifndef PERSONDETAILS_H
#define PERSONDETAILS_H

#include <iostream>

using namespace std;

class PersonDetails
{
public:
    PersonDetails();
    PersonDetails(std::string &Id, std::string &password,
                  std::string &name, std::string &phoneNo);
    virtual ~PersonDetails();

    std::string getPersonId() const;
    void setPersonId(const std::string &newPersonId);

    std::string getName() const;
    void setName(const std::string &newName);

    std::string getPhoneNo() const;
    void setPhoneNo(const std::string &newPhoneNo);

    std::string getPassword() const;
    void setPassword(const std::string &newPassword);

private:
    std::string m_personId;
    std::string m_name;
    std::string m_PhoneNo;
    std::string m_password;
};

#endif // PERSONDETAILS_H
