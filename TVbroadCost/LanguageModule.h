#ifndef LANGUAGEMODULE_H
#define LANGUAGEMODULE_H

#include <iostream>
#include <map>
#include "BroadCostDbReader.h"

class BroadCostDbReader;
class LanguageModule
{
public:
    enum Mani_Menu
    {
        CREATE_LANGUAGE=1,
        DELETE_LANGUAGE,
        MANAGE_IN_CHANNEL,
        DISPLAY_ALL,
        MANAGE_PAKAGE,
        EXIT_
    };

    enum chanelList
    {
        ADD_CHANEL=1,
        ADD_PROGRAM,
        UPDATE_CHANEL,
        UPDATE_PROGRAM,
        DELETE_CHANEL,
        DELETE_PROGRAM,
        EXIT__
    };

    explicit LanguageModule(BroadCostDbReader *dbReader = nullptr);
    ~LanguageModule();

    void init();
    void languageMenu();
    void mangaeInChanel(int langId);

    void createLanguage();
    void addchannelInLanguage(int langId);
    void displayLanguage();
    void addProgramsInChannel(int langId);
    void updateInchannel(int langId);
    void updateInProgram(int langId);
    void deleteLanguage();
    void deleteChannel(int langId);
    void deleteProgram(int langId);

    std::map<int, Languages*>& getLanguageList();

private:
    Chanels* isChanefind(int chId);
    bool isChannelIdPresentInAnyLanguage(int channelId) const;
    bool isProgramIdPresentInAnyLanguage(int programId) const;
    bool isAlpha(const std::string &name) const;
    bool isLangNamefound(const std::string &name) const;
    bool timeValidation(const std::string &t) const;

    BroadCostDbReader *m_dbReader = nullptr;
    std::map<int, Languages*> m_languageList;

};

#endif // LANGUAGEMODULE_H
