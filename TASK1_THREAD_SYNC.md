# Task 1: Thread Synchronization Implementation

## Summary
Added mutex-based thread synchronization to the FileSystem class for safe concurrent access.

## Changes Made
1. **FileSystem.h**:
   - Added `#include <mutex>`
   - Added `mutex fs_mutex` member variable to FileSystem class

2. **FileSystem.cpp**:
   - Added `lock_guard<mutex> lock(fs_mutex)` guards to all state-modifying methods:
     - `createFile()` - Protects file creation
     - `deleteFile()` - Protects file deletion
     - `makeDir()` - Protects directory creation
     - `changeDirectory()` - Protects current directory changes
     - `openFile()` - Protects file lookup operations
     - `moveFile()` - Protects rename/move operations

## Thread Safety Mechanism
- Uses `std::lock_guard` for RAII-style automatic lock management
- Ensures operations are atomic and no race conditions occur
- Locks automatically released when guard goes out of scope

## Impact
Enables safe multi-threaded access to shared file system state without data corruption.
