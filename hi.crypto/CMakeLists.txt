cmake_minimum_required(VERSION 3.20)

enable_language(C)

set(CMAKE_REQUIRED_FLAGS "-DMAIN_FUNCTION")
set(CMAKE_REQUIRED_DEFINITIONS "-D__STDC_LIMIT_MACROS")

project(hiCrypto VERSION 0.0.0 LANGUAGES CXX ASM_NASM)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
if(NOT SRC_FILES)
    message(FATAL_ERROR "No source files found in ${CMAKE_CURRENT_SOURCE_DIR}/src/")
else()
    message(STATUS "Source files: ${SRC_FILES}")
endif()

# Add assembly files and set NASM object format based on the operating system
if(WIN32)
    file(GLOB ASM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/asm/windows/*.asm)
    set(CMAKE_ASM_NASM_OBJECT_FORMAT win64)
elseif(UNIX)
    #file(GLOB ASM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/asm/linux/*.asm)
    #set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
endif()

if(NOT ASM_FILES)
    #message(FATAL_ERROR "No assembly files found in ${CMAKE_CURRENT_SOURCE_DIR}/asm/")
else()
    message(STATUS "Assembly files: ${ASM_FILES}")
endif()

find_package(OpenSSL REQUIRED)

# Create the main executable
add_executable(hiCrypto ${SRC_FILES} ${ASM_FILES})

# Set properties for NASM source files
#set_source_files_properties(${ASM_FILES} PROPERTIES LANGUAGE ASM_NASM)

# Option to build tests
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
    if(NOT TEST_FILES)
        message(FATAL_ERROR "No test files found in ${CMAKE_CURRENT_SOURCE_DIR}/tests/")
    else()
        message(STATUS "Test files: ${TEST_FILES}")
    endif()
    add_executable(TestCrypto ${TEST_FILES} ${ASM_FILES})
    target_include_directories(TestCrypto PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_test(NAME TestCrypto COMMAND TestCrypto)
endif()

# Link libraries for Windows
if(WIN32)
    target_link_libraries(hiCrypto ws2_32)
endif()

target_link_libraries(hiCrypto OpenSSL::SSL OpenSSL::Crypto)