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

#ifndef hpp_ShuntingYard_OperatorKind
#define hpp_ShuntingYard_OperatorKind

#include <iosfwd>

enum class OperatorKind
{
    LSquare, // [
    RSquare, // ]
    LParen, // (
    RParen, // )
    LBrace, // {
    RBrace, // }
    Add, // +
    Subtract, // -
    Multiply, // *
    Divide, // /
};

std::ostream& operator<<(std::ostream& os, OperatorKind rhs);

bool isOperatorLeftScope(OperatorKind k);
bool isOperatorRightScope(OperatorKind k);
bool isOperatorArithmetic(OperatorKind k);

OperatorKind operatorMatchingScope(OperatorKind k);

#endif // hpp_ShuntingYard_OperatorKind
