#include "../include/FileSystem.h"
#include <iostream>

FileSystem::FileSystem()
{
    root_directory = make_shared<Directory>("root");
    current = root_directory;
}

shared_ptr<File> FileSystem::createFile(string name)
{
    lock_guard<mutex> lock(fs_mutex);
    shared_ptr<File> newFile = make_shared<File>(name);
    current->contents[name] = newFile;
    cout<<name<<" created successfully!"<<endl;
    return newFile;
}

void FileSystem::deleteFile(string name)
{
    lock_guard<mutex> lock(fs_mutex);
    auto it = current->contents.find(name);

    if(it != current->contents.end())
    {
        current->contents.erase(it);
        cout << "File/Directory deleted successfully" <<endl;
    }
    else
    {
        cout << "Error: File/Directory not found" <<endl;
    }
}

void FileSystem::makeDir(string name)
{
    lock_guard<mutex> lock(fs_mutex);
    shared_ptr<Directory> dir = make_shared<Directory>(name);
    dir->parent = current;
    current->contents[name] = dir;
}

void FileSystem::changeDirectory(string name)
{
    lock_guard<mutex> lock(fs_mutex);
    if(name == "..")
    {
        if(current->parent != nullptr)
            current = current->parent;
        return;
    }

    auto it = current->contents.find(name);

    if(it != current->contents.end() && it->second->getIsDirectory())
    {
        current = dynamic_pointer_cast<Directory>(it->second);
    }
}

shared_ptr<File> FileSystem::openFile(string name, string mode)
{
    lock_guard<mutex> lock(fs_mutex);
    auto it = current->contents.find(name);

    if(it != current->contents.end() && !it->second->getIsDirectory())
    {
        cout << "Opened " << name << " in " << mode << " mode." << endl;
        return dynamic_pointer_cast<File>(it->second);
    }

    cout << "Error: File not found to open." << endl;
    return nullptr;
}

void FileSystem::closeFile(string name)
{
    cout << "File " << name << " closed." << endl;
}

void FileSystem::moveFile(string source, string target)
{
    lock_guard<mutex> lock(fs_mutex);
    auto it = current->contents.find(source);

    if(it != current->contents.end())
    {
        it->second->setName(target);
        current->contents[target] = it->second;
        current->contents.erase(it);
        cout << "Moved " << source << " to " << target << " successfully!" << endl;
    }
    else
    {
        cout << "Error: Source not found." << endl;
    }
}

void FileSystem::showMemoryMap()
{
    cout << endl<<"FULL MEMORY MAP" << endl;
    printDirectoryTree(root_directory, 0);
    cout<<endl;
}

void FileSystem::printDirectoryTree(shared_ptr<Directory> dir, int depth)
{
    string indent = string(depth * 4, ' ');
    cout << indent << "[DIR ] " << dir->getName() << endl;

    for(auto &p : dir->contents)
    {
        if(p.second->getIsDirectory())
        {
            printDirectoryTree(dynamic_pointer_cast<Directory>(p.second), depth + 1);
        }
        else
        {
            auto f = dynamic_pointer_cast<File>(p.second);
            cout << indent << "    [FILE] " << f->getName() << " | size = " << f->size << endl;
        }
    }
}

void FileSystem::saveToDisk()
{
    ofstream out("sample.dat");

    saveDirectory(root_directory, out);

    out.close();
}

void FileSystem::saveDirectory(shared_ptr<Directory> dir, ofstream &out)
{
    out << "DIR:" << dir->getName() << endl;

    for(auto &p : dir->contents)
    {
        if(p.second->getIsDirectory())
        {
            out << "DIR_ITEM:" << p.first <<endl;
            saveDirectory(dynamic_pointer_cast<Directory>(p.second), out);
        }
        else
        {
            auto f = dynamic_pointer_cast<File>(p.second);

            out << "FILE:" << f->getName()
                << "|" << f->read_from_file()
                << "|" << f->size << "\n";
        }
    }
    out << "END_DIR\n";
}

void FileSystem::loadFromDisk()
{
    ifstream in("sample.dat");
    if(!in) return;
    
    string line;

    root_directory = make_shared<Directory>("root");
    current = root_directory;

    cout << endl<<"LOADING SAMPLE.DAT"<<endl;

    while(getline(in, line))
    {
        if(line.find("DIR:") == 0)
        {
            string dname = line.substr(4);
            if(dname != "root") 
            {
                makeDir(dname);
                changeDirectory(dname);
            }
        }
        else if(line == "END_DIR")
        {
            if(current->parent != nullptr) 
            {
                current = current->parent;
            }
        }
        else if(line.find("FILE:") == 0)
        {
            string rest = line.substr(5);
            size_t d1 = rest.find('|');
            size_t d2 = rest.find('|', d1 + 1);
            
            if(d1 != string::npos && d2 != string::npos) 
            {
                string fname = rest.substr(0, d1);
                string fdata = rest.substr(d1 + 1, d2 - d1 - 1);
                
                auto newFile = createFile(fname);
                if(!fdata.empty()) 
                {
                     newFile->write_to_file(fdata);
                }
            }
        }
    }
    
    current = root_directory; 
    in.close();
    
    cout << "\nLOAD SUCCESSFUL!\n" << endl;
}
