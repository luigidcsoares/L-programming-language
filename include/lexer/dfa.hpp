#ifndef LEXER_DFA_HPP
#define LEXER_DFA_HPP

#include <sstream>
#include <fstream>

#include "utils/source.hpp"

using namespace utils::source;

namespace lexer::dfa {
    int state0(char c, std::stringstream &lexeme, Source &source);
    int state1(char c, std::stringstream &lexeme, Source &source);
}

#endif
