 #ifndef PAKAGES_H
#define PAKAGES_H

#include <iostream>
#include <map>
#include "Chanels.h"

class Pakages
{
public:
    Pakages();

    int getPakageAmmount() const;
    void setPakageAmmount(int newPakageAmmount);

    std::string getPakageName() const;
    void setPakageName(const std::string &newPakageName);

    void addChannel(Chanels *newchanel);
    void removeChannelId(int chId);
    void displayChannelIds() const;

    std::map<int, Chanels*> getChannelIds() const;

private:
    int m_pakageAmmount = 0;
    std::string m_pakageName;
    std::map<int, Chanels*> m_PakageChannelIst;
};

#endif // PAKAGES_H
