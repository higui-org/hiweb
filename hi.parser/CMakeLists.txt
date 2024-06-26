cmake_minimum_required(VERSION 3.20)
project(HiParser VERSION 0.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glm)

add_executable(HiParser
    src/main.cpp
    src/html5.cpp
)
