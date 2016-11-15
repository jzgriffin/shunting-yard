// Copyright (c) Jeremiah Z. Griffin <nokurn@gmail.com>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE NEGLIGENCE OR OTHER TORTIOUS ACTION,
// ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
// SOFTWARE.

#ifndef hpp_ShuntingYard_SyntaxAnalyzer
#define hpp_ShuntingYard_SyntaxAnalyzer

#include "LexicalAnalyzer.hpp"
#include "Node.hpp"
#include "OperatorKind.hpp"
#include "OperatorProperties.hpp"
#include <deque>
#include <map>
#include <stack>

class SyntaxAnalyzer
{
public:
    explicit SyntaxAnalyzer(LexicalAnalyzer& la);

    const std::deque<Node>& nodes() const noexcept { return _nodes; }

    bool next();

private:
    static const std::map<OperatorKind, OperatorProperties> _operatorProps;

    LexicalAnalyzer& _la;
    std::stack<OperatorKind> _operators;
    std::deque<Node> _nodes;

    void parseNumber(const Token& t);
    void parseOperator(const Token& t);
    void parseLeftScope(OperatorKind kind, const Token& t);
    void parseRightScope(OperatorKind kind, const Token& t);
    void parseArithmetic(OperatorKind kind, const Token& t);

    void finalizeNodes();
};

#endif // hpp_ShuntingYard_SyntaxAnalyzer
