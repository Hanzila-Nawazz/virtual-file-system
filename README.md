# Mini-File-Management-Simulator
This is a mini clone of the file management system working in the Operating Systems for handling our files , directories etc. It is just a showcase of how file handler works. It does not work with the actual OS files for now. It works with a single directory .dat file.


## Unformatted Documentation

FILE SYSTEM LAB - USER GUIDE

----------------------------------------
1. HOW TO RUN THE PROGRAM
----------------------------------------

Compile the program using:
g++ main.cpp -o fs

Run the program:
fs


----------------------------------------
2. BASIC FEATURES
----------------------------------------

This system allows you to create and manage files and directories inside a simulated file system having one root directory for all.


----------------------------------------
3. CREATE FILE
----------------------------------------

fs.createFile("fileName");

Example:
fs.createFile("a.txt");

This creates a new file in the current directory.


----------------------------------------
4. DELETE FILE OR DIRECTORY
----------------------------------------

fs.deleteFile("name");

Example:
fs.deleteFile("a.txt");

If file exists, it will be deleted.


----------------------------------------
5. CREATE DIRECTORY
----------------------------------------

fs.makeDir("folderName");

Example:
fs.makeDir("docs");

Creates a new folder inside current directory.


----------------------------------------
6. CHANGE DIRECTORY
----------------------------------------

fs.changeDirectory("folderName");

To go back:
fs.changeDirectory("..");


----------------------------------------
7. OPEN FILE
----------------------------------------

auto f = fs.openFile("fileName");

Example:
auto f = fs.openFile("a.txt");


----------------------------------------
8. WRITE TO FILE
----------------------------------------

f->write_to_file("text");

Example:
f->write_to_file("Hello World");


Write at position:
f->write_to_file(2, "Hi");


----------------------------------------
9. READ FILE
----------------------------------------

Full read:
cout << f->read_from_file();

Partial read:
f->read_from_file(start, size);


----------------------------------------
10. MOVE FILE NAME
----------------------------------------

fs.moveFile("oldName", "newName");


----------------------------------------
11. MEMORY MAP
----------------------------------------

fs.showMemoryMap();

Shows structure of all files and directories.


----------------------------------------
12. SAVE SYSTEM
----------------------------------------

fs.saveToDisk();

Stores data in:
sample.dat


----------------------------------------
13. LOAD SYSTEM
----------------------------------------

fs.loadFromDisk();

Loads previously saved data from sample.dat


----------------------------------------
IMPORTANT NOTE
----------------------------------------

All data is stored in a single file:
sample.dat

This file is used for saving and restoring the system state.




## System design doc (unformatted yet again)

FILE SYSTEM LAB - SYSTEM DESIGN DOCUMENT

1. OBJECTIVE

The purpose of this project is to simulate a simple file system that can manage files and directories.

It supports:
- file creation and deletion
- directory creation and navigation
- reading and writing file data
- persistence using a single file


2. MAIN COMPONENTS


2.1 FileSystemEntity (Base Class)

This is the base class for both files and directories.

It stores:
- name of entity
- type (file or directory)


2.2 File Class
Represents a file in the system.

It contains:
- name
- data (content of file)
- size
- start index (for memory simulation)
- creation time
- last modified time

Supports:
- write
- read
- write at position
- truncate
- move within file


2.3 Directory Class
Represents a folder.

It contains:
- name
- map of files and subdirectories
- parent pointer

It forms a tree structure:
root -> folders -> files


2.4 FileSystem Class

This is the main controller of the system.

It manages:
- root directory
- current directory

It performs:
- file creation and deletion
- directory creation and navigation
- file opening
- memory map display
- saving and loading system



3. DIRECTORY STRUCTURE


The system follows a tree structure:

root
 ├── file1
 ├── folder1
 │     ├── file2
 │     └── file3


Navigation:
- ".." moves to parent directory
- folder name moves inside directory



4. FILE STORAGE METHOD


Files are not real OS files (as per the lab requirement since the real OS files would be requiring much complex logic to support all type of files)

Instead:
- file data is stored in memory (strings)
- structure is stored using objects
- relationships are stored using maps and pointers



5. PERSISTENCE SYSTEM


All data is stored in a single file:

sample.dat

It contains:
- directory structure
- file names
- file content
- file sizes

When program restarts, this file is used to rebuild the system.



6. MEMORY MAP


The memory map shows:
- all directories
- all files inside them
- file sizes

It helps visualize system structure.



7. CONCLUSION


This project simulates a basic file system using object oriented programming.

It demonstrates:
- file handling concepts
- directory structure management
- persistence using file storage
- basic operating system behavior

