# Task 4: Sample Input/Output Files

## Summary
Created sample test files demonstrating multi-threaded file system operations.

## Files Created

### Input Files
**input_thread1.txt**:
- Creates file1.txt with content
- Creates folder1 directory
- Creates nested.txt inside folder1
- Reads and displays memory map

**input_thread2.txt**:
- Creates file2.txt with content
- Creates folder2 directory
- Creates data.txt inside folder2
- Renames file2.txt to renamed_file2.txt
- Displays memory map

### Output Files
**output_thread1.txt**:
- Shows confirmation of file creation
- Displays read operations
- Shows hierarchical memory map including nested structures

**output_thread2.txt**:
- Shows folder and file creation confirmations
- Shows file rename operation
- Displays updated memory map

## Coverage
- Tests concurrent file creation across threads
- Tests directory hierarchy management
- Tests file operations (create, read, move)
- Tests memory map output consistency

## Impact
Provides realistic test vectors for validating multi-threaded file system implementation.
