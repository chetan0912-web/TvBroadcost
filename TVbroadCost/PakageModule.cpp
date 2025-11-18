#include "PakageModule.h"

PakageModule::PakageModule(LanguageModule *languageModule, BroadCostDbReader *dbReader)
    : m_dbReader(dbReader)
{
    if (!m_dbReader)
    {
        std::cerr << "PakageModule: DB Reader is NULL!\n";
        return;
    }

    if (!languageModule)
    {
        std::cerr << "PakageModule: LanguageModule is NULL!\n";
        return;
    }

    m_languageList = &languageModule->getLanguageList();

    if (m_languageList)
        m_dbReader->loadPackages(m_pakageList, *m_languageList);
}

PakageModule::~PakageModule()
{
    for (auto &p : m_pakageList)
        delete p.second;

    m_pakageList.clear();
}
