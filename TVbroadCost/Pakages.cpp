#include "Pakages.h"
#include <iomanip>
using namespace std;

Pakages::Pakages() {}

int Pakages::getPakageAmmount() const
{
    return m_pakageAmmount;
}

void Pakages::setPakageAmmount(int newPakageAmmount)
{
    m_pakageAmmount = newPakageAmmount;
}

std::string Pakages::getPakageName() const
{
    return m_pakageName;
}

void Pakages::setPakageName(const std::string &newPakageName)
{
    m_pakageName = newPakageName;
}

void Pakages::addChannel(Chanels* newchanel)
{
    m_PakageChannelIst[newchanel->getChenelId()] = newchanel;
}

void Pakages::removeChannelId(int chId)
{
    auto it = m_PakageChannelIst.find(chId);
    if (it != m_PakageChannelIst.end())
    {
        m_PakageChannelIst.erase(it);
        cout << "Channel ID " << chId << " removed from package.\n";
    }
    else
    {
        cout << "Channel ID not found in package.\n";
    }
}

void Pakages::displayChannelIds() const
{
    if (m_PakageChannelIst.empty())
    {
        cout << "No channels added to this package.\n";
        return;
    }
    cout << "Channels in package \"" << m_pakageName << "\": ";
    cout << "\n==============================================\n"
         << " ch Id\t channelName\tchannelPrice\n"
         << "==============================================\n";
    for (auto const &id : m_PakageChannelIst)
    {
        cout << left << setw(10) << id.first
             << left << setw(20) << id.second->getChanelName()
             << id.second->getChannelPrice() << endl;
    }
    cout << endl;
}

std::map<int, Chanels *> Pakages::getChannelIds() const
{
    return m_PakageChannelIst;
}
