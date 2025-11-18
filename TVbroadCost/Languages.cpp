#include "Languages.h"
#include <iomanip>

Languages::Languages() {}
Languages::~Languages() {}

Languages::Languages(int lId, string language)
    : m_languageId(lId), m_language(std::move(language)) {}

void Languages::createChannel()
{
    cout << "Channel is created"<< endl;
}

void Languages::updatechanelname(int chId)
{
    auto chanelId = m_channelList.find(chId);
    if (chanelId == m_channelList.end())
    {
        cout << "Channel not found\n";
        return;
    }
    string newChanelName;
    getline(cin, newChanelName);
    chanelId->second->setChanelName(newChanelName);
    cout << "Chanel name is updated" << endl;
}

int Languages::languageId() const
{
    return m_languageId;
}
string Languages::language() const
{
    return m_language;
}

Chanels* Languages::chanelFound(int chanelId)
{
    auto itr = m_channelList.find(chanelId);
    if (itr == m_channelList.end())
        return nullptr;
    return itr->second;
}

void Languages::addprogram(int chanelId, int programId, Programs *program)
{
    auto ch = m_channelList.find(chanelId);
    if (ch != m_channelList.end()) ch->second->setProgramList(programId, program);
}

void Languages::updateProgram(int chanelId, int programId, string programName, string sTime, string eTime)
{
    auto findChannel = m_channelList.find(chanelId);
    if (findChannel == m_channelList.end())
    {
        cout << "id is not found" << endl;
        return;
    }
    findChannel->second->updatePrograms(programId, programName, sTime, eTime);
}

void Languages::setChannels(int chId, Chanels* channel)
{
    m_channelList[chId] = channel;
}

map<int, Chanels *> Languages::channelList() const
{
    return m_channelList;
}

std::map<int, Chanels *> &Languages::channelMap()
{
    return m_channelList;
}

const std::map<int, Chanels *> &Languages::channelMap() const
{
    return m_channelList;
}


void Languages::setLanguageId(int newLanguageId)
{
    m_languageId = newLanguageId;
}

void Languages::setLanguage(const string &newLanguage)
{
    m_language = newLanguage;
}

bool Languages::findChannelPresent(int channelId) const
{
    return m_channelList.find(channelId) != m_channelList.end();
}

map<int, Chanels *> Languages::channels() const
{
    return m_channelList;
}

void Languages::displayCh()
{
    if (m_channelList.empty())
    {
        cout << "channel List is Not found!" << endl;
        return;
    }
    for (auto i: m_channelList)
    {
        cout << "==============================================\n"
             << " ch Id\t channelName\tchannelPrice\n";
        cout << left << setw(10) << i.first
             << left << setw(20) << i.second->getChanelName()
             << i.second->getChannelPrice() << endl;
        cout << "==============================================\n";
        cout << endl;
        i.second->displayPrograms();
    }
}

void Languages::displayForCustomer()
{
    if (m_channelList.empty())
    {
        cout << "channel List is Not found!" << endl;
        return;
    }
    cout << "==============================================\n"
         << " ch Id\t channelName\tchannelPrice\n"
         << "==============================================\n";
    for (auto i: m_channelList)
    {
        cout << left << setw(10) << i.first
             << left << setw(20) << i.second->getChanelName()
             << i.second->getChannelPrice() << endl;
    }
}
