#include "DataModule.h"
#include "BroadCostDbReader.h"
#include "LanguageModule.h"
#include "PakageModule.h"
#include "CustomerModule.h"
#include "Admin.h"
#include "Customer.h"

#include <iostream>

DataModule* DataModule::m_dataModule = nullptr;

DataModule::DataModule(const std::string &dbFile)
{
    std::cout << "Database ready.\n";

    m_dbReader = new BroadCostDbReader();

    if (!m_dbReader->openFile(dbFile))
    {
        std::cerr << "Failed to open database: " << dbFile << "\n";
    }
    else
    {
        m_dbReader->createFile();
    }

    m_dbReader->readData(m_languageList);

    m_dbReader->loadAdmins(m_adminList);
    m_dbReader->loadCustomers(m_customerList);

    m_languageModule = new LanguageModule(m_dbReader);
    m_packageModule  = new PakageModule(m_languageModule, m_dbReader);
    m_customerModule = new CustomerModule(m_dbReader, m_customerList, m_languageList);

    std::cout << "Modules initialized.\n";
}

DataModule::~DataModule()
{
    delete m_languageModule;
    delete m_packageModule;
    delete m_customerModule;
    delete m_dbReader;

    for (auto &p : m_adminList) delete p.second;
    for (auto &p : m_customerList) delete p.second;
    for (auto &p : m_languageList) delete p.second;

    m_adminList.clear();
    m_customerList.clear();
    m_languageList.clear();
}

std::map<int, Languages *> &DataModule::getLanguageList()
{
    return m_languageList;
}

DataModule *DataModule::dataModuleInstance()
{
    if(m_dataModule == nullptr)
       return m_dataModule = new DataModule;
    return m_dataModule;
}

BroadCostDbReader *DataModule::getDbReader() const
{
    return m_dbReader;
}

LanguageModule *DataModule::getLanguageModule() const
{
    return m_languageModule;
}

PakageModule *DataModule::getPackageModule() const
{
    return m_packageModule;
}

CustomerModule *DataModule::getCustomerModule() const
{
    return m_customerModule;
}

std::map<string, Customer *> &DataModule::getCustomerList()
{
    return m_customerList;
}

std::map<string, Admin *> &DataModule::getAdminList()
{
    return m_adminList;
}
