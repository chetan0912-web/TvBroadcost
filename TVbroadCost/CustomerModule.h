#ifndef CUSTOMERMODULE_H
#define CUSTOMERMODULE_H

#include <iostream>
#include "Customer.h"
#include "Pakages.h"

#include "BroadCostDbReader.h"

class CustomerModule
{
public:
    CustomerModule(BroadCostDbReader *dbReader,
                   std::map<std::string, Customer*> &customerList,
                   std::map<int, Languages*> &langList);

    bool subscribe(const std::string &custId, const std::string &pakName);
    bool unsubscribe(const std::string &custId, const std::string &pakName);

    void showAllPackages();
    void showSubscribed(const std::string &custId);

    std::map<std::string, Pakages*>& getPackageList() { return m_packageList; }

private:
    BroadCostDbReader *m_dbReader = nullptr;

    std::map<std::string, Customer*> &m_customerList;
    std::map<std::string, Pakages*> m_packageList;
};

#endif
