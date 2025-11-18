#include "Interface.h"
#include "Customer.h"
#include "LanguageModule.h"
#include "CustomerModule.h"

using namespace std;

Interface::Interface()
{
    m_dataModule = DataModule::dataModuleInstance();
    if (!m_dataModule)
    {
        cerr << "Error: DataModule pointer is NULL!\n";
        exit(1);
    }

    m_auth = Authontication(
        m_dataModule->getAdminList(),
        m_dataModule->getCustomerList(),
        m_dataModule->getDbReader());
}

Interface::~Interface() {}

void Interface::AuthonticationMenu()
{
    while (true)
    {
        int choice = 0;
        cout << "\n------ LOGIN MENU ------\n";
        cout << "1. Admin\n";
        cout << "2. Customer\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore(1000, '\n');

        if (choice == EXIT)
            return;

        switch (choice)
        {
        case ADMIN:
            if (m_auth.menu(ADMIN))
            {
                if (m_dataModule->getLanguageModule())
                    m_dataModule->getLanguageModule()->languageMenu();
            }
            break;

        case CUSTOMER:
            if (m_auth.menu(CUSTOMER))
            {
                Customer *logged = m_auth.getLoggedCustomer();
                if (logged)
                    logged->customerMenu(m_dataModule);
            }
            break;

        default:
            cout << "Invalid choice.\n";
        }
    }
}
