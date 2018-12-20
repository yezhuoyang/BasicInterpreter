cmake_minimum_required(VERSION 3.13)
project(Basic_int)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Basic_int
        Basic.cpp
        evalstate.cpp
        evalstate.h
        exp.cpp
        exp.h
        main.cpp
        parser.cpp
        parser.h
        program.cpp
        program.h
        statement.cpp
        statement.h)


link_directories(${Basic_int_SOURCE_DIR}/StanfordCPPLib)