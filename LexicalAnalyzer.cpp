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

#include "LexicalAnalyzer.hpp"
#include <cmath>
#include <istream>
#include <locale>

LexicalAnalyzer::LexicalAnalyzer(std::istream& is)
    : _is(is)
{
}

std::optional<Token> LexicalAnalyzer::get()
{
    if (_is.eof()) {
        return {};
    }

    if (auto t = getWhitespace(); t) {
        return t;
    }

    if (auto t = getNumericConstant(); t) {
        return t;
    }

    if (auto t = getPunctuation(); t) {
        return t;
    }

    throw std::runtime_error{"Unknown token"};
}

std::optional<Token> LexicalAnalyzer::getWhitespace()
{
    auto loc = _is.getloc();

    if (!std::isspace<char>(_is.peek(), loc)) {
        return {};
    }

    Token t{TokenKind::Whitespace};
    do {
        t.lexeme.push_back(_is.get());
    } while (std::isspace<char>(_is.peek(), loc));

    return t;
}

std::optional<Token> LexicalAnalyzer::getNumericConstant()
{
    auto loc = _is.getloc();

    if (!std::isdigit<char>(_is.peek(), loc)) {
        return {};
    }

    Token t{TokenKind::NumericConstant};
    double v = 0;
    do {
        auto c = _is.get();
        t.lexeme.push_back(c);
        v *= 10;
        v += c - '0';
    } while (std::isdigit<char>(_is.peek(), loc));

    if (_is.peek() == '.') {
        t.lexeme.push_back(_is.get());

        double b = 1;
        while (std::isdigit<char>(_is.peek(), loc)) {
            auto c = _is.get();
            t.lexeme.push_back(c);
            b *= 10;
            v += static_cast<double>(c - '0') / b;
        }
    }

    if (std::tolower<char>(_is.peek(), loc) == 'e') {
        t.lexeme.push_back(_is.get());

        double s = 1;
        if (auto c = _is.peek(); c == '+') {
            t.lexeme.push_back(_is.get());
        }
        else if (c == '-') {
            t.lexeme.push_back(_is.get());
            s = -1;
        }

        double e = 0;
        while (std::isdigit<char>(_is.peek(), loc)) {
            auto c = _is.get();
            t.lexeme.push_back(c);
            e *= 10;
            e += c - '0';
        }

        v *= std::pow(10, e);
    }

    t.value = v;
    return t;
}

std::optional<Token> LexicalAnalyzer::getPunctuation()
{
    auto makeToken = [this](auto k) -> Token
    {
        return {k, {1, static_cast<char>(_is.get())}};
    };

    switch (auto c = _is.peek()) {
        case '[': return makeToken(TokenKind::LSquare);
        case ']': return makeToken(TokenKind::RSquare);
        case '(': return makeToken(TokenKind::LParen);
        case ')': return makeToken(TokenKind::RParen);
        case '{': return makeToken(TokenKind::LBrace);
        case '}': return makeToken(TokenKind::RBrace);
        case '+': return makeToken(TokenKind::Plus);
        case '-': return makeToken(TokenKind::Minus);
        case '*': return makeToken(TokenKind::Star);
        case '/': return makeToken(TokenKind::Slash);
        default: return {};
    }
}
