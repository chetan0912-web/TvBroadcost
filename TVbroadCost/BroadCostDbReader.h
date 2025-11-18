#ifndef BROADCOSTDBREADER_H
#define BROADCOSTDBREADER_H

#include "FileReader.h"
#include <sqlite3.h>
#include <map>
#include "Admin.h"
#include "Customer.h"

class BroadCostDbReader : public FileReader
{
private:
    sqlite3 *db;

public:
    BroadCostDbReader();
    ~BroadCostDbReader();

    static BroadCostDbReader* instance();


    virtual bool openFile(const std::string &filename) override;
    virtual void closeFile() override;
    virtual void createFile() override;
    virtual void readData(std::map<int, Languages*>&) override;

    virtual void insertLanguage(int, const Languages*) override;
    virtual void insertChannel(int, int, const Chanels*) override;
    virtual void insertProgram(int, const Programs*) override;
    virtual void insertFullTree(const std::map<int, Languages*>&) override;

    virtual bool deleteChannel(int) override;
    virtual bool deleteProgram(int, int) override;
    virtual void deleteAllPrograms() override;
    virtual void deleteAll() override;


    bool dbAddChannel(int langId, int chId, const std::string &name, double price);
    bool dbAddProgram(int chId, int pId, const std::string &name,
                      const std::string &st, const std::string &et);

    bool deleteLanguage(int langId);

    bool dbDeleteChannel(int chId);
    bool dbDeleteProgram(int progId);
    bool dbDeletePackage(const std::string &pakName);

    bool dbCustomerSubscribePackage(const std::string &custId, const std::string &pakName);

    bool dbCustomerUnsubscribePackage(const std::string &custId, const std::string &pakName);

    bool addAdmin(const Admin &admin);
    bool addCustomer(const Customer &cust);

    bool dbAddChannelToPackage(const std::string &pakName, int chId);
    bool dbRemoveChannelFromPackage(const std::string &pakName, int chId);

    bool dbCreatePackage(const std::string &pakName, int amount);

    bool loadAdmins(std::map<std::string, Admin*> &admins);
    bool loadCustomers(std::map<std::string, Customer*> &customers);

    bool loadPackages(std::map<std::string, Pakages*> &pakages,
                      const std::map<int, Languages*> &languages);

    bool loadCustomerSubscriptions(std::map<std::string, Customer*> &customers,
                                   std::map<std::string, Pakages*> &pakages);

    Chanels* findChannelById(int chId, const std::map<int, Languages*> &languages);
private:
    static BroadCostDbReader* m_dbreader;
};

#endif
