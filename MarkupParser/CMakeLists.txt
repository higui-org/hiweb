cmake_minimum_required(VERSION 3.20)
project(hiMarkup VERSION 0.0.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glm/glm/include)


add_executable(hiMarkup
    src/main.cpp
	src/html.cpp
	src/xml.cpp
)