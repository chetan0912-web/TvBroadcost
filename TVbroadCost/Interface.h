#ifndef Interface_H
#define Interface_H

#include <iostream>
#include "Authontication.h"
#include "DataModule.h"

class Interface
{
    enum InterfaceType
    {
        ADMIN = 1,
        CUSTOMER,
        EXIT
    };

public:
    Interface();
    ~Interface();

    void AuthonticationMenu();

private:

    DataModule *m_dataModule;
    Authontication m_auth;
};

#endif // Interface_H
