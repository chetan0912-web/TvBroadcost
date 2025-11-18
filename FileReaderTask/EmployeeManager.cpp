#include <iomanip>
#include "EmployeeManager.h"

EmployeeManager::EmployeeManager()
{

    m_fileReaderType =
        {
            {1,new EmployeeCSVReader},
            {2,new EmployeeTextReader},
            {3,new EmployeeDbReader}
        };

    m_fileMap =
        {
            {READ_FROM_CSV,  "employee.csv"},
            {READ_FROM_TEXT, "employees.text"},
            {READ_FROM_DB,   "employee.db"}
        };
    cout << "Manager constructer is called" << endl;

}

EmployeeManager::~EmployeeManager()
{
    cout << "Manager Distructer is called" << endl;




    if(m_fileReaderType[READ_FROM_CSV] != nullptr)
    {

        delete m_fileReaderType[READ_FROM_CSV];
        cout << "\nCSV data deleted\n" << endl;
    }
    else
    {
        cout << "\nCSV File memory is not allocated.\n" << endl;
    }

    if(m_fileReaderType[READ_FROM_TEXT] != nullptr)
    {
        delete m_fileReaderType[READ_FROM_TEXT];
        cout << "\nTEXT data deleted\n" << endl;
    }
    else
    {
        cout << "\nTEXT File memory is not allocated.\n" << endl;
    }

    if(m_fileReaderType[READ_FROM_DB] != nullptr)
    {
        delete m_fileReaderType[READ_FROM_DB];
        cout << "\nDB data deleted\n" << endl;
    }
    else
    {
        cout << "\nDB File memory is not allocated.\n" << endl;
    }

}

void EmployeeManager::display()
{
    int choice;
    while(true)
    {
        cout << "1. display from  CSV\n"
             << "2. display from TEXT\n"
             << "3. display from DB\n"
             << "5. EXIT.\n"
             << "Enter the choice : ";
        cin >> choice;

        if (choice == EXIT)
        {
            cout << "Exiting\n";
            return;
        }

        for (auto &entry : m_fileReaderType)
        {
            if (entry.first == choice)
            {
                entry.second->display();
            }
        }

    }
}

void EmployeeManager::menu()
{
    int choice;
    while(true)
    {
        cout << "1. Fetch The Date.\n"
             << "2. Display.\n"
             << "3. EXIT\n"
             << "Enter the Choice : ";
        cin >> choice;

        if(choice == 1)
        {
            ReadMenu();
        }
        else if(choice == 2)
        {
            display();
        }
        else if( choice == 3)
        {
            cout << "Exiting" << endl;
            return;
        }
        else
        {
            cout << "\nEnter the correct choice.\n" << endl;
        }
    }
}

void EmployeeManager::operator =(const EmployeeManager& empManager)
{
    cout << "Manager assign constructer is called" << endl;
}

EmployeeManager::EmployeeManager(const EmployeeManager& empManager)
{
    cout << "Manager copy constructer is called" << endl;
}

void EmployeeManager::ReadMenu()
{
    int choice;


    while (true)
    {
        cout << "1. Read From CSV\n"
             << "2. Read From TEXT\n"
             << "3. Read From DB\n"
             << "4. EXIT\n"
             << "Enter the choice : ";
        cin >> choice;

        if (choice == EXIT)
        {
            cout << "Exiting\n";
            return;
        }
        bool isFound=false;

        for (auto &entry : m_fileReaderType)
        {
            if (entry.first == choice)
            {
                isFound=true;

                cout << "Reading data\n";
                entry.second->readFile(m_fileMap[choice]);
                break;
            }
        }
        if(!isFound)
        {
            cout << "\ndata is not found.\n" << endl;
        }
    }
}




