#include "Customer.h"
#include "DataModule.h"
#include <iomanip>

#include "CustomerModule.h"


using namespace std;

Customer::Customer(const std::string &Id, const std::string &password,
                   const std::string &name, const std::string phoneNo)
{
    setPersonId(Id);
    setPassword(password);
    setName(name);
    setPhoneNo(phoneNo);
}

Customer::Customer() {}

Customer::~Customer() {}

bool Customer::customerMenu(DataModule *broadCost)
{
    int choice = 0;
    while (choice != 5)
    {
        cout << "\n========= Customer Menu =========\n";
        cout << "1. View All Packages\n";
        cout << "2. Subscribe to a Package\n";
        cout << "3. View My Subscribed Packages\n";
        cout << "4. View Package Details\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!\n";
            continue;
        }
        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1:
        {

            displayPakage(broadCost);
            break;
        }
        case 2:
        {
            addPakage(broadCost);
            break;
        }
        case 3:
        {

            pakageDetails();
            break;
        }
        case 4:
        {
            displayPakageDetails();
            break;
        }
        case 5:
        {
            cout << "Exiting customer menu...\n";
            return false;
        }
        default:
            cout << "Invalid choice, try again.\n";
        }
    }
    return true;
}

void Customer::addPakage(DataModule *broadCost)
{
    string pakName;
    cout << "Enter package name: ";
    getline(cin, pakName);

    broadCost->getCustomerModule()->subscribe(getPersonId(), pakName);

}

void Customer::displayPakage(DataModule *broadCost)
{
    broadCost->getCustomerModule()->showAllPackages();
}

void Customer::pakageDetails()
{
    cout << "\nYour Packages:\n";
    for (auto &p : m_subscribedPakages)
    {
        cout << " - " << p.first
             << " (Amount: " << p.second->getPakageAmmount() << ")\n";
    }
}

void Customer::displayPakageDetails()
{
    cout << "Enter package name to view details: ";
    string pakName;
    getline(cin, pakName);

    auto it = m_subscribedPakages.find(pakName);
    if (it == m_subscribedPakages.end())
    {
        cout << "Package not found in your subscription list.\n";
        return;
    }

    Pakages *pkg = it->second;
    pkg->displayChannelIds();
}
void Customer::addSubscribedPackage(const std::string &pakName, Pakages *pkg)
{
    m_subscribedPakages[pakName] = pkg;
}
