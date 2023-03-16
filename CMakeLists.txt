cmake_minimum_required(VERSION 3.22)
project(2023SE_word_list)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
target_link_directories(2023SE_word_list ./bin)
target_link_libraries(2023SE_word_list core_changed.dll)
add_executable(2023SE_word_list
        src/Algorithm.h
        src/Core.h
        src/word_list.cpp
        src/word_list.h src/MaxWordWithRing.h src/WithRingSolver.h src/ExceptionHandler.h)
