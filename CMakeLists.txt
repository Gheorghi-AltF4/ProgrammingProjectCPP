cmake_minimum_required(VERSION 3.28)
project(C__PP)

set(CMAKE_CXX_STANDARD 17)

add_executable(C__PP src/main.cpp
        src/accounts.h
        src/fileIO.h
        src/accounts.cpp
        src/fileIO.cpp)
