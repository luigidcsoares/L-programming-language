#ifndef LEXER_TOKEN_HPP_
#define LEXER_TOKEN_HPP_

namespace lexer::token {

    enum class Token {
        // Reserved words:
        Const,
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
        Write,
        Writeln,
        Percent,
        LBracket, // '['.
        RBracket, // ']'.
        Do,

        // Other tokens:
        Id,
        Constant // String, char (including hexa) or integer.
    };

}

#endif
