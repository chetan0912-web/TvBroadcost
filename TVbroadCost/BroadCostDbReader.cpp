#include "BroadCostDbReader.h"
#include "Pakages.h"
#include <iostream>
#include <sqlite3.h>
using namespace std;


BroadCostDbReader* BroadCostDbReader::m_dbreader = nullptr;

bool BroadCostDbReader::openFile(const std::string &filename)
{
    if (sqlite3_open(filename.c_str(), &db) == SQLITE_OK)
        return true;

    cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
    db = nullptr;
    return false;
}

void BroadCostDbReader::closeFile()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

void BroadCostDbReader::createFile()
{
    const char *sql[] = {
        "CREATE TABLE IF NOT EXISTS Languages(LanguageId INTEGER PRIMARY KEY, LanguageName TEXT);",
        "CREATE TABLE IF NOT EXISTS Channels(ChannelId INTEGER PRIMARY KEY, LanguageId INTEGER, ChannelName TEXT, ChannelPrice DOUBLE, FOREIGN KEY(LanguageId) REFERENCES Languages(LanguageId));",
        "CREATE TABLE IF NOT EXISTS Programs(ProgramId INTEGER PRIMARY KEY, ChannelId INTEGER, ProgramName TEXT, StartTime TEXT, EndTime TEXT, FOREIGN KEY(ChannelId) REFERENCES Channels(ChannelId));",
        "CREATE TABLE IF NOT EXISTS Admins(AdminId TEXT PRIMARY KEY, Password TEXT, Name TEXT, Phone TEXT);",
        "CREATE TABLE IF NOT EXISTS Customers(CustomerId TEXT PRIMARY KEY, Password TEXT, Name TEXT, Phone TEXT);",
        "CREATE TABLE IF NOT EXISTS Packages(PackageName TEXT PRIMARY KEY, Amount INTEGER);",
        "CREATE TABLE IF NOT EXISTS PackageChannels(PackageName TEXT, ChannelId INTEGER, FOREIGN KEY(PackageName) REFERENCES Packages(PackageName), FOREIGN KEY(ChannelId) REFERENCES Channels(ChannelId));",
        "CREATE TABLE IF NOT EXISTS CustomerPackages(CustomerId TEXT, PackageName TEXT, FOREIGN KEY(CustomerId) REFERENCES Customers(CustomerId), FOREIGN KEY(PackageName) REFERENCES Packages(PackageName));"
    };
    for (auto s : sql)
        sqlite3_exec(db, s, nullptr, nullptr, nullptr);
}

void BroadCostDbReader::readData(std::map<int, Languages *> &langList)
{
    if (!db) return;

    sqlite3_stmt *stmt;

    const char *sqlLang = "SELECT LanguageId, LanguageName FROM Languages;";
    if (sqlite3_prepare_v2(db, sqlLang, -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int id = sqlite3_column_int(stmt, 0);
            string name = (const char *)sqlite3_column_text(stmt, 1);
            langList[id] = new Languages(id, name);
        }
        sqlite3_finalize(stmt);
    }

    const char *sqlCh = "SELECT ChannelId, LanguageId, ChannelName, ChannelPrice FROM Channels;";
    if (sqlite3_prepare_v2(db, sqlCh, -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int chId = sqlite3_column_int(stmt, 0);
            int langId = sqlite3_column_int(stmt, 1);
            string chName = (const char *)sqlite3_column_text(stmt, 2);
            double price = sqlite3_column_double(stmt, 3);
            if (langList.count(langId))
                langList[langId]->setChannels(chId, new Chanels(chId, chName, price));
        }
        sqlite3_finalize(stmt);
    }

    const char *sqlProg = "SELECT ProgramId, ChannelId, ProgramName, StartTime, EndTime FROM Programs;";
    if (sqlite3_prepare_v2(db, sqlProg, -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int pId = sqlite3_column_int(stmt, 0);
            int chId = sqlite3_column_int(stmt, 1);
            string pName = (const char *)sqlite3_column_text(stmt, 2);
            string start = (const char *)sqlite3_column_text(stmt, 3);
            string end = (const char *)sqlite3_column_text(stmt, 4);

            Programs *prog = new Programs(pId, pName, start, end);
            for (auto &lp : langList)
            {
                Chanels *ch = lp.second->chanelFound(chId);
                if (ch)
                {
                    ch->setProgramList(pId, prog);
                    break;
                }
            }
        }
        sqlite3_finalize(stmt);
    }
}

void BroadCostDbReader::insertLanguage(int id, const Languages *lang)
{
    const char *sql = "INSERT OR REPLACE INTO Languages VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return;
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, lang->language().c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void BroadCostDbReader::insertChannel(int chId, int langId, const Chanels *ch)
{
    const char *sql = "INSERT OR REPLACE INTO Channels VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return;
    sqlite3_bind_int(stmt, 1, chId);
    sqlite3_bind_int(stmt, 2, langId);
    sqlite3_bind_text(stmt, 3, ch->getChanelName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, ch->getChannelPrice());
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void BroadCostDbReader::insertProgram(int chId, const Programs *prog)
{
    const char *sql = "INSERT OR REPLACE INTO Programs VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return;
    sqlite3_bind_int(stmt, 1, prog->getProgramId());
    sqlite3_bind_int(stmt, 2, chId);
    sqlite3_bind_text(stmt, 3, prog->getProgramName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, prog->getStartTime().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, prog->getEndTime().c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}


bool BroadCostDbReader::addAdmin(const Admin &admin)
{
    if (!db) return false;

    const char *sql = "INSERT INTO Admins (AdminId, Password, Name, Phone) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, admin.getPersonId().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, admin.getPassword().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, admin.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, admin.getPhoneNo().c_str(), -1, SQLITE_TRANSIENT);

    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}

bool BroadCostDbReader::addCustomer(const Customer &cust)
{
    if (!db) return false;

    const char *sql = "INSERT INTO Customers (CustomerId, Password, Name, Phone) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, cust.getPersonId().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, cust.getPassword().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, cust.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, cust.getPhoneNo().c_str(), -1, SQLITE_TRANSIENT);

    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}

bool BroadCostDbReader::loadAdmins(std::map<std::string, Admin*> &admins)
{
    if (!db) return false;

    sqlite3_stmt *stmt;
    const char *sql = "SELECT AdminId, Password, Name, Phone FROM Admins;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        string id    = (const char*)sqlite3_column_text(stmt, 0);
        string pass  = (const char*)sqlite3_column_text(stmt, 1);
        string name  = (const char*)sqlite3_column_text(stmt, 2);
        string phone = (const char*)sqlite3_column_text(stmt, 3);

        if (admins.find(id) == admins.end())
            admins[id] = new Admin(id, pass, name, phone);
    }

    sqlite3_finalize(stmt);
    return true;
}

bool BroadCostDbReader::loadCustomers(std::map<std::string, Customer*> &customers)
{
    if (!db) return false;

    sqlite3_stmt *stmt;
    const char *sql = "SELECT CustomerId, Password, Name, Phone FROM Customers;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        string id    = (const char*)sqlite3_column_text(stmt, 0);
        string pass  = (const char*)sqlite3_column_text(stmt, 1);
        string name  = (const char*)sqlite3_column_text(stmt, 2);
        string phone = (const char*)sqlite3_column_text(stmt, 3);

        if (customers.find(id) == customers.end())
            customers[id] = new Customer(id, pass, name, phone);
    }

    sqlite3_finalize(stmt);
    return true;
}

bool BroadCostDbReader::dbCreatePackage(const std::string &pakName, int amount)
{
    const char *sql = "INSERT INTO Packages VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, pakName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, amount);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool BroadCostDbReader::dbAddChannelToPackage(const std::string &pakName, int chId)
{
    const char *sql = "INSERT INTO PackageChannels VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, pakName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, chId);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool BroadCostDbReader::dbRemoveChannelFromPackage(const std::string &pakName, int chId)
{
    const char *sql = "DELETE FROM PackageChannels WHERE PackageName=? AND ChannelId=?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, pakName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, chId);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool BroadCostDbReader::dbDeletePackage(const std::string &pakName)
{
    const char *sql = "DELETE FROM Packages WHERE PackageName=?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, pakName.c_str(), -1, SQLITE_STATIC);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool BroadCostDbReader::dbCustomerSubscribePackage(const std::string &custId, const std::string &pakName)
{
    const char *sql = "INSERT INTO CustomerPackages VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, custId.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pakName.c_str(), -1, SQLITE_STATIC);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool BroadCostDbReader::dbCustomerUnsubscribePackage(const std::string &custId, const std::string &pakName)
{
    const char *sql = "DELETE FROM CustomerPackages WHERE CustomerId=? AND PackageName=?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, custId.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pakName.c_str(), -1, SQLITE_STATIC);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool BroadCostDbReader::deleteChannel(int channelId)
{
    const char *sql = "DELETE FROM Channels WHERE ChannelId=?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_int(stmt, 1, channelId);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool BroadCostDbReader::deleteProgram(int channelId, int programId)
{
    const char *sql = "DELETE FROM Programs WHERE ChannelId=? AND ProgramId=?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_int(stmt, 1, channelId);
    sqlite3_bind_int(stmt, 2, programId);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool BroadCostDbReader::deleteLanguage(int langId)
{
    const char *sql = "DELETE FROM Languages WHERE LanguageId=?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_int(stmt, 1, langId);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

void BroadCostDbReader::deleteAll()
{
    const char *sqls[] = {
        "DELETE FROM Programs;",
        "DELETE FROM Channels;",
        "DELETE FROM Languages;",
        "DELETE FROM Admins;",
        "DELETE FROM Customers;",
        "DELETE FROM Packages;",
        "DELETE FROM PackageChannels;",
        "DELETE FROM CustomerPackages;"
    };
    for (auto s : sqls)
        sqlite3_exec(db, s, nullptr, nullptr, nullptr);
}

void BroadCostDbReader::deleteAllPrograms()
{
    if (!db) return;
    sqlite3_exec(db, "DELETE FROM Programs;", nullptr, nullptr, nullptr);
}

bool BroadCostDbReader::dbAddChannel(int langId, int chId, const std::string &chName, double price)
{
    if (!db) return false;

    const char *sql =
        "INSERT OR REPLACE INTO Channels (ChannelId, LanguageId, ChannelName, ChannelPrice) "
        "VALUES (?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "dbAddChannel prepare failed: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, chId);
    sqlite3_bind_int(stmt, 2, langId);
    sqlite3_bind_text(stmt, 3, chName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 4, price);

    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}

bool BroadCostDbReader::dbAddProgram(int chId, int pId,
                                     const std::string &name,
                                     const std::string &st,
                                     const std::string &et)
{
    if (!db) return false;

    const char *sql =
        "INSERT OR REPLACE INTO Programs (ProgramId, ChannelId, ProgramName, StartTime, EndTime) "
        "VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "dbAddProgram prepare failed: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, pId);
    sqlite3_bind_text(stmt, 3, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, st.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, et.c_str(), -1, SQLITE_TRANSIENT);

    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}

bool BroadCostDbReader::dbDeleteChannel(int chId)
{
    if (!db) return false;

    const char *sql = "DELETE FROM Channels WHERE ChannelId=?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "dbDeleteChannel prepare failed: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, chId);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}

bool BroadCostDbReader::dbDeleteProgram(int progId)
{
    if (!db) return false;

    const char *sql = "DELETE FROM Programs WHERE ProgramId=?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "dbDeleteProgram prepare failed: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, progId);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}

void BroadCostDbReader::insertFullTree(const std::map<int, Languages*> &langList)
{
    if (!db) return;

    sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);
    for (const auto &langPair : langList)
    {
        int langId = langPair.first;
        const Languages *lang = langPair.second;
        insertLanguage(langId, lang);

        for (const auto &chPair : lang->channelMap())
        {
            int chId = chPair.first;
            const Chanels *ch = chPair.second;
            insertChannel(chId, langId, ch);

            for (const auto &progPair : ch->programMap())
            {
                const Programs *prog = progPair.second;
                insertProgram(chId, prog);
            }
        }
    }
    sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr);
}

bool BroadCostDbReader::loadPackages(std::map<std::string, Pakages*> &pakages,
                                     const std::map<int, Languages*> &languages)
{
    if (!db) return false;

    sqlite3_stmt *stmt;

    const char *sql = "SELECT PackageName, Amount FROM Packages;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string pakName = (const char*)sqlite3_column_text(stmt, 0);
        int amount = sqlite3_column_int(stmt, 1);

        Pakages *pkg = new Pakages();
        pkg->setPakageName(pakName);
        pkg->setPakageAmmount(amount);
        pakages[pakName] = pkg;
    }
    sqlite3_finalize(stmt);

    const char *sqlChannels = "SELECT PackageName, ChannelId FROM PackageChannels;";
    if (sqlite3_prepare_v2(db, sqlChannels, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string pakName = (const char*)sqlite3_column_text(stmt, 0);
        int chId = sqlite3_column_int(stmt, 1);

        auto pkgIt = pakages.find(pakName);
        if (pkgIt == pakages.end()) continue;

        Chanels* realCh = findChannelById(chId, languages);

        if (realCh)
        {
            pkgIt->second->addChannel(realCh);
        }
        else
        {
            std::cerr << "Channel ID " << chId
                      << " not found in DB for package '"
                      << pakName << "'. Added as Unknown.\n";
            Chanels *dummy = new Chanels(chId, "Unknown", 0.0);
            pkgIt->second->addChannel(dummy);
        }
    }

    sqlite3_finalize(stmt);
    return true;
}


bool BroadCostDbReader::loadCustomerSubscriptions(std::map<std::string, Customer*>& customers,
                                                  std::map<std::string, Pakages*>& pakages)
{
    if (!db) return false;

    sqlite3_stmt* stmt;
    const char* sql = "SELECT CustomerId, PackageName FROM CustomerPackages;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string custId = (const char*)sqlite3_column_text(stmt, 0);
        std::string pakName = (const char*)sqlite3_column_text(stmt, 1);

        auto custIt = customers.find(custId);
        auto pakIt  = pakages.find(pakName);

        if (custIt != customers.end() && pakIt != pakages.end())
        {
            custIt->second->addSubscribedPackage(pakName, pakIt->second);

        }
    }

    sqlite3_finalize(stmt);
    return true;
}
Chanels* BroadCostDbReader::findChannelById(
    int chId,
    const std::map<int, Languages*>& languages)
{
    for (const auto& langPair : languages)
    {
        const auto& chMap = langPair.second->channelMap();
        auto it = chMap.find(chId);
        if (it != chMap.end())
        {
            return it->second;
        }
    }
    return nullptr;
}




BroadCostDbReader::BroadCostDbReader()
{
    db = nullptr;
}

BroadCostDbReader::~BroadCostDbReader()
{
    closeFile();
}

BroadCostDbReader* BroadCostDbReader::instance()
{
    if (m_dbreader == nullptr)
        m_dbreader = new BroadCostDbReader;
    return m_dbreader;
}
