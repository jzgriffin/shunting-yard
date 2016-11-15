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

#include "Token.hpp"
#include <iomanip>
#include <ostream>

std::ostream& operator<<(std::ostream& os, const Token& rhs)
{
    os << "Token Kind: " << rhs.kind
        << ", Lexeme: " << std::quoted(rhs.lexeme);
    switch (rhs.kind) {
        case TokenKind::NumericConstant:
            os << ", Value: " << std::get<double>(rhs.value);
            break;

        default:
            break;
    }

    return os;
}
