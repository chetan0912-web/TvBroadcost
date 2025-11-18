#include "CustomerModule.h"

CustomerModule::CustomerModule(BroadCostDbReader *dbReader,
                               std::map<std::string, Customer*> &customerList,
                               std::map<int, Languages*> &langList)
    : m_dbReader(dbReader), m_customerList(customerList)
{
    if (m_dbReader)
    {
        m_dbReader->loadPackages(m_packageList, langList);

        m_dbReader->loadCustomerSubscriptions(m_customerList, m_packageList);
    }
}

bool CustomerModule::subscribe(const std::string &custId, const std::string &pakName)
{
    if (!m_packageList.count(pakName))
    {
        cout << "Package not found!\n";
        return false;
    }

    if (!m_customerList.count(custId))
    {
        cout << "Customer not found!\n";
        return false;
    }

    Customer *cust = m_customerList[custId];
    cust->addSubscribedPackage(pakName, m_packageList[pakName]);

    if (m_dbReader && m_dbReader->dbCustomerSubscribePackage(custId, pakName))
    {
        cout << "Subscribed successfully!\n";
        return true;
    }

    cout << "Failed to update database.\n";
    return false;
}

bool CustomerModule::unsubscribe(const std::string &custId, const std::string &pakName)
{
    if (!m_customerList.count(custId))
    {
        cout << "Customer not found!\n";
        return false;
    }

    auto &subscribed = m_customerList[custId]->getSubscribedPackages();

    if (!subscribed.count(pakName))
    {
        cout << "You are not subscribed to this package.\n";
        return false;
    }

    subscribed.erase(pakName);

    if (m_dbReader)
        m_dbReader->dbCustomerUnsubscribePackage(custId, pakName);

    cout << "Unsubscribed successfully.\n";
    return true;
}

void CustomerModule::showAllPackages()
{
    cout << "\n=========== ALL PACKAGES ===========\n";

    if (m_packageList.empty())
    {
        cout << "No packages found.\n";
        return;
    }

    for (auto &p : m_packageList)
    {
        cout << " • " << p.first << "  (Rs " << p.second->getPakageAmmount() << ")\n";
    }

    cout << "===================================\n";
}

void CustomerModule::showSubscribed(const std::string &custId)
{
    if (!m_customerList.count(custId))
    {
        cout << "Customer not found.\n";
        return;
    }

    auto &mp = m_customerList[custId]->getSubscribedPackages();

    cout << "\n========= YOUR SUBSCRIBED PACKAGES =========\n";

    if (mp.empty())
    {
        cout << "No subscribed packages.\n";
        return;
    }

    for (auto &p : mp)
    {
        cout << " • " << p.first << " (Rs " << p.second->getPakageAmmount() << ")\n";
    }
}
