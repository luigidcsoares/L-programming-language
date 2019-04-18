#ifndef LEXER_LEXER_HPP_
#define LEXER_LEXER_HPP_

#include <fstream>

namespace lexer {

    /**
     * Read and return the next valid token or the first error found.
     *
     * @param ifstream& source Source file.
     * @param int& curr_line Current line number.
     *
     * @return TokenReg.
     */
    void next(std::ifstream &source, int &curr_line);
}

#endif
