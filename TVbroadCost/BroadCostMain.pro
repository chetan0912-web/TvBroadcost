TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Admin.cpp \
        Authontication.cpp \
        BroadCostDbReader.cpp \
        Chanels.cpp \
        Customer.cpp \
        CustomerModule.cpp \
        DataModule.cpp \
        FileReader.cpp \
        Interface.cpp \
        LanguageModule.cpp \
        Languages.cpp \
        PakageModule.cpp \
        Pakages.cpp \
        PersonDetails.cpp \
        Programs.cpp \
        main.cpp \
        sqlite3.c

DISTFILES += \
    broadcast.db

HEADERS += \
    Admin.h \
    Authontication.h \
    BroadCostDbReader.h \
    Chanels.h \
    Customer.h \
    CustomerModule.h \
    DataModule.h \
    FileReader.h \
    Interface.h \
    LanguageModule.h \
    Languages.h \
    PakageModule.h \
    Pakages.h \
    PersonDetails.h \
    Programs.h \
    sqlite3.h \
    sqlite3ext.h
