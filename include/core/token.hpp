#ifndef CORE_TOKEN_HPP_
#define CORE_TOKEN_HPP_

#include <string>

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
        Plus,
        Minus,
        Times,
        Slash, // Used for division or comments.
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


    struct TokenReg {
        Token token;  
        std::string lexeme;
        std::string type;
        int length;
    };
}

#endif
