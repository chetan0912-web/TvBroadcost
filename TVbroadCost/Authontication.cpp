#include "Authontication.h"
#include <iostream>

using namespace std;

Authontication::Authontication() : m_dbReader(nullptr), m_loggedCustomer(nullptr) {}

Authontication::Authontication(std::map<string, Admin *> &adminList,
                               std::map<string, Customer *> &customerList,
                               BroadCostDbReader *dbReader)
    : m_adminList(adminList),
    m_customerList(customerList),
    m_dbReader(dbReader),
    m_loggedCustomer(nullptr)
{}

bool Authontication::menu(int personType)
{
    static bool loaded = false;
    if (!loaded && m_dbReader)
    {
        m_dbReader->loadAdmins(m_adminList);
        m_dbReader->loadCustomers(m_customerList);
        loaded = true;
    }

    while (true)
    {
        int choice = 0;

        cout << "1. Login\n"
             << "2. Register\n"
             << "3. EXIT\n"
             << "Enter the choice: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }
        cin.ignore(1000, '\n');

        if (choice == EXIT)
            return false;

        switch (choice)
        {
        case LOGIN:
            if (personType == 1)
                return adminLogin();
            else
                return customerLogin();
        case REGISTER:
            if (personType == 1)
                adminRegister();
            else
                customerRegister();
            break;
        default:
            cout << "Enter a valid choice.\n";
        }
    }
}

bool Authontication::adminLogin()
{
    cout << "\n--------------------------------\n";
    cout << "           ADMIN LOGIN          \n";
    cout << "--------------------------------\n";
    string inputId, inputPass;
    int count = 3;
    while(count !=0)
    {
        cout << "Enter Admin ID: ";
        getline(cin, inputId);
        if(isDigit(inputId))
            break;
        else
        {
            count--;
            cout << "Only digits are allowed! " << count << " attempt left" << endl;
        }

    }
    if(count == 0)
        return false;

    cout << "Enter Password: ";
    getline(cin, inputPass);

    auto it = m_adminList.find(inputId);
    if (it != m_adminList.end() && it->second->getPassword() == inputPass)
    {
        cout << "\nWelcome " << it->second->getName() << "!\n\n";
        return true;
    }
    cout << "\nWrong ID or Password.\n\n";
    return false;
}

void Authontication::adminRegister()
{
    string newId, newPass, newName, newPhone;
    while(true)
    {
        cout << "Enter Admin ID: ";
        getline(cin, newId);

        if(isDigit(newId))
            break;
        else
            cout << "Only digits are allowed!" << endl;
    }
    cout << "Enter Name: ";
    getline(cin, newName);
    cout << "Enter Password: ";
    getline(cin, newPass);

    while(true)
    {
        cout << "Enter Phone No: ";
        getline(cin, newPhone);

        if(phoneNoValidation(newPhone))
            break;
        else
            cout << "Invalid phone number. Must be 10 digits\n" << endl;
    }

    Admin newAdmin(newId, newPass, newName, newPhone);

    if (m_dbReader && m_dbReader->addAdmin(newAdmin))
    {
        m_adminList[newId] = new Admin(newAdmin);
        cout << "Admin registered and added to database.\n";
    }
    else
    {
        cout << "Failed to register Admin.\n";
    }
}

bool Authontication::customerLogin()
{
    cout << "\n--------------------------------\n";
    cout << "        CUSTOMER LOGIN          \n";
    cout << "--------------------------------\n";

    string inputId, inputPass;

    int count=3;

    while(count)
    {
        cout << "Enter Customer ID: ";
        getline(cin, inputId);

        if(isDigit(inputId))
            break;
        else
        {
            cout << "Only digits are allowed! " << count
                 << " attempt left!" << endl;
            count--;
        }

    }
    if(!count)
    {
        cout << "reatched Maximum attempts!" << endl;
        return false;
    }

    cout << "Enter Password: ";
    getline(cin, inputPass);

    auto it = m_customerList.find(inputId);
    if (it != m_customerList.end() && it->second->getPassword() == inputPass)
    {
        cout << "\nWelcome " << it->second->getName() << "!\n\n";
        m_loggedCustomer = it->second;
        return true;
    }
    cout << "\nWrong ID or Password.\n\n";
    return false;
}

void Authontication::customerRegister()
{
    string newId, newPass, newName, newPhone;
    int count = 3;

    while(count)
    {
        cout << "Enter Customer ID: ";
        getline(cin, newId);

        if(isDigit(newId))
            break;
        else
            cout << "Only digits are allowed! "
                 << count << " attempt left" << endl;count--;
    }
    if(!count)
    {
        cout << "Attempt expired!" << endl;
        return;
    }
    else
        count = 3;

    cout << "Enter Name: ";
    getline(cin, newName);
    cout << "Enter Password: ";
    getline(cin, newPass);

    while(count)
    {
        cout << "Enter Phone No: ";
        getline(cin, newPhone);

        if(phoneNoValidation(newPhone))
            break;
        else
            cout << "Invalid phone number. Must be 10 digits\n"
                 << count << " attempt left" << endl;count--;
    }
    if(!count)
    {
        cout << "Attempt expired!" << endl;
        return;
    }

    Customer newCust(newId, newPass, newName, newPhone);

    if (m_dbReader && m_dbReader->addCustomer(newCust))
    {
        m_customerList[newId] = new Customer(newCust);
        cout << "Customer registered and added to database.\n";
    }
    else
    {
        cout << "Failed to register Customer.\n";
    }
}

const std::map<string, Customer *> &Authontication::getCustomerList() const
{
    return m_customerList;
}

void Authontication::setCustomerList(Customer *newCustomer)
{
    if (newCustomer)
        m_customerList[newCustomer->getPersonId()] = newCustomer;
}

const std::map<string, Admin *> &Authontication::getAdminList() const
{
    return m_adminList;
}

void Authontication::setAdminList(Admin *newAdmin)
{
    if (newAdmin)
        m_adminList[newAdmin->getPersonId()] = newAdmin;
}

Customer *Authontication::getLoggedCustomer() const
{
    return m_loggedCustomer;
}

bool Authontication::isDigit(string newId)
{
    for(auto i : newId)
    {
        if(!isdigit(i))
            return false;

    }
    return true;
}

bool Authontication::phoneNoValidation(const string phoneNo) const
{
    if (phoneNo.size() != 10)
        return false;
    for (char c : phoneNo)
        if (!isdigit((c)))
            return false;
    return true;
}
