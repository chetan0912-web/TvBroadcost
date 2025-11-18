#ifndef ADMIN_H
#define ADMIN_H

#include "PersonDetails.h"

class Admin : public PersonDetails
{
public:
    Admin();
    ~Admin();
    Admin(const std::string &Id, const std::string &password,
          const std::string &name, const std::string &phoneNumber);
};

#endif // ADMIN_H
