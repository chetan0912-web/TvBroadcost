#ifndef PAKAGEMODULE_H
#define PAKAGEMODULE_H

#include <iostream>
#include <map>
#include "Pakages.h"
#include "BroadCostDbReader.h"
#include "LanguageModule.h"

class PakageModule
{
public:
    PakageModule(LanguageModule *languageModule, BroadCostDbReader *dbReader);
    ~PakageModule();

    void managePakage();
    void DisplayPakage();

private:
    BroadCostDbReader *m_dbReader = nullptr;
    std::map<std::string, Pakages*> m_pakageList;
    std::map<int, Languages*> *m_languageList = nullptr;

    bool isChannelIdPresentInAnyLanguage(int channelId) const;
    Chanels* isChanefind(int chId);
};

#endif // PAKAGEMODULE_H
