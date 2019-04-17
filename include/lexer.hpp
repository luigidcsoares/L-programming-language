#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <fstream>

namespace lexer {

    /**
     * Read and return the next valid token or the first error found.
     * @param ifstream source file.
     * @return TokenReg.
     */
    void next(std::ifstream &source);
}

#endif
