#include "Programs.h"

Programs::Programs()
    : m_programName(""), m_startTime(""), m_endTime(""), m_duration(0), m_programId(0)
{}

Programs::~Programs() {}

Programs::Programs(int newProgramId, string newProgramName, string newStartTime, string newEndTime)
    : m_programId(newProgramId), m_programName(std::move(newProgramName)),
    m_startTime(std::move(newStartTime)), m_endTime(std::move(newEndTime)), m_duration(0) {}

Programs::Programs(string newProgramName, int newDuration)
    : m_programName((newProgramName)), m_duration(newDuration), m_programId(0) {}

void Programs::setProgramName(string newProgramName)
{
    m_programName = (newProgramName);
}
void Programs::setStartTime(string newStartTime)
{
    m_startTime = (newStartTime);
}
void Programs::setEndTime(string newEndTime)
{
    m_endTime =(newEndTime);
}

void Programs::setDuration(int newDuration)
{
    m_duration = newDuration;
}

void Programs::setProgranId(int newProgramId)
{
    m_programId = newProgramId;
}

string Programs::getProgramName() const
{
    return m_programName;
}

string Programs::getStartTime() const
{
    return m_startTime;
}

string Programs::getEndTime() const
{
    return m_endTime;
}

int Programs::getDuration() const
{
    return m_duration;
}

int Programs::getProgramId() const
{
    return m_programId;
}

void Programs::display()
{
    cout << "Program: " << m_programName
         << " | Start: " << m_startTime
         << " | End: " << m_endTime
         << " | Duration: " << m_duration << endl;
}
