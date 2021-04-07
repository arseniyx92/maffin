cmake_minimum_required(VERSION 3.17)
project(maffin)

set(CMAKE_CXX_STANDARD 17)

add_executable(maffin main.cpp lexer.cpp include/lexer.h token.cpp include/token.h parser/parser.cpp include/parser.h imports.cpp include/imports.h parser/parser_vital_functions.cpp structs/list/list.cpp structs/list/list.h structs/stack/stack.cpp structs/stack/stack.h)