# setup
cmake_minimum_required(VERSION 3.10)
project(VirtualFileSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# point source code
add_executable(vfs
    src/main.cpp
    src/FileSystemEntity.cpp
    src/File.cpp
    src/Directory.cpp
    src/FileSystem.cpp
)
target_include_directories(vfs PUBLIC include)

