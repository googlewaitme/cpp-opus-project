cmake_minimum_required(VERSION 3.16)

project(cpp_opus)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE main.cpp
        encoder.cpp
        )
set(HEADER encoder.h
        AudioFile.h
        )

add_executable(cpp_opus ${SOURCE})

target_link_libraries(cpp_opus opus)
