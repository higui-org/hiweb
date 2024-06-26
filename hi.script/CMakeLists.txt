cmake_minimum_required(VERSION 3.20)
project(calc VERSION 0.0.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/llvm/llvm/include)

set(NO_RTTI "-fno-rtti")
add_definitions(${NO_RTTI})

# Find LLVM
find_package(LLVM REQUIRED CONFIG)
message("Found LLVM ${LLVM_PACKAGE_VERSION}, build type ${LLVM_BUILD_TYPE}")
list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})

# Add LLVM definitions and include directories
# separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
# add_definitions(${LLVM_DEFINITIONS_LIST})

# include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})

# Map LLVM components to libraries
#llvm_map_components_to_libnames(llvm_libs Core)

# add executable and source files
add_subdirectory("src")