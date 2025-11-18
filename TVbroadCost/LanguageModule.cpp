#include "LanguageModule.h"

LanguageModule::LanguageModule(BroadCostDbReader *dbReader)
    : m_dbReader(dbReader)
{
    if (m_dbReader)
    {
        m_dbReader->readData(m_languageList);
    }
}

LanguageModule::~LanguageModule()
{
    for (auto &p : m_languageList) delete p.second;
    m_languageList.clear();
}

void LanguageModule::init()
{
    if (m_dbReader)
        m_dbReader->readData(m_languageList);
}

void LanguageModule::languageMenu()
{
    cout << "--------------------------------\n"
         << "           MAIN MENU            \n"
         << "--------------------------------\n";

    while (true)
    {
        int choice;
        while(true)
        {
            cout << "1. Create Language\n"
                 << "2. Delete Language\n"
                 << "3. Manage In Channel\n"
                 << "4. Display All\n"
                 << "5. Manage Pakage\n"
                 << "6. Exit\n"
                 << "Choice: ";
            if (cin >> choice) break;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice!\n";
        }
        cin.ignore(1000, '\n');

        if (choice == EXIT_)
        {
            if (m_dbReader) m_dbReader->insertFullTree(m_languageList);
            cout << "Goodbye! All data saved.\n";
            break;
        }

        switch (choice)
        {
        case CREATE_LANGUAGE:
        {
            createLanguage();
            break;
        }
        case DELETE_LANGUAGE:
        {
            deleteLanguage();
            break;
        }
        case MANAGE_IN_CHANNEL:
        {
            cout << "Language ID: ";
            int langId;
            if (!(cin >> langId))
            {
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Invalid\n";
                break;
            }
            cin.ignore(1000,'\n');

            if (m_languageList.find(langId) == m_languageList.end())
            {
                cout << "Language not found!\n";
                break;
            }
            mangaeInChanel(langId);
            break;
        }
        case DISPLAY_ALL:
        {
            displayLanguage();
            break;
        }
        default:
        {
            cout << "Invalid choice!\n";
            break;
        }
        }
    }
}

void LanguageModule::mangaeInChanel(int langId)
{
    auto itr = m_languageList.find(langId);
    if (itr == m_languageList.end())
    {
        cout << "Language not found!\n";
        return;
    }

    cout << "--------------------------------\n";
    cout << " MANAGE IN " << itr->second->language() << " LANGUAGE" << endl;
    cout << "--------------------------------\n";

    int choice;
    while (true)
    {
        while(true)
        {
            cout << "1. Add Channel\n"
                 << "2. Add Program\n"
                 << "3. Update Channel\n"
                 << "4. Update Program\n"
                 << "5. Delete chanel\n"
                 << "6. Delete program\n"
                 << "7. Exit\n"
                 << "Enter the choice: ";
            if (cin >> choice)
                break;
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid choice!\n";
        }
        cin.ignore(1000,'\n');

        if (choice == EXIT__)
            return;

        switch (choice)
        {
        case ADD_CHANEL:
        {
            addchannelInLanguage(langId);
            break;
        }
        case ADD_PROGRAM:
        {
            addProgramsInChannel(langId);
            break;
        }
        case UPDATE_CHANEL:
        {
            updateInchannel(langId);
            break;
        }
        case UPDATE_PROGRAM:
        {
            updateInProgram(langId);
            break;
        }
        case DELETE_CHANEL:
        {
            deleteChannel(langId);
            break;
        }
        case DELETE_PROGRAM:
        {
            deleteProgram(langId);
            break;
        }
        default:
        {
            cout << "Invalid choice!\n";
            break;
        }
        }
    }
}

void LanguageModule::createLanguage()
{
    int id;
    cout << "Language ID: ";
    while (!(cin >> id))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter a valid id: ";
    }
    cin.ignore(1000, '\n');

    if (m_languageList.count(id))
    {
        cout << "ID exists enter different Id!\n";
        return;
    }

    cout << "Language Name: ";
    string name;
    getline(cin, name);
    if (name.empty())
    {
        cout << "Invalid name\n";
        return;
    }

    if (isLangNamefound(name))
    {
        cout << "Language already exists!\n";
        return;
    }

    Languages *lang = new Languages(id, name);
    m_languageList[id] = lang;
    if (m_dbReader) m_dbReader->insertLanguage(id, lang);
    cout << "Language created & saved!\n";
}

void LanguageModule::addchannelInLanguage(int langId)
{
    int chId;
    double chanelPrice;
    string name;

    auto lit = m_languageList.find(langId);
    if (lit == m_languageList.end())
    {
        cout << "Language not found!\n";
        return;
    }

    cout << "Channel ID: ";
    while (!(cin >> chId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter a valid ID: ";
    }
    cin.ignore(1000, '\n');

    if (isChannelIdPresentInAnyLanguage(chId))
    {
        cout << "ID already exists!\n";
        return;
    }

    cout << "Channel Name: ";
    getline(cin, name);

    cout << "Set a price to Buy: ";
    while (!(cin >> chanelPrice))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter a valid price: ";
    }
    cin.ignore(1000, '\n');

    Chanels *ch = new Chanels(chId, name, chanelPrice);
    lit->second->setChannels(chId, ch);

    if (m_dbReader && m_dbReader->dbAddChannel(langId, chId, name, chanelPrice))
        cout << "Channel added & saved to DB!\n";
    else
        cout << "Failed to save channel to DB.\n";
}

void LanguageModule::displayLanguage()
{
    for (auto &p : m_languageList)
        cout << "\nLanguage: " << p.second->language() << " (ID: " << p.first << ")\n";

    cout << "Enter language Id to display channels: ";
    int langId;
    if (!(cin >> langId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid\n";
        return;
    }
    cin.ignore(1000, '\n');

    if (!m_languageList.count(langId))
    {
        cout << "Incorrect Id!\n";
        return;
    }
    auto findlang = m_languageList.find(langId);
    findlang->second->displayCh();
}

void LanguageModule::addProgramsInChannel(int langId)
{
    int chId;
    auto lang = m_languageList.find(langId);
    if (lang == m_languageList.end())
    {
        cout << "Language not found!\n";
        return;
    }

    cout << "Channel ID: ";
    if (!(cin >> chId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid\n";
        return;
    }
    cin.ignore(1000, '\n');

    Chanels *ch = lang->second->chanelFound(chId);
    if (!ch)
    {
        cout << "Channel not found!\n";
        return;
    }

    int pId;
    string name, st, et;

    cout << "Program ID: ";
    while (!(cin >> pId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter valid id: ";
    }
    cin.ignore(1000, '\n');

    cout << "Program Name: ";
    getline(cin, name);
    while(true)
    {
        cout << "Start (HH:MM): ";
        getline(cin, st);

        if(timeValidation(st))
            break;
        else
            cout << "Time formate is Invalid!" << endl;
    }

    while(true)
    {
        cout << "End (HH:MM): ";
        getline(cin, et);
        if(timeValidation(et))
            break;
        else
            cout << "Time formate is Invalid!" << endl;
    }

    Programs *prog = new Programs(pId, name, st, et);
    ch->setProgramList(pId, prog);
    lang->second->addprogram(chId, pId, prog);

    if (m_dbReader && m_dbReader->dbAddProgram(chId, pId, name, st, et))
        cout << "Program added and saved to DB.\n";
    else
        cout << "Failed to save program to DB.\n";
}

void LanguageModule::updateInchannel(int langId)
{
    cout << "Channel ID: ";
    int chId;
    if (!(cin >> chId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid\n";
        return;
    }
    cin.ignore(1000, '\n');

    auto lit = m_languageList.find(langId);
    if (lit == m_languageList.end())
    {
        cout << "Language not found!\n";
        return;
    }

    auto ch = lit->second->chanelFound(chId);
    if (!ch)
    {
        cout << "Channel not found!\n";
        return;
    }

    cout << "Enter the channel updated name: ";
    string newName;
    getline(cin, newName);
    ch->setChanelName(newName);
    cout << "Channel updated in memory. (DB update not implemented for name-only change)\n";
}

void LanguageModule::updateInProgram(int langId)
{
    auto langIt = m_languageList.find(langId);
    if (langIt == m_languageList.end())
    {
        cout << "Language not found!\n";
        return;
    }

    auto lang = langIt->second;
    cout << "Available Channels in " << lang->language() << ":\n";
    lang->displayForCustomer();

    cout << "Enter Channel ID to update a program: ";
    int chId;
    if (!(cin >> chId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input.\n";
        return;
    }
    cin.ignore(1000, '\n');

    Chanels *ch = lang->chanelFound(chId);
    if (!ch)
    {
        cout << "Channel not found!\n";
        return;
    }

    ch->displayPrograms();
    if (ch->programMap().empty())
    {
        cout << "No programs to update in this channel.\n";
        return;
    }

    cout << "Enter Program ID to update: ";
    int progId;
    if (!(cin >> progId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid Program ID.\n";
        return;
    }
    cin.ignore(1000, '\n');

    auto &progMap = ch->programMap();
    auto progIt = progMap.find(progId);
    if (progIt == progMap.end())
    {
        cout << "Program ID not found!\n";
        return;
    }

    string newName, newStart, newEnd;
    cout << "Enter new Program Name: ";
    getline(cin, newName);

    cout << "Enter new Start Time (HH:MM): ";
    getline(cin, newStart);
    if (!timeValidation(newStart))
    {
        cout << "Invalid start time format.\n";
        return;
    }

    cout << "Enter new End Time (HH:MM): ";
    getline(cin, newEnd);
    if (!timeValidation(newEnd))
    {
        cout << "Invalid end time format.\n";
        return;
    }

    progIt->second->setProgramName(newName);
    progIt->second->setStartTime(newStart);
    progIt->second->setEndTime(newEnd);
    cout << "Program updated in memory.\n";

    if (m_dbReader && m_dbReader->dbAddProgram(chId, progId, newName, newStart, newEnd))
        cout << "Program updated successfully in database.\n";
    else
        cout << "Program update failed to save in database.\n";
}

void LanguageModule::deleteLanguage()
{
    cout << "Language ID: ";
    int langId;
    if (!(cin >> langId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid\n";
        return;
    }
    cin.ignore(1000, '\n');

    auto lit = m_languageList.find(langId);
    if (lit == m_languageList.end())
    {
        cout << "Language not found!\n";
        return;
    }

    for (auto &ch : lit->second->channelMap()) delete ch.second;
    delete lit->second;
    m_languageList.erase(lit);

    if (m_dbReader && m_dbReader->deleteLanguage(langId))
        cout << "Language removed from DB.\n";
    else
        cout << "Language removed but DB delete may have failed.\n";
}

void LanguageModule::deleteChannel(int langId)
{
    cout << "Enter Channel ID to delete: ";
    int chId;
    if (!(cin >> chId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid\n";
        return;
    }
    cin.ignore(1000, '\n');

    auto lit = m_languageList.find(langId);
    if (lit == m_languageList.end())
    {
        cout << "Language not found!\n";
        return;
    }

    auto &channelMap = lit->second->channelMap();
    auto findChanel = channelMap.find(chId);
    if (findChanel == channelMap.end())
    {
        cout << "Channel not found!\n";
        return;
    }

    delete findChanel->second;
    channelMap.erase(findChanel);

    if (m_dbReader && m_dbReader->dbDeleteChannel(chId))
        cout << "Channel deleted from database.\n";
    else
        cout << "Failed to delete channel from database.\n";
}

void LanguageModule::deleteProgram(int langId)
{
    cout << "Channel ID: ";
    int chId;
    if (!(cin >> chId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid\n";
        return;
    }
    cin.ignore(1000, '\n');

    auto lit = m_languageList.find(langId);
    if (lit == m_languageList.end())
    {
        cout << "Language not found!\n";
        return;
    }
    auto channel = lit->second->chanelFound(chId);
    if (!channel)
    {
        cout << "Channel not found!\n";
        return;
    }

    channel->displayPrograms();

    cout << "Program ID to delete: ";
    int progId;
    if (!(cin >> progId))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid\n";
        return;
    }
    cin.ignore(1000, '\n');

    auto &progMap = channel->programMap();
    auto progIt = progMap.find(progId);
    if (progIt == progMap.end())
    {
        cout << "Program not found!\n";
        return;
    }

    delete progIt->second;
    progMap.erase(progIt);

    if (m_dbReader && m_dbReader->dbDeleteProgram(progId))
        cout << "Program deleted successfully from database.\n";
    else
        cout << "Failed to delete program from database.\n";
}

Chanels *LanguageModule::isChanefind(int chId)
{
    for (const auto& langPair : m_languageList)
    {
        auto chList = langPair.second->channelList();
        auto channelFind = chList.find(chId);
        if (channelFind != chList.end()) return channelFind->second;
    }
    return nullptr;
}

bool LanguageModule::isChannelIdPresentInAnyLanguage(int channelId) const
{
    for (const auto& langPair : m_languageList)
        if (langPair.second->findChannelPresent(channelId))
            return true;
    return false;
}

bool LanguageModule::isProgramIdPresentInAnyLanguage(int programId) const
{
    for (const auto& langPair : m_languageList)
    {
        for (const auto& chPair : langPair.second->channelMap())
        {
            if (chPair.second->programMap().find(programId) != chPair.second->programMap().end())
                return true;
        }
    }
    return false;
}

bool LanguageModule::isAlpha(const std::string &name) const
{
    for (char c : name)
    {
        if(!isalpha(c))
            return false;
    }
    return true;
}

bool LanguageModule::isLangNamefound(const std::string &name) const
{
    for (const auto &p : m_languageList)
        if (p.second->language() == name)
            return true;
    return false;
}

bool LanguageModule::timeValidation(const std::string &t) const
{
    if (t.size() != 5 || t[2] != ':')
        return false;
    int h = std::stoi(t.substr(0,2));
    int m = std::stoi(t.substr(3,2));

    return h >= 0 && h < 24 && m >= 0 && m < 60;
}

std::map<int, Languages*>& LanguageModule::getLanguageList()
{
    return m_languageList;
}
