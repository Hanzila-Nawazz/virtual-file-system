# Threaded Virtual File System - User Guide

## System Overview
The Threaded Virtual File System is a multi-threaded file management system that allows concurrent file operations through multiple threads. Each thread independently processes commands from its input file and generates output in its respective output file.

## Directory Structure

```
virtual-file-system/
├── CMakeLists.txt              # Build configuration
├── README.md                   # Project overview
├── lab.txt                     # Lab requirements
├── sample.dat                  # Serialized file system state
├── input_thread<x>.txt         # Input commands for thread x
├── output_thread<x>.txt        # Output results from thread x
├── include/
│   ├── FileSystem.h           # Main file system interface with mutex
│   ├── File.h                 # File class with read/write operations
│   ├── Directory.h            # Directory class
│   └── FileSystemEntity.h     # Base class for files and directories
└── src/
    ├── main.cpp               # Multi-threaded entry point
    ├── FileSystem.cpp         # Thread-safe implementations with locks
    ├── File.cpp               # File operations
    ├── Directory.cpp          # Directory operations
    └── FileSystemEntity.cpp   # Base entity implementations
```

## Building the System

### Prerequisites
- C++ compiler (C++11 or later)
- CMake 3.10+
- POSIX threads support

### Build Steps
```bash
cd virtual-file-system
mkdir build
cd build
cmake ..
make
```

## Running the System

### Execution
```bash
./vfs <number_of_threads>
```

**Example:**
```bash
./vfs 2
```
This creates 2 threads that will:
- Read commands from `input_thread1.txt` and `input_thread2.txt`
- Execute commands with thread synchronization
- Write output to `output_thread1.txt` and `output_thread2.txt`
- Persist the file system state in `sample.dat`

## Supported Commands

### File Operations
- **Create <filename>** - Create a new file
  ```
  Create myfile.txt
  ```

- **Open <filename> [mode]** - Open a file (default mode: READ)
  ```
  Open myfile.txt READ
  ```

- **Close <filename>** - Close an open file
  ```
  Close myfile.txt
  ```

- **Delete <filename>** - Delete a file or directory
  ```
  Delete myfile.txt
  ```

- **Move <source> <target>** - Rename/move a file
  ```
  Move myfile.txt newname.txt
  ```

### Data Operations
- **Write_to_file <filename>, <text>** - Write text to file
  ```
  Write_to_file myfile.txt, Hello World
  ```

- **Write_to_file <filename>, <text>, <location>, <size>** - Write at specific location
  ```
  Write_to_file myfile.txt, Updated, 0, 7
  ```

- **Read_from_file <filename>, <start>, <size>** - Read from file
  ```
  Read_from_file myfile.txt, 0, 5
  ```

- **Truncate_file <filename>, <maxSize>** - Truncate file to size
  ```
  Truncate_file myfile.txt, 100
  ```

### Directory Operations
- **Mkdir <dirname>** - Create a directory
  ```
  Mkdir myfolder
  ```

- **chDir <dirname>** - Change current directory
  ```
  chDir myfolder
  ```

- **chDir ..** - Go to parent directory
  ```
  chDir ..
  ```

### System Operations
- **Show_memory_map** - Display file system hierarchy
  ```
  Show_memory_map
  ```

## Thread Synchronization

The system uses **mutex locks** for thread safety:

1. **Shared Mutex**: A `std::mutex` object in FileSystem protects all shared state
2. **Lock Guard**: Each file system operation uses `lock_guard<mutex>` for automatic lock management
3. **Operations Protected**:
   - Create/Delete files
   - Read/Write directory contents
   - Directory navigation
   - File open/close

This ensures:
- No data corruption from concurrent access
- Atomic operations on directory structures
- Safe file creation and deletion
- Consistent file system state

## Sample Input File Format

**input_thread1.txt:**
```
Create test.txt
Write_to_file test.txt, Hello Thread
Mkdir data
chDir data
Create dataset.txt
chDir ..
Show_memory_map
```

**Expected output in output_thread1.txt:**
```
test.txt created successfully!
Opened test.txt in READ mode.
dataset.txt created successfully!
[DIR ] root
    [DIR ] data
        [FILE] dataset.txt | size = 0
    [FILE] test.txt | size = 12
```

## Persistence

- **Save**: File system state is saved to `sample.dat` after all threads complete
- **Load**: System loads from `sample.dat` at startup if it exists
- **Format**: Hierarchical text format with file contents embedded

## Notes

- Each thread operates independently on the shared file system
- All concurrent modifications are serialized through the mutex
- Output is written to thread-specific files to avoid I/O conflicts
- File system persists across program runs via sample.dat
