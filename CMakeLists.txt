###################################################################################
#	  ____  ____   _    ____      ____      __       _____
#	 |_   ||   _| (_)  |_  _|    |_  _|    [  |     \     /
#	   | |__| |   __     \ \  /\  / / .---. | |.--.  \   /
#	   |  __  |  [  |     \ \/  \/ / / /___\| '/''\ \ \_/
#	  _| |  | |_  | |      \  /\  /  | \___ |  \__/ |  _
#	 |____||____|[___] ()   \/  \/    '.__/ [__\.___' (_)
#                      `
# HiWeb licensed under MIT License
#
# Copyright (C) 2024 setbe <max@lafk.eu>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
###################################################################################

cmake_minimum_required(VERSION 3.7...3.16 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(HiWeb VERSION 24.4)


set(SOURCES

    src/main.cpp
    src/SHA2.cpp
)

add_executable(HiWeb ${SOURCES})
target_include_directories(HiWeb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
    # Compiler: MSVC
    target_compile_options(HiWeb PRIVATE /O2)
elseif(APPLE)
    # Compiler: Clang
    target_compile_options(HiWeb PRIVATE -O3)
else()
    # Compilers: GCC, Clang
    target_compile_options(HiWeb PRIVATE -O3)
endif()

# linking libs
target_link_libraries(HiWeb)