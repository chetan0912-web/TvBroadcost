TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Employee.cpp \
        EmployeeCSVReader.cpp \
        EmployeeDbReader.cpp \
        EmployeeManager.cpp \
        EmployeeTextReader.cpp \
        FileReader.cpp \
        main.cpp \
        sqlite3.c

HEADERS += \
    Employee.h \
    EmployeeCSVReader.h \
    EmployeeDbReader.h \
    EmployeeManager.h \
    EmployeeTextReader.h \
    FileReader.h \
    sqlite3.h \
    sqlite3ext.h
