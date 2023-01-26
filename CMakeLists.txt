cmake_minimum_required(VERSION 3.16)
project(NCP)

set(CMAKE_CXX_STANDARD 20)

set(SRC_FILES
        src/main.cpp
        src/TuringMachine.cpp
        src/EarleyParser.cpp
        src/UniversalTuringMachine.cpp
        src/Objects.cpp
        src/Track.cpp src/Computing.cpp src/Computing.h)

add_executable(NCP ${SRC_FILES})