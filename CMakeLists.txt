cmake_minimum_required(VERSION 3.0)

project(ShuntingYard)

add_executable(ShuntingYard
    Evaluator.cpp
    Evaluator.hpp
    LexicalAnalyzer.cpp
    LexicalAnalyzer.hpp
    Node.cpp
    Node.hpp
    NodeKind.cpp
    NodeKind.hpp
    OperatorAssoc.hpp
    OperatorKind.cpp
    OperatorKind.hpp
    OperatorProperties.hpp
    SyntaxAnalyzer.cpp
    SyntaxAnalyzer.hpp
    Token.cpp
    Token.hpp
    TokenKind.cpp
    TokenKind.hpp
    main.cpp
)
