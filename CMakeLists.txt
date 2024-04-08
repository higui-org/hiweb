
# cmake version, c++ standard
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

# project name, version
set(PROJECT_NAME hiweb)
project(${PROJECT_NAME} VERSION 24.4)

# -----------------------------
#          FEATURES
option(PARSING_SYSTEM_ONLY "Build parsing system ONLY" OFF)

if(PARSING_SYSTEM_ONLY)
    add_definitions(-DHIWEB_FEATURES_PARSING_SYSTEM_ONLY)
endif()
# -----------------------------




# -----------------------------
#          SOURCES
set(SOURCES
    src/main.cpp

    src/web.cpp
    src/dom.cpp
    src/parser/base.cpp

    # Markups
    src/parser/html/html.cpp    # html
    src/parser/xhtml/xhtml.cpp  # xhtml
    src/parser/xml/xml.cpp      # xml

    # Styles
    src/parser/css/css.cpp      # css
)
# -----------------------------



# Add executable
add_executable(hiweb ${SOURCES})

# Include directories
target_include_directories(hiweb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)





# -----------------------------
#          LINKING
if(MSVC)
    target_link_libraries(${PROJECT_NAME})
elseif(APPLE)
    # Specific libraries for macOS
    target_link_libraries(${PROJECT_NAME})
else()
    # For Linux and other Unix-like systems
    target_link_libraries(${PROJECT_NAME})
endif()
# -----------------------------