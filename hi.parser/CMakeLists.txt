cmake_minimum_required(VERSION 3.20)
project(HiParser VERSION 0.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# HiParser include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# GLM include
 #include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glm)
# GLFW include
 #include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glfw/include)
 #add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../external/glfw ${CMAKE_BINARY_DIR}/external/glfw)

 #find_package(Vulkan REQUIRED)

add_executable(HiParser src/main.cpp src/html5.cpp)

 #target_include_directories(HiParser PRIVATE ${Vulkan_INCLUDE_DIRS})
 #target_link_libraries(HiParser PRIVATE glfw ${Vulkan_LIBRARIES})