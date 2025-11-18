#ifndef AUTHONTICATION_H
#define AUTHONTICATION_H

#include <map>
#include "BroadCostDbReader.h"
#include "Admin.h"
#include "Customer.h"

class Authontication
{
    enum LoginMenu
    {
        LOGIN=1,
        REGISTER,
        EXIT
    };

public:
    Authontication();
    Authontication(std::map<std::string, Admin *> &adminList,
                   std::map<std::string, Customer *> &customerList, BroadCostDbReader *dbReader);

    bool menu(int personType);
    bool adminLogin();
    bool customerLogin();
    void adminRegister();
    void customerRegister();

    const std::map<std::string, Customer *> &getCustomerList() const;
    void setCustomerList(Customer *newCustomer);
    const std::map<std::string, Admin *> &getAdminList() const;
    void setAdminList(Admin *newAdmin);

    Customer *getLoggedCustomer() const;

private:
    std::map<std::string, Admin *> m_adminList;
    std::map<std::string, Customer *> m_customerList;
    BroadCostDbReader *m_dbReader;

    bool isDigit(std::string newId);

    Customer *m_loggedCustomer;
    bool phoneNoValidation(const std::string phoneNo) const;
};

#endif // AUTHONTICATION_H
