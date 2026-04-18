#include "../include/FileSystem.h"

int main()
{
    FileSystem fs;

    fs.createFile("a.txt");
    fs.createFile("b.txt");

    auto f = fs.openFile("a.txt");
    if(f != nullptr)
    {
        f->write_to_file("Hello OS Lab");
    }

    fs.makeDir("docs");
    fs.changeDirectory("docs");

    fs.createFile("c.txt");

    fs.changeDirectory("..");

    fs.showMemoryMap();

    fs.saveToDisk();
    fs.loadFromDisk();

    return 0;
}
