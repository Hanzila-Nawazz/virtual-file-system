#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "File.h"
#include "Directory.h"
#include <memory>
#include <fstream>

using namespace std;

class FileSystem
{
    private:
    shared_ptr<Directory> root_directory;
    shared_ptr<Directory> current;

    public:
    FileSystem();

    shared_ptr<File> createFile(string name);

    void deleteFile(string name);

    void makeDir(string name);

    void changeDirectory(string name);

    shared_ptr<File> openFile(string name, string mode = "READ");

    void closeFile(string name);

    void moveFile(string source, string target);

    void showMemoryMap();

    void printDirectoryTree(shared_ptr<Directory> dir, int depth);

    void saveToDisk();

    void saveDirectory(shared_ptr<Directory> dir, ofstream &out);

    void loadFromDisk();
};

#endif

