#include "Admin.h"

Admin::Admin() {}

Admin::~Admin() {}

Admin::Admin(const std::string &Id, const std::string& password, const std::string &name, const std::string &phoneNumber)
{
    setName(name);
    setPassword(password);
    setPersonId(Id);
    setPhoneNo(phoneNumber);
}
