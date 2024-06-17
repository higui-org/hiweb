cmake_minimum_required(VERSION 3.20)
project(DOMinator VERSION 0.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glm/glm/include)

add_executable(DOMinator
    src/main.cpp
    src/Tag.cpp

    src/internal/Element.cpp
)
