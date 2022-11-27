cmake_minimum_required(VERSION 3.20)
project(NCP)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 main.cpp TuringMachine.cpp TuringMachine.h EarleyParser.cpp EarleyParser.h UniversalTuringMachine.cpp UniversalTuringMachine.h Transition.h)
