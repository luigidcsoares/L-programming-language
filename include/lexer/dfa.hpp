/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#ifndef LEXER_DFA_HPP
#define LEXER_DFA_HPP

#include <sstream>
#include <fstream>

#include "utils/source.hpp"

using namespace utils;

namespace lexer {
    /**
     * Declarate all states of the DFA that represents our lexer.
     * @param: char, c -> current char
     * @param: stringstream, lexeme -> lexeme
     */ 
    int state0(char c, std::stringstream &lexeme);
    int state1(char c, std::stringstream &lexeme);
    int state2(char c, std::stringstream &lexeme);
    int state3(char c, std::stringstream &lexeme);
    int state4(char c, std::stringstream &lexeme);
    int state5(char c, std::stringstream &lexeme);
    int state6(char c, std::stringstream &lexeme);
    int state7(char c, std::stringstream &lexeme);
    int state8(char c, std::stringstream &lexeme);
    int state9(char c, std::stringstream &lexeme);
    int state10(char c, std::stringstream &lexeme);
    int state11(char c, std::stringstream &lexeme);
    int state12(char c, std::stringstream &lexeme);
    int state13(char c, std::stringstream &lexeme);
    int state14(char c, std::stringstream &lexeme);
}

#endif
