# Task 3: Command Parser Implementation

## Summary
Implemented comprehensive command parsing to handle all Lab 12 required operations.

## Parser Features
1. **String Utilities**:
   - `trim()` - Removes leading/trailing whitespace
   - `split()` - Tokenizes strings by delimiter

2. **Command Execution Engine**:
   - `executeCommand()` - Main parsing dispatcher
   - Handles 11 different command types with variants

3. **Handled Commands**:
   - File operations: Create, Delete, Open, Close, Move
   - Directory operations: Mkdir, chDir
   - Data operations: Write_to_file, Read_from_file, Truncate_file
   - System: Show_memory_map

## Parsing Strategy
- Case-sensitive command matching
- Flexible argument parsing using comma and space delimiters
- Support for variable argument counts
- Error handling for invalid operations

## Impact
Enables flexible command-line based file system control for each thread independently.
