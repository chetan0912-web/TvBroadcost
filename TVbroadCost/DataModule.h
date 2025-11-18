#ifndef BROADCOST_H
#define BROADCOST_H

#include <map>
#include "BroadCostDbReader.h"
#include "LanguageModule.h"
#include "PakageModule.h"
#include "CustomerModule.h"
#include "Admin.h"
#include "Customer.h"

class DataModule
{
public:
    DataModule(const std::string &dbFile = "broadcast.db");
    ~DataModule();

    std::map<std::string, Admin*>& getAdminList();
    std::map<std::string, Customer*>& getCustomerList();
    std::map<int, Languages*>& getLanguageList();

    static DataModule *dataModuleInstance();

    BroadCostDbReader* getDbReader() const;
    LanguageModule* getLanguageModule() const;
    PakageModule* getPackageModule() const;
    CustomerModule* getCustomerModule() const;

private:
    BroadCostDbReader *m_dbReader = nullptr;

    std::map<std::string, Admin*> m_adminList;
    std::map<std::string, Customer*> m_customerList;
    std::map<int, Languages*> m_languageList;

    LanguageModule *m_languageModule = nullptr;
    PakageModule   *m_packageModule = nullptr;
    CustomerModule *m_customerModule = nullptr;

    static DataModule *m_dataModule;
};

#endif
