#include "../include/Directory.h"

Directory::Directory(string name) : FileSystemEntity(name, true)
{
    parent = nullptr;
}
