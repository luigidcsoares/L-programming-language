#ifndef LEXER_DFA_HPP
#define LEXER_DFA_HPP

#include <sstream>
#include <fstream>

#include "utils/source.hpp"

using namespace utils::source;

namespace lexer::dfa {
    int state0(char c, std::stringstream &lexeme, Source &source);
    int state1(char c, std::stringstream &lexeme, Source &source);
    int state2(char c, std::stringstream &lexeme, Source &source);
    int state3(char c, std::stringstream &lexeme, Source &source);
    int state4(char c, std::stringstream &lexeme, Source &source);
    int state5(char c, std::stringstream &lexeme, Source &source);
    int state6(char c, std::stringstream &lexeme, Source &source);
    int state7(char c, std::stringstream &lexeme, Source &source);
    int state8(char c, std::stringstream &lexeme, Source &source);
    int state9(char c, std::stringstream &lexeme, Source &source);
    int state10(char c, std::stringstream &lexeme, Source &source);
    int state11(char c, std::stringstream &lexeme, Source &source);
    int state12(char c, std::stringstream &lexeme, Source &source);
    int state13(char c, std::stringstream &lexeme, Source &source);
    int state14(char c, std::stringstream &lexeme, Source &source);
}

#endif
