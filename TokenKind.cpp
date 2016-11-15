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

#include "TokenKind.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& os, TokenKind rhs)
{
    switch (rhs) {
        case TokenKind::Whitespace: return os << "Whitespace";
        case TokenKind::NumericConstant: return os << "NumericConstant";
        case TokenKind::LSquare: return os << "LSquare";
        case TokenKind::RSquare: return os << "RSquare";
        case TokenKind::LParen: return os << "LParen";
        case TokenKind::RParen: return os << "RParen";
        case TokenKind::LBrace: return os << "LBrace";
        case TokenKind::RBrace: return os << "RBrace";
        case TokenKind::Plus: return os << "Plus";
        case TokenKind::Minus: return os << "Minus";
        case TokenKind::Star: return os << "Star";
        case TokenKind::Slash: return os << "Slash";
        case TokenKind::Caret: return os << "Caret";
    }
}
