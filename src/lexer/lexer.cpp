#include <iostream>
#include <sstream>

#include "core/token.hpp"
#include "lexer/dfa.hpp"
#include "lexer/lexer.hpp"
#include "utils/regex.hpp"

using namespace lexer;

namespace lexer {

    void next(Source &source) {
        int state = 0;
        std::stringstream lexeme; 
        
        // Looping through chars looking for the next token.
        while (state != 15) {
            char c;

            // If we didn't reach EOF yet, we need to check
            // whether the next character is a valid one or not.
            if (source.file.peek() != EOF) {
                c = source.file.get();
                c = toupper(c); // Since L is case insensitive.

                // Handling the current line number.
                if (c == '\n') source.curr_line++;

                // If it isn't a valid char, throw error and exit program.
                if (!utils::regex::is_valid_char(c)) {
                    std::stringstream err;
                std::cout << c << std::endl;
                    err << source.curr_line << ": caractere invalido.";
                    throw std::runtime_error(err.str());
                }
            } else c = EOF;
           
            switch(state) {
                case 0:
                    state = dfa::state0(c, lexeme, source);
                    break;
                case 1:
                    state = dfa::state1(c, lexeme, source);
                    break;
                case 2:
                    state = dfa::state2(c, lexeme, source);
                    break;
                case 3:
                    state = dfa::state3(c, lexeme, source);
                    break;
                case 4:
                    state = dfa::state4(c, lexeme, source);
                    break;
                case 5:
                    state = dfa::state5(c, lexeme, source);
                    break;
                case 6:
                    state = dfa::state6(c, lexeme, source);
                    break;
                case 7:
                    state = dfa::state7(c, lexeme, source);
                    break;
                case 8:
                    if (utils::regex::is_digit(c)) {
                        lexeme << c;
                    } else {
                        // voltar 1
                        // TOK = const
                        state = 15;
                    }
                    break;
                case 9:
                    if (utils::regex::is_valid_char(c)) {
                        lexeme << c;
                        state = 10;
                    } else {
                        std::cout << "Error 9";
                        // exit
                    }
                    break;
                case 10:
                    if (c == '\'') {
                        lexeme << c;
                        // TOK = const
                        state = 15;
                    } else {
                        std::cout << "Error 10";
                        // exit
                    }
                    break;
                case 11:
                    if (utils::regex::is_digit(c)) {
                        lexeme << c;
                        state = 8;
                    } else if (c == 'X' || c == 'x') {
                        lexeme << c;
                        state = 12;
                    } else {
                        // voltar 1
                        // TOK = const
                        state = 15;
                    }
                    break;
                case 12:
                    if (utils::regex::is_hexa(c)) {
                        lexeme << c;
                        state = 13;
                    } else {
                        std::cout << "Error 12";
                        // exit
                    }
                    break;
                case 13:
                    if (utils::regex::is_hexa(c)) {
                        lexeme << c;
                        // TOK = const
                        state = 15;
                    } else {
                        std::cout << "Error 13";
                        // exit
                    }
                    break;
                case 14:
                    break;
                default:
                    break;
            }
        }

        std::cout << lexeme.str() << std::endl;
    }
}
