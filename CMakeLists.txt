cmake_minimum_required(VERSION 3.16)
project(cpp_opus)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE src/main.cpp
        src/encoder.cpp
        )

set(HEADER src/encoder.h
        src/AudioFile.h
        )

find_package(Opus REQUIRED)

add_executable(cpp_opus ${SOURCE})

set(INCLUDE_DIRECTORIES
        ${OPUS_INCLUDE_DIRS}
        )

set(DEPENDENCIES
        ${OPUS_LIBRARIES})

target_include_directories(cpp_opus PUBLIC ${INCLUDE_DIRECTORIES})

target_link_libraries(cpp_opus PRIVATE ${DEPENDENCIES})
