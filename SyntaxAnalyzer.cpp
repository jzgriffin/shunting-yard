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

#include "SyntaxAnalyzer.hpp"
#include <stdexcept>

const std::map<OperatorKind, OperatorProperties>
SyntaxAnalyzer::_operatorProps{
    {OperatorKind::LSquare, {}},
    {OperatorKind::RSquare, {}},
    {OperatorKind::LParen, {}},
    {OperatorKind::RParen, {}},
    {OperatorKind::LBrace, {}},
    {OperatorKind::RBrace, {}},
    {OperatorKind::Add, {OperatorAssoc::Left, 1}},
    {OperatorKind::Subtract, {OperatorAssoc::Left, 1}},
    {OperatorKind::Multiply, {OperatorAssoc::Left, 2}},
    {OperatorKind::Divide, {OperatorAssoc::Left, 2}},
};

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer& la)
    : _la(la)
{
}

bool SyntaxAnalyzer::next()
{
    auto t = _la.get();
    if (!t) {
        if (_operators.empty()) {
            return false;
        }

        finalizeNodes();
        return true;
    }

    switch ((*t).kind) {
        case TokenKind::Whitespace:
            return true;

        case TokenKind::NumericConstant:
            parseNumber(*t);
            return true;

        case TokenKind::LSquare:
        case TokenKind::RSquare:
        case TokenKind::LParen:
        case TokenKind::RParen:
        case TokenKind::LBrace:
        case TokenKind::RBrace:
        case TokenKind::Plus:
        case TokenKind::Minus:
        case TokenKind::Star:
        case TokenKind::Slash:
            parseOperator(*t);
            return true;
    }
}

void SyntaxAnalyzer::parseNumber(const Token& t)
{
    _nodes.emplace_back(std::get<double>(t.value));
}

void SyntaxAnalyzer::parseOperator(const Token& t)
{
    OperatorKind kind;
    switch (t.kind) {
        case TokenKind::LSquare: kind = OperatorKind::LSquare; break;
        case TokenKind::RSquare: kind = OperatorKind::RSquare; break;
        case TokenKind::LParen: kind = OperatorKind::LParen; break;
        case TokenKind::RParen: kind = OperatorKind::RParen; break;
        case TokenKind::LBrace: kind = OperatorKind::LBrace; break;
        case TokenKind::RBrace: kind = OperatorKind::RBrace; break;
        case TokenKind::Plus: kind = OperatorKind::Add; break;
        case TokenKind::Minus: kind = OperatorKind::Subtract; break;
        case TokenKind::Star: kind = OperatorKind::Multiply; break;
        case TokenKind::Slash: kind = OperatorKind::Divide; break;
        default:
            throw std::runtime_error{"Token kind is not operator"};
    }

    if (isOperatorLeftScope(kind)) {
        parseLeftScope(kind, t);
    }
    else if (isOperatorRightScope(kind)) {
        parseRightScope(kind, t);
    }
    else if (isOperatorArithmetic(kind)) {
        parseArithmetic(kind, t);
    }
    else {
        throw std::runtime_error{"Unknown operator"};
    }
}

void SyntaxAnalyzer::parseLeftScope(OperatorKind kind, const Token& t)
{
    _operators.emplace(kind);
}

void SyntaxAnalyzer::parseRightScope(OperatorKind kind, const Token& t)
{
    auto matchKind = operatorMatchingScope(kind);
    while (!_operators.empty() && _operators.top() != matchKind) {
        auto k = _operators.top();
        if (isOperatorLeftScope(k)) {
            throw std::runtime_error{"Mismatched parenthesis"};
        }

        _operators.pop();
        _nodes.emplace_back(k);
    }

    if (_operators.empty()) {
        throw std::runtime_error{"Mismatched parenthesis"};
    }

    _operators.pop();
}

void SyntaxAnalyzer::parseArithmetic(OperatorKind kind, const Token& t)
{
    auto&& prop = _operatorProps.at(kind);
    while (!_operators.empty()) {
        auto k = _operators.top();
        auto&& p = _operatorProps.at(k);

        if ((prop.assoc == OperatorAssoc::Left &&
                    prop.prec <= p.prec) ||
                (prop.assoc == OperatorAssoc::Right &&
                 prop.prec < p.prec)) {
            _operators.pop();
            _nodes.emplace_back(k);
        }
        else {
            break;
        }
    }

    _operators.emplace(kind);
}

void SyntaxAnalyzer::finalizeNodes()
{
    while (!_operators.empty()) {
        auto k = _operators.top();
        if (isOperatorLeftScope(k)) {
            throw std::runtime_error{"Mismatched parenthesis"};
        }

        _operators.pop();
        _nodes.emplace_back(k);
    }
}
