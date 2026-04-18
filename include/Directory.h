#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "FileSystemEntity.h"
#include <unordered_map>
#include <memory>
#include <string>

using namespace std;

class Directory : public FileSystemEntity
{
    public:
    unordered_map<string, shared_ptr<FileSystemEntity>> contents;
    shared_ptr<Directory> parent;

    Directory(string name);
};

#endif

