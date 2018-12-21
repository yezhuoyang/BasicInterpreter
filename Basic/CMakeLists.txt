cmake_minimum_required(VERSION 3.13)
project(Basic_int)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Basic
        Basic.cpp
        evalstate.cpp
        evalstate.h
        exp.cpp
        exp.h
        parser.cpp
        parser.h
        program.cpp
        program.h
        statement.cpp
        statement.h)



target_link_libraries(Basic /Users/yezhuoyang/Desktop/project/libStanfordCPPLib.a)
#link_directories("${Basic_int_SOURCE_DIR}/StanfordCPPLib")
