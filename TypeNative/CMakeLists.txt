cmake_minimum_required(VERSION 3.20.0)
project(TypeNative VERSION 24.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories( # TypeNative
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include_directories( # LLVM
    ${CMAKE_SOURCE_DIR}/external/llvm/llvm/include
)

add_executable(TypeNative 
	src/Lexer.cpp
	src/Parser.cpp
	src/Semantic.cpp
	src/CodeGen.cpp
	src/Calc.cpp
	src/rtcalc.c)

set_target_properties(TypeNative PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Check if the system is Windows and set the MSVC linker
if (WIN32)
    set(CMAKE_LINKER "link")
    set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> <FLAGS> <CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -out:<TARGET> <LINK_LIBRARIES>")
endif()

# Check if the specified linker works, if not, print a warning
execute_process(COMMAND ${CMAKE_LINKER} /?
                RESULT_VARIABLE link_result)
if(NOT link_result EQUAL 0)
    message(FATAL_ERROR "MSVC linker 'link' not found or not working properly.")
endif()
