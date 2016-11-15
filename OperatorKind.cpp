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

#include "OperatorKind.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& os, OperatorKind rhs)
{
    switch (rhs) {
        case OperatorKind::LSquare: return os << "LSquare";
        case OperatorKind::RSquare: return os << "RSquare";
        case OperatorKind::LParen: return os << "LParen";
        case OperatorKind::RParen: return os << "RParen";
        case OperatorKind::LBrace: return os << "LBrace";
        case OperatorKind::RBrace: return os << "RBrace";
        case OperatorKind::Add: return os << "Add";
        case OperatorKind::Subtract: return os << "Subtract";
        case OperatorKind::Multiply: return os << "Multiply";
        case OperatorKind::Divide: return os << "Divide";
    }
}

bool isOperatorLeftScope(OperatorKind k)
{
    switch (k) {
        case OperatorKind::LSquare:
        case OperatorKind::LParen:
        case OperatorKind::LBrace:
            return true;

        default:
            return false;
    }
}

bool isOperatorRightScope(OperatorKind k)
{
    switch (k) {
        case OperatorKind::RSquare:
        case OperatorKind::RParen:
        case OperatorKind::RBrace:
            return true;

        default:
            return false;
    }
}

bool isOperatorArithmetic(OperatorKind k)
{
    switch (k) {
        case OperatorKind::Add:
        case OperatorKind::Subtract:
        case OperatorKind::Multiply:
        case OperatorKind::Divide:
            return true;

        default:
            return false;
    }
}

OperatorKind operatorMatchingScope(OperatorKind k)
{
    switch (k) {
        case OperatorKind::LSquare: return OperatorKind::RSquare;
        case OperatorKind::RSquare: return OperatorKind::LSquare;
        case OperatorKind::LParen: return OperatorKind::RParen;
        case OperatorKind::RParen: return OperatorKind::LParen;
        case OperatorKind::LBrace: return OperatorKind::RBrace;
        case OperatorKind::RBrace: return OperatorKind::LBrace;
        default:
            throw std::runtime_error{"Operator is not scope"};
    }
}
