cmake_minimum_required(VERSION 3.16)
project(NCP)

set(CMAKE_CXX_STANDARD 20)

set(SRC_FILES
        main.cpp
        TuringMachine.cpp
        EarleyParser.cpp
        UniversalTuringMachine.cpp
        Objects.cpp
        Track.cpp)

add_executable(NCP ${SRC_FILES})