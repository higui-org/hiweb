cmake_minimum_required(VERSION 3.0)

# hiweb
set(PROJECT_NAME hiweb)
project(${PROJECT_NAME} VERSION 24.2)

set(CMAKE_CXX_STANDARD 17)

# Sources
set(SOURCES
    src/main.cpp
    src/parser/base.cpp

    # HTML
    src/parser/html/html.cpp

    # XHTML
    src/parser/xhtml/xhtml.cpp

    # XML
    src/parser/xml/xml.cpp

    # CSS
    src/parser/css/css.cpp
)

# -----------------------------
#          INCLUDE
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# -----------------------------

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} "src/parser/xhtml/xhtml.cpp")

# -----------------------------
#           BUILDS
if(MSVC)
    # Use /O2 for optimization and /GL for whole program optimization (only for MSVC).
    # /MD - Use Multi-threaded DLL RTL (only if not in Debug mode).
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /GL /MD")
else()
    # For GCC and Clang, set -O3 for maximum optimization and -DNDEBUG to disable asserts.
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

# Set the build type if it is not specified.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# -----------------------------
#          LINKING
if(MSVC)
    #target_link_libraries(${PROJECT_NAME})
elseif(APPLE)
    # Specific libraries for macOS
    target_link_libraries(${PROJECT_NAME})
else()
    # For Linux and other Unix-like systems
    target_link_libraries(${PROJECT_NAME})
endif()
# -----------------------------
