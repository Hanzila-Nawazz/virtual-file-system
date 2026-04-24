# Task 2: Multi-Threading Main Program

## Summary
Rewrote main.cpp to support k threads processing commands independently with output redirection.

## Changes Made
1. **Global FileSystem Instance**:
   - Created `FileSystem globalFS` for shared access across threads

2. **Command Parsing Functions**:
   - `trim()` - Removes whitespace from strings
   - `split()` - Tokenizes commands by delimiter
   - `executeCommand()` - Parses and executes individual commands

3. **Thread Function**:
   - `threadFunction()` - Each thread:
     - Reads from `input_thread<x>.txt`
     - Executes commands line-by-line
     - Writes output to `output_thread<x>.txt`

4. **Main Function**:
   - Accepts command-line argument for thread count
   - Loads file system from `sample.dat`
   - Creates and joins k threads
   - Saves file system to `sample.dat` after completion

## Supported Commands Implemented
- Create, Delete, Mkdir, chDir
- Move, Open, Close
- Write_to_file (with two variants)
- Read_from_file, Truncate_file
- Show_memory_map

## Impact
Enables concurrent file system operations with proper thread management and I/O isolation.
