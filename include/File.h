#ifndef FILE_H
#define FILE_H

#include "FileSystemEntity.h"
#include <chrono>
#include <string>

using namespace std;

class File : public FileSystemEntity
{
    public:
    string data;
    int size;
    int start;

    chrono::system_clock::time_point date_created;
    chrono::system_clock::time_point last_modified;

    File(string name);

    void write_to_file(string text);

    void write_to_file(int write_at, string text);

    string read_from_file();

    string read_from_file(int start, int len);

    void move_within_file(int from, int len, int to);

    void truncate_file(int maxSize);
};

#endif

