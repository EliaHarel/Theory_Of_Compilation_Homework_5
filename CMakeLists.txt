cmake_minimum_required(VERSION 3.15)
project(Homework_5)
# Itamar Holder

set(CMAKE_CXX_STANDARD 14) # C++ 14 is needed for the following commands!
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
# -O0 flag to disable compiler optimizations to give more precise breakpoints stops.

FIND_PACKAGE(BISON)
FIND_PACKAGE(FLEX)

BISON_TARGET(
        Parser # Just a name
        parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp # path to save output
)

FLEX_TARGET(
        Lexer
        scanner.lex ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
)

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})


ADD_EXECUTABLE(Homework_5
        ${BISON_Parser_OUTPUTS} ${FLEX_Lexer_OUTPUTS}
        attributes.hpp enums.h funcSymbolsTable.cpp function.h globalFuncs.cpp hw3_output.cpp scope.h
        statement.h var.cpp varsSymbolsTable.h expression.h expression.cpp bp.cpp)
