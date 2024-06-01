# src/CMakeLists.txt

add_executable(calc
    Calc.cpp
    CodeGen.cpp
    Lexer.cpp
    Parser.cpp
    Semantic.cpp
    rtcalc.c
)

execute_process(COMMAND llvm-config --libs all OUTPUT_VARIABLE LLVM_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND llvm-config --cxxflags OUTPUT_VARIABLE LLVM_CXXFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

target_compile_options(calc PRIVATE ${LLVM_CXXFLAGS})
target_link_libraries(calc ${LLVM_LIBS} -lrt -ldl -lm -lz -lzstd)