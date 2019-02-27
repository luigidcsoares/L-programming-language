#ifndef LC_TOKEN_H_
#define LC_TOKEN_H_

namespace lc::core::token {

    enum class Token {
        // Reserved words.
        If,
        Then,
        Else,
        For,

        // Other tokens.
        Id,
        Const
    };

}

#endif

