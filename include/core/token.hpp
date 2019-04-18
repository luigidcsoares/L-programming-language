#ifndef CORE_TOKEN_HPP_
#define CORE_TOKEN_HPP_

namespace core::token {

    enum class Token {
        // Reserved words:
        ConstKW,
        VarKW,
        IntegerKW,
        CharKW,
        ForKW,
        IfKW,
        ElseKW,
        AndKW,
        OrKW,
        NotKW,
        ToKW,
        ThenKW,
        ReadlnKW,
        StepKW,
        WriteKW,
        WritelnKW,
        DoKW,

        // Others.
        EQ, // Comparison or assignment.
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
        Percent,
        LBracket, // '['.
        RBracket, // ']'.

        Id,
        Const // String, char (including hexa) or integer.
    };
}

#endif
