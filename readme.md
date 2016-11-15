Shunting Yard
=============

This is an implementation of the shunting-yard algorithm for parsing
infix notation mathematical expressions, as devised by Edsger Dijkstra.
It is written in C++17 (and thus requires a sufficiently compliant
compiler to build) and divides the process into three main phases:

  1.  Lexical analysis
  2.  Syntax analysis
  3.  Evaluation

During lexical analysis, a stream of characters is scanned into a stream
of lexical tokens and categorized. This phase combines the traditional
scanning and evaluation phases of lexical analysis into one, due to the
simplicity of the grammar. Syntax analysis parses the infix notation
stream and produces a list of nodes in postfix notation according to the
shunting-yard algorithm. In this implementation, the syntax analyzer
invokes the lexical analyzer one token at a time, effectively combining
the lexing and parsing phases. Once this deque of nodes is assembled,
the evaluator passes over it and performs the indicated operations in
a manner similar to a stack machine, producing the result of the
arithmetic calculation.

Presently, the implementation supports the following operations:

  1.  Grouping using parentheses, square brackets, and curly braces
  2.  Addition
  3.  Subtraction
  4.  Multiplication
  5.  Division
