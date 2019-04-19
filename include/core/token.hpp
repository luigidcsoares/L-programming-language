#ifndef CORE_TOKEN_HPP_
#define CORE_TOKEN_HPP_

#include <string>
#include "core/type.hpp"

using namespace core::type;

namespace core::token {

    enum class Token {
        // Reserved words:
        ConstKW, // KW to diff from constants.
        Var,
        Integer,
        Char,
        For,
        If,
        Else,
        And,
        Or,
        Not,
        EQ, // Comparison or assignment.
        To,
        LParen, // '('.
        RParen, // ')'.
        LT, // Less than.
        GT, // Greater than.
        NE, // Not equal.
        GE, // Greater than or equal.
        LE, // Less than or equal.
        Comma,
        Add,
        Sub,
        Mult,
        Div, // Used for division or comments.
        Semicolon,
        LBrace, // '{'.
        RBrace, // '}'.
        Then,
        Readln,
        Step,
        Do,
        Write,
        Writeln,
        Percent,
        LBracket, // '['.
        RBracket, // ']'.

        // Other tokens (defined in runtime).
        Id,
        Const // String, char (including hexa) or integer.
    };

}

#endif
