cmake_minimum_required(VERSION 3.20)
project(grammatical_analysis)

set(CMAKE_CXX_STANDARD 20)

add_executable(grammatical_analysis main.cpp Parser/Parser.h Token.h TokenStream/TokenStream.h TokenStream/TokenStream.cpp Parser/Parser.cpp Lexer/Lexer.cpp Lexer/Lexer.h Error/Error.cpp Error/Error.h)
