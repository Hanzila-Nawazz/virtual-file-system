#ifndef FILE_SYSTEM_ENTITY_H
#define FILE_SYSTEM_ENTITY_H

#include <string>

using namespace std;

class FileSystemEntity
{
    protected:
    string name;
    bool is_directory;

    public:
    FileSystemEntity(string name, bool is_directory);

    virtual ~FileSystemEntity() = default;

    string getName();

    bool getIsDirectory();

    void setName(string name);
};

#endif

