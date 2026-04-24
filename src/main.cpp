#include "../include/FileSystem.h"
#include <thread>
#include <sstream>
#include <iostream>
#include <vector>

FileSystem globalFS;

string trim(const string& str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if(first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

vector<string> split(const string& str, char delimiter)
{
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while(getline(ss, token, delimiter))
    {
        tokens.push_back(trim(token));
    }
    return tokens;
}

void executeCommand(const string& command, ofstream& outFile)
{
    string cmd = trim(command);
    if(cmd.empty()) return;

    vector<string> parts = split(cmd, ' ');
    string operation = parts[0];

    if(operation == "Create" && parts.size() >= 2)
    {
        globalFS.createFile(parts[1]);
    }
    else if(operation == "Delete" && parts.size() >= 2)
    {
        globalFS.deleteFile(parts[1]);
    }
    else if(operation == "Mkdir" && parts.size() >= 2)
    {
        globalFS.makeDir(parts[1]);
    }
    else if(operation == "chDir" && parts.size() >= 2)
    {
        globalFS.changeDirectory(parts[1]);
    }
    else if(operation == "Move" && parts.size() >= 3)
    {
        globalFS.moveFile(parts[1], parts[2]);
    }
    else if(operation == "Open" && parts.size() >= 2)
    {
        string mode = (parts.size() >= 3) ? parts[2] : "READ";
        globalFS.openFile(parts[1], mode);
    }
    else if(operation == "Close" && parts.size() >= 2)
    {
        globalFS.closeFile(parts[1]);
    }
    else if(operation == "Write_to_file")
    {
        size_t pos = cmd.find("Write_to_file");
        string rest = cmd.substr(pos + 13);
        size_t comma1 = rest.find(',');
        
        if(comma1 != string::npos)
        {
            string filename = trim(rest.substr(0, comma1));
            string remaining = rest.substr(comma1 + 1);
            size_t comma2 = remaining.find(',');
            
            if(comma2 != string::npos)
            {
                string text = trim(remaining.substr(0, comma2));
                vector<string> locAndSize = split(remaining.substr(comma2 + 1), ',');
                if(locAndSize.size() >= 2)
                {
                    int loc = stoi(trim(locAndSize[0]));
                    auto f = globalFS.openFile(filename);
                    if(f) f->write_to_file(loc, text);
                }
            }
            else
            {
                string text = trim(remaining);
                auto f = globalFS.openFile(filename);
                if(f) f->write_to_file(text);
            }
        }
    }
    else if(operation == "Read_from_file")
    {
        size_t pos = cmd.find("Read_from_file");
        string rest = cmd.substr(pos + 14);
        vector<string> parts = split(rest, ',');
        
        if(parts.size() >= 3)
        {
            string filename = trim(parts[0]);
            int start = stoi(trim(parts[1]));
            int size = stoi(trim(parts[2]));
            auto f = globalFS.openFile(filename);
            if(f) outFile << f->read_from_file(start, size) << endl;
        }
    }
    else if(operation.find("Truncate_file") != string::npos)
    {
        size_t pos = cmd.find("Truncate_file");
        size_t space = cmd.find(' ', pos);
        string remaining = cmd.substr(space + 1);
        vector<string> parts = split(remaining, ',');
        
        if(parts.size() >= 2)
        {
            string filename = trim(parts[0]);
            int maxSize = stoi(trim(parts[1]));
            auto f = globalFS.openFile(filename);
            if(f) f->truncate_file(maxSize);
        }
    }
    else if(operation == "Show_memory_map")
    {
        globalFS.showMemoryMap();
    }
}

void threadFunction(int threadId)
{
    string inputFile = "input_thread" + to_string(threadId) + ".txt";
    string outputFile = "output_thread" + to_string(threadId) + ".txt";

    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if(!inFile || !outFile) return;

    string command;
    while(getline(inFile, command))
    {
        executeCommand(command, outFile);
    }

    inFile.close();
    outFile.close();
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <number_of_threads>" << endl;
        return 1;
    }

    int numThreads = stoi(argv[1]);
    vector<thread> threads;

    globalFS.loadFromDisk();

    for(int i = 1; i <= numThreads; i++)
    {
        threads.push_back(thread(threadFunction, i));
    }

    for(auto& t : threads)
    {
        t.join();
    }

    globalFS.saveToDisk();

    return 0;
}
