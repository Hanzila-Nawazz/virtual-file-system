#include<iostream>
#include<string>
#include<chrono>
#include<unordered_map>
#include<memory>
#include<fstream>

using namespace std;


class fileSystemEntity
{
    protected:
    string name;
    bool is_directory;

    public:
    fileSystemEntity(string name, bool is_directory)
    {
        this->name = name;
        this->is_directory = is_directory;
    }

    virtual ~fileSystemEntity() = default;

    string getName()
    {
        return name;
    }

    bool getIsDirectory()
    {
        return is_directory;
    }

    void setName(string name)
    {
        this->name = name;
    }
};

class File : public fileSystemEntity
{
    public:
    string data;
    int size;
    int start;

    chrono::system_clock::time_point date_created;
    chrono::system_clock::time_point last_modified;

    File(string name) : fileSystemEntity(name, false)
    {
        size = 0;
        start = -1;
        data = "";

        date_created = chrono::system_clock::now();
        last_modified = chrono::system_clock::now();
    }

    void write_to_file(string text)
    {
        data += text;
        size = data.size();
        last_modified = chrono::system_clock::now();
    }

    //Overloaded function for the write (if you want to write at a specifc point)
    void write_to_file(int write_at, string text)
    {
        if(write_at > size) return;

        data.replace(write_at, text.size(), text);
        size = data.size();
        last_modified = chrono::system_clock::now();
    }

    string read_from_file()
    {
        return data;
    }

    string read_from_file(int start, int len)
    {
        if(start >= size) return "";
        return data.substr(start, len);
    }

    void move_within_file(int from, int len, int to)
    {
        if(from + len > size || to > size) return;

        string temp = data.substr(from, len);
        data.erase(from, len);
        data.insert(to, temp);

        size = data.size();
    }

    void truncate_file(int maxSize)
    {
        if(maxSize < size)
        {
            data = data.substr(0, maxSize);
            size = data.size();
        }
    }
};


class Directory : public fileSystemEntity
{
    public:
    unordered_map<string, shared_ptr<fileSystemEntity>> contents;
    shared_ptr<Directory> parent;

    Directory(string name) : fileSystemEntity(name, true)
    {
        parent = nullptr;
    }
};


class FileSystem
{
    private:
    shared_ptr<Directory> root_directory;
    shared_ptr<Directory> current;

    public:
    FileSystem()
    {
        root_directory = make_shared<Directory>("root");
        current = root_directory;
    }

    
    shared_ptr<File> createFile(string name)
    {
        shared_ptr<File> newFile = make_shared<File>(name);
        current->contents[name] = newFile;
        cout<<name<<" created successfully!"<<endl;
        return newFile;
    }

    
    void deleteFile(string name)
    {
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

   
    void makeDir(string name)
    {
        shared_ptr<Directory> dir = make_shared<Directory>(name);
        dir->parent = current;
        current->contents[name] = dir;
    }

    
    void changeDirectory(string name)
    {
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

    shared_ptr<File> openFile(string name, string mode = "READ")
    {
        auto it = current->contents.find(name);

        if(it != current->contents.end() && !it->second->getIsDirectory())
        {
            cout << "Opened " << name << " in " << mode << " mode." << endl;
            return dynamic_pointer_cast<File>(it->second);
        }

        cout << "Error: File not found to open." << endl;
        return nullptr;
    }

    void closeFile(string name)
    {
        cout << "File " << name << " closed." << endl;
    }

    void moveFile(string source, string target)
    {
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

    void showMemoryMap()
    {
        cout << endl<<"FULL MEMORY MAP" << endl;
        printDirectoryTree(root_directory, 0);
        cout<<endl;
    }

    void printDirectoryTree(shared_ptr<Directory> dir, int depth)
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

    // Persistent
    void saveToDisk()
    {
        ofstream out("sample.dat");

        saveDirectory(root_directory, out);

        out.close();
    }

   
    void saveDirectory(shared_ptr<Directory> dir, ofstream &out)
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

    // Loading the svaed one from the disk after program restarts 
    void loadFromDisk()
    {
        ifstream in("sample.dat");
        if(!in) return;
        
        string line;

        // Reset to empty state before loading
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
        
        // Restore current to root after load is done
        current = root_directory; 
        in.close();
        
        cout << "\nLOAD SUCCESSFUL!\n" << endl;
    }
};


int main()
{
    FileSystem fs;

    // Example 
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