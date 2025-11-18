#include "EmployeeDbReader.h"
#include <sqlite3.h>

EmployeeDbReader::EmployeeDbReader()
{
    std::cout << "DB Reader Constructor called" << std::endl;
}

EmployeeDbReader::~EmployeeDbReader()
{
    std::cout << "DB Reader Destructor called" << std::endl;
}

void EmployeeDbReader::operator =(const EmployeeDbReader &emp)
{
    cout << "Db assign operater is called" << endl;
}

EmployeeDbReader::EmployeeDbReader(const EmployeeDbReader &emp)
{
    cout << "Db copy constructer is called" << endl;
}

void EmployeeDbReader::readFile(const string& filename)
{
    sqlite3 *db = nullptr;
    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_open(filename.c_str(), &db) != SQLITE_OK)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    const char *sql = "SELECT EMPLOYID, EMPLOYNAME, DESIGNATION FROM EMPLOYEES;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string id       = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string name     = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string desig    = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        Employee *emp = new Employee(id, name, desig);
        setEmployees(emp);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    std::cout << "Employee data read from database successfully." << std::endl;
}
