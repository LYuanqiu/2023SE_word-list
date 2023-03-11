cmake_minimum_required(VERSION 3.22)
project(2023SE_word_list)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(2023SE_word_list
        src/Algorithm.h
        src/Core.h
        src/word_list.cpp
        src/word_list.h src/MaxWordWithRing.h src/WithRingSolver.h)
