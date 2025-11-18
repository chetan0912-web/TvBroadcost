#ifndef CHANELS_H
#define CHANELS_H

#include <map>
#include "Programs.h"

class Chanels
{
public:
    Chanels();
    Chanels(int id, std::string name, double price);
    ~Chanels();

    int getChenelId() const;
    std::string getChanelName() const;
    double getChannelPrice() const;

    void setChanelName(std::string name);
    void setChannelPrice(double price);

    void setProgramList(int progId, Programs *prog);

    std::map<int, Programs*> &programMap();
    const std::map<int, Programs*> &programMap() const;

    void updatePrograms(int programId, std::string newProgramName,
                        std::string newType, std::string newTime);

    void displayPrograms();
    void displayChannelDetails();

    void removeProgram(int progId);
    void clearAllPrograms();

private:
    int m_chanelId;
    std::string m_chanelName;
    double m_chanelPrice;
    std::map<int, Programs*> m_programList;
};

#endif // CHANELS_H
