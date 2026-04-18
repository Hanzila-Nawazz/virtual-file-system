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