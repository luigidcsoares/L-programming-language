#ifndef CORE_LC_HPP_
#define CORE_LC_HPP_

#include "core/token.hpp"

using namespace core::token;

namespace core::lc {

    struct TokenReg {
        Token token;  
        std::string lexeme;
        std::string type;
        int length;
    };

    extern TokenReg token_reg;
}

#endif
