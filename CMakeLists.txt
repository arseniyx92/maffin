cmake_minimum_required(VERSION 3.17)
project(maffin)

set(CMAKE_CXX_STANDARD 17)

add_executable(maffin main.cpp lexer.cpp include/lexer.h token.cpp include/token.h parser.cpp include/parser.h imports.cpp include/imports.h)