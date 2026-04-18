#include "../include/FileSystemEntity.h"

FileSystemEntity::FileSystemEntity(string name, bool is_directory)
{
    this->name = name;
    this->is_directory = is_directory;
}

string FileSystemEntity::getName()
{
    return name;
}

bool FileSystemEntity::getIsDirectory()
{
    return is_directory;
}

void FileSystemEntity::setName(string name)
{
    this->name = name;
}
