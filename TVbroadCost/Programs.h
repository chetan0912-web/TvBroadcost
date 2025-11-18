#ifndef PROGRAMS_H
#define PROGRAMS_H

#include <iostream>

using namespace std;

class Programs
{
public:
    Programs();
    ~Programs();

    Programs(int newProgramId, std::string newProgramName, std::string newStartTime, std::string newEndTime);
    Programs(std::string newProgramName, int newDuration);

    void setProgramName(std::string newProgramName);
    void setStartTime(std::string newStartTime);
    void setEndTime(std::string newEndTime);
    void setDuration(int newDuration);
    void setProgranId(int newProgramId);

    std::string getProgramName() const;
    std::string getStartTime() const;
    std::string getEndTime() const;
    int getDuration() const;
    int getProgramId() const;

    void display();

private:
    int m_programId = 0;
    std::string m_programName;
    std::string m_startTime;
    std::string m_endTime;
    int m_duration = 0;
};

#endif // PROGRAMS_H
