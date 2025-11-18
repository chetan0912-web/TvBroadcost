#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <iostream>
#include <map>
#include "Chanels.h"

class Languages
{
public:
    Languages();
    ~Languages();
    Languages(int lId, std::string language);

    void createChannel();
    void updatechanelname(int chId);

    int languageId() const;
    std::string language() const;

    Chanels* chanelFound(int chanelId);
    void addprogram(int chanelId, int programId, Programs *program);
    void updateProgram(int chanelId, int programId,
                       std::string programName, std::string sTime, std::string eTime);

    void setChannels(int chId, Chanels *channel);
    std::map<int, Chanels*> channelList() const;

    std::map<int, Chanels*> &channelMap();
    const std::map<int, Chanels*> &channelMap() const;

    void setLanguageId(int newLanguageId);
    void setLanguage(const std::string &newLanguage);

    bool findChannelPresent(int channelId) const;
    std::map<int, Chanels*> channels() const;

    void displayCh();
    void displayForCustomer();

private:
    int m_languageId;
    std::string m_language;
    std::map<int, Chanels*> m_channelList;
};

#endif // LANGUAGES_H
