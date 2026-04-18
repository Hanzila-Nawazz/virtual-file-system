#include "../include/File.h"

File::File(string name) : FileSystemEntity(name, false)
{
    size = 0;
    start = -1;
    data = "";

    date_created = chrono::system_clock::now();
    last_modified = chrono::system_clock::now();
}

void File::write_to_file(string text)
{
    data += text;
    size = data.size();
    last_modified = chrono::system_clock::now();
}

void File::write_to_file(int write_at, string text)
{
    if(write_at > size) return;

    data.replace(write_at, text.size(), text);
    size = data.size();
    last_modified = chrono::system_clock::now();
}

string File::read_from_file()
{
    return data;
}

string File::read_from_file(int start, int len)
{
    if(start >= size) return "";
    return data.substr(start, len);
}

void File::move_within_file(int from, int len, int to)
{
    if(from + len > size || to > size) return;

    string temp = data.substr(from, len);
    data.erase(from, len);
    data.insert(to, temp);

    size = data.size();
}

void File::truncate_file(int maxSize)
{
    if(maxSize < size)
    {
        data = data.substr(0, maxSize);
        size = data.size();
    }
}
