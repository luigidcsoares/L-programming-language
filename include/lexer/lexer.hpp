#ifndef LEXER_LEXER_HPP_
#define LEXER_LEXER_HPP_

#include <fstream>

#include "utils/source.hpp"
#include "core/token.hpp"
#include "core/type.hpp"

using namespace core;
using namespace utils;

namespace lexer {

    /**
     * Read and return the next valid token or the first error found.
     *
     * @param utils::source::Source source file.
     * @param lexer::LexerReg token register.
     *
     * @return LxerReg.
     */
    void next(Source &source);

    struct LexerReg {
        Token token;  
        std::string lexeme;
        Type type;
        int length;
    };
}

#endif
