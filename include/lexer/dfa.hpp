#ifndef LEXER_DFA_HPP
#define LEXER_DFA_HPP

#include <sstream>
#include <fstream>

namespace lexer::dfa {

    int state0(char c, std::stringstream &lexeme, int curr_line);
    int state1(char c, std::stringstream &lexeme, int curr_line,
            std::ifstream &source);
}

#endif
