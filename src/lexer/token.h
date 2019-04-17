#ifndef LC_TOKEN_H_
#define LC_TOKEN_H_

namespace lc::lexer::token {

    enum class Token {
        // Reserved words.
        If,
        Then,
        Else,
        For,
        To,
        Step,
        Do,
        Var,
        Integer,
        Char,
        And,
        Or,
        Not,
        Equals, // Same as assign token?
        LParen, 
        RParen,
        LBraces,
        RBraces,
        LBrackt,
        RBrackt,
        LSS, // Less than.
        GTR, // Greater than.
        LEQ, // Less than or equal.
        GEQ, // Greater than or equal.

        // Other tokens.
        Id,
        Const
    };

}

#endif
