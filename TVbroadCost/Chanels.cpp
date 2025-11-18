#include "Chanels.h"
#include <iomanip>
using namespace std;

Chanels::Chanels()
{
    m_chanelId = 0;
    m_chanelName = "";
    m_chanelPrice = 0.0;
}

Chanels::Chanels(int id, std::string name, double price)
{
    m_chanelId = id;
    m_chanelName = name;
    m_chanelPrice = price;
}

Chanels::~Chanels()
{
    for (auto &p : m_programList)
    {
        delete p.second;
    }
    m_programList.clear();
}

int Chanels::getChenelId() const
{
    return m_chanelId;
}

std::string Chanels::getChanelName() const
{
    return m_chanelName;
}

double Chanels::getChannelPrice() const
{
    return m_chanelPrice;
}

void Chanels::setChanelName(std::string name)
{
    m_chanelName = name;
}

void Chanels::setChannelPrice(double price)
{
    m_chanelPrice = price;
}

void Chanels::setProgramList(int progId, Programs *prog)
{
    m_programList[progId] = prog;
}

std::map<int, Programs*> &Chanels::programMap()
{
    return m_programList;
}

const std::map<int, Programs*> &Chanels::programMap() const
{
    return m_programList;
}

void Chanels::updatePrograms(int programId, std::string newProgramName,
                             std::string newStartTime, std::string newEndTime)
{
    auto it = m_programList.find(programId);
    if (it != m_programList.end())
    {
        it->second->setProgramName(newProgramName);
        it->second->setStartTime(newStartTime);
        it->second->setEndTime(newEndTime);
    }
    else
    {
        Programs *newProg = new Programs(programId, newProgramName, newStartTime, newEndTime);
        m_programList[programId] = newProg;
    }
}

void Chanels::displayPrograms()
{
    if (m_programList.empty())
    {
        cout << "No programs available for this channel.\n";
        return;
    }

    cout << "\nPrograms under Channel: " << m_chanelName << "\n";
    cout << left << setw(10) << "Prog ID"
         << setw(25) << "Program Name"
         << setw(15) << "Start"
         << setw(15) << "End"
         << setw(10) << "Duration" << endl;
    cout << "-------------------------------------------------------------------\n";

    for (const auto &p : m_programList)
    {
        cout << left << setw(10) << p.second->getProgramId()
        << setw(25) << p.second->getProgramName()
        << setw(15) << p.second->getStartTime()
        << setw(15) << p.second->getEndTime()
        << setw(10) << p.second->getDuration()
        << endl;
    }
}

void Chanels::displayChannelDetails()
{
    cout << left << setw(5) << m_chanelId
         << setw(25) << m_chanelName
         << setw(10) << m_chanelPrice << endl;
}

void Chanels::removeProgram(int progId)
{
    auto it = m_programList.find(progId);
    if (it != m_programList.end())
    {
        delete it->second;
        m_programList.erase(it);
    }
}

void Chanels::clearAllPrograms()
{
    for (auto &p : m_programList)
    {
        delete p.second;
    }
    m_programList.clear();
}
