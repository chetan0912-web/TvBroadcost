#ifndef FILEREADER_H
#define FILEREADER_H

#include <map>
#include "Languages.h"
#include "Chanels.h"
#include "Programs.h"

class FileReader
{
public:
    FileReader() {}

    ~FileReader() {}

    virtual bool openFile(const std::string&) = 0;
    virtual void closeFile() = 0;
    virtual void createFile() = 0;

    virtual void readData(std::map<int, Languages*>&) = 0;

    virtual void insertLanguage(int, const Languages*) = 0;
    virtual void insertChannel(int, int, const Chanels*) = 0;
    virtual void insertProgram(int, const Programs*) = 0;
    virtual void insertFullTree(const std::map<int, Languages*>&) = 0;

    virtual bool deleteChannel(int) = 0;
    virtual bool deleteProgram(int, int) = 0;
    virtual void deleteAllPrograms() = 0;
    virtual void deleteAll() = 0;
};

#endif
