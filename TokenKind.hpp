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

#ifndef hpp_ShuntingYard_TokenKind
#define hpp_ShuntingYard_TokenKind

#include <iosfwd>

enum class TokenKind
{
    Whitespace, // \s
    NumericConstant, // [0-9]+(.[0-9]+)?([eE][\+-]?[0-9]+)?
    LSquare, // [
    RSquare, // ]
    LParen, // (
    RParen, // )
    LBrace, // {
    RBrace, // }
    Plus, // +
    Minus, // -
    Star, // *
    Slash, // /
};

std::ostream& operator<<(std::ostream& os, TokenKind rhs);

#endif // hpp_ShuntingYard_TokenKind
