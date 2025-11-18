#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "PersonDetails.h"
#include "Pakages.h"
#include <map>

class DataModule;

class Customer : public PersonDetails
{
public:
    Customer();
    Customer(const std::string &Id, const std::string &password,
             const std::string &name, const std::string phoneNo);
    void addSubscribedPackage(const std::string &pakName, Pakages *pkg);

    ~Customer();
    std::map<std::string, Pakages*>& getSubscribedPackages()
    {
        return m_subscribedPakages;
    }

    bool customerMenu(DataModule *broadCost);

private:
    void addPakage(DataModule *broadCost);
    void displayPakage(DataModule *broadCost);
    void pakageDetails();
    void displayPakageDetails();
    std::map<std::string, Pakages*> m_subscribedPakages;

};


#endif // CUSTOMER_H
