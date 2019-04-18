#ifndef LEXER_LEXER_HPP_
#define LEXER_LEXER_HPP_

#include <fstream>

#include "utils/source.hpp"

using namespace utils::source;

namespace lexer {

    /**
     * Read and return the next valid token or the first error found.
     *
     * @param utils::source::Source source file.
     * @param core::token::TokenReg token register.
     *
     * @return TokenReg.
     */
    void next(Source &source);
}

#endif
