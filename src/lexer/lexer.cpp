/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#include <iostream>
#include <sstream>

#include "core/global.hpp"
#include "core/token.hpp"
#include "lexer/dfa.hpp"
#include "lexer/lexer.hpp"
#include "utils/regex.hpp"

using namespace core;

namespace lexer {

    /**
     * lexer.hpp implementations 
     */ 

    void LexReg::fill(Token token, std::string lexeme, 
            Type type, int length) {

        this->tag = LexReg::Const;
        this->token = token;
        this->lexeme = lexeme;
        this->type = type;
        this->length = length;
    }
    
    void LexReg::fill(Token token, std::string lexeme, 
            TSymbolElem * p_tab_elem) {

        this->tag = LexReg::Id_Kw;
        this->token = token;
        this->lexeme = lexeme;
        this->p_tab_elem = p_tab_elem;
    }

    void next() {
        int state = 0;
        std::stringstream lexeme; 
        char c;

        // Looping through chars looking for the next token.
        while (state != 15) {
            // If we didn't reach EOF yet, we need to check
            // whether the next character is a valid one or not.
            if (g_source.file.get(c)) {
                // Handling the current line number.
                if (c == '\n') g_source.curr_line++;

                // If it isn't a valid char, throw error and exit program.
                if (!utils::is_valid_char(c)) {
                    std::stringstream err;
                    err << g_source.curr_line << ":caractere invalido.";
                    throw std::runtime_error(err.str());
                }
            } else c = EOF;
           
            switch(state) {
                case 0:
                    state = state0(c, lexeme);
                    break;
                case 1:
                    state = state1(c, lexeme);
                    break;
                case 2:
                    state = state2(c, lexeme);
                    break;
                case 3:
                    state = state3(c, lexeme);
                    break;
                case 4:
                    state = state4(c, lexeme);
                    break;
                case 5:
                    state = state5(c, lexeme);
                    break;
                case 6:
                    state = state6(c, lexeme);
                    break;
                case 7:
                    state = state7(c, lexeme);
                    break;
                case 8:
                    state = state8(c, lexeme);
                    break;
                case 9:
                    state = state9(c, lexeme);
                    break;
                case 10:
                    state = state10(c, lexeme);
                    break;
                case 11:
                    state = state11(c, lexeme);
                    break;
                case 12:
                    state = state12(c, lexeme);
                    break;
                case 13:
                    state = state13(c, lexeme);
                    break;
                case 14:
                    state = state14(c, lexeme);
            }
        }
    }
}
