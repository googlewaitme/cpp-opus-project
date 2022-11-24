cmake_minimum_required(VERSION 3.16)
project(cpp_opus)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/external/cmake)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
        src/*.h
        src/*.cpp
        )

find_package(Opus REQUIRED)

add_executable(cpp_opus ${SOURCES})

set(INCLUDE_DIRECTORIES
        ${OPUS_INCLUDE_DIRS}
        ${OPUS_INCLUDE_DIRS}/opus
        external/Audiofile
        /usr/include/
        )

set(DEPENDENCIES
        ${OPUS_LIBRARIES})

target_include_directories(cpp_opus PUBLIC ${INCLUDE_DIRECTORIES})
target_link_libraries(cpp_opus PUBLIC ${DEPENDENCIES})
