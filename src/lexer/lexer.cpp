#include <iostream>
#include <regex>
#include <string>
#include <sstream>

#include "lexer.hpp"
#include "token.hpp"

namespace lexer {

    void next(std::ifstream &source, int &curr_line) {
        int state = 0;
        int final_state = 15;
        
        std::stringstream lexeme;
        
        // Regex for later tests.
        std::string letter_str = "[a-zA-Z]";
        std::regex letter(letter_str);

        std::string digit_str = "[0-9]";
        std::regex digit(digit_str);

        std::regex digit_not_zero("[1-9]");
        std::regex hexadecimal("[0-9a-fA-F]");

        std::string other_str(",|%|\\+|-|\\*|=|\\[|\\]|\\(|\\)|\\{|\\}|;");
        std::regex other(other_str);

        std::stringstream valid_char_ss(letter_str);
        valid_char_ss << '|' << digit_str << '|' 
            << other_str << "| |&|_|\"|'|\\/|\\^|@|!|\\?|<|>|=";
        std::regex valid_char(valid_char_ss.str());

        // Looping through chars looking for the next token.
        while (state != final_state) {
            // We're using string instead of char to make it work with
            // std::regex_match.
            std::string c;

            if (source.peek() != EOF) {
                c = std::string(1, source.get());

                // Handling the current line number.
                if (c == "\n") curr_line++;

                std::cout << "CHAR: " << c << std::endl;
                // Se C inválido, erro.
            } else { state = final_state; };
           
            switch(state) {
                case 0:
                    // Whitespace or newline.
                    if (c == " " || c == "\n");

                    // Identifier and reserved words.
                    else if (std::regex_match(c, letter)) {
                        lexeme << c;
                        state = 1;
                    } else if (c == "_" || c == ".") {
                        lexeme << c;
                        state = 2;
                    }

                    // Comment or division.
                    else if (c == "/") {
                        lexeme << c;
                        state = 3;
                    }

                    // Greater (than or equal).
                    else if (c == ">") {
                        lexeme << c;
                        state = 6;
                    }

                    // Less (than or equal) or not equal.
                    else if (c == "<") {
                        lexeme << c;
                        state = 7;
                    }

                    // Other tokens.
                    else if (std::regex_match(c, other)) {
                        lexeme << c;
                        // TOK = pesquisarToken
                        state = final_state;
                    }

                    // Const
                    else if (c == "\"") {
                        lexeme << c;
                        state = 14;
                    } else if(c == "'") {
                        lexeme << c;
                        state = 9;
                    } else if(std::regex_match(c, digit_not_zero)) {
                        lexeme << c;
                        state = 8;
                    } else if (c == "0") {
                        lexeme << c;
                        state = 11;
                    } else {
                        std::cout << "Error 0";
                        // exit
                    }

                    break;
                case 1:
                    if(std::regex_match(c, letter) || std::regex_match(c, digit) ||
                       c == "_" || c == ".") {
                        lexeme << c;
                    } else {
                        // voltar 1
                        // TOK = pesquisarToken
                        state = final_state;
                    }
                    
                    break;
                case 2:
                    if(std::regex_match(c, letter) || std::regex_match(c, digit)) {
                        lexeme << c;
                        state = 1;
                    } else {
                        std::cout << "Error 2";
                        // exit
                    }
                    break;
                case 3:
                    if(c == "*") {
                        lexeme.str("");
                        state = 4;
                    } else {
                        // voltar 1
                        // TOK = divisão
                        state = final_state;
                    }
                    break;
                case 4:
                    if(c == "*") {
                        state = 5;
                    }
                    break;
                case 5:
                    if(c == "/") {
                        state = 0;
                    } else if( c != "*") {
                        state = 4;
                    }
                    break;
                case 6:
                    if(c == "=") {
                        lexeme << c;
                    } else {
                        // voltar 1
                    }
                    // TOK = pesquisarToken
                    state = final_state;
                    break;
                case 7:
                    if(c == ">"  || c == "=") {
                        lexeme << c;
                    } else {
                        // voltar 1
                    }
                    // pesquisar token
                    state = final_state;
                    break;
                case 8:
                    if(std::regex_match(c, digit)) {
                        lexeme << c;
                    } else {
                        // voltar 1
                        // TOK = const
                        state = final_state;
                    }
                    break;
                case 9:
                    if(std::regex_match(c, valid_char)) {
                        lexeme << c;
                        state = 10;
                    } else {
                        std::cout << "Error 9";
                        // exit
                    }
                    break;
                case 10:
                    if(c == "'") {
                        lexeme << c;
                        // TOK = const
                        state = final_state;
                    } else {
                        std::cout << "Error 10";
                        // exit
                    }
                    break;
                case 11:
                    if(std::regex_match(c, digit)) {
                        lexeme << c;
                        state = 8;
                    } else if(c == "X" || c == "x") {
                        lexeme << c;
                        state = 12;
                    } else {
                        // voltar 1
                        // TOK = const
                        state = final_state;
                    }
                    break;
                case 12:
                    if(std::regex_match(c, hexadecimal)) {
                        lexeme << c;
                        state = 13;
                    } else {
                        std::cout << "Error 12";
                        // exit
                    }
                    break;
                case 13:
                    if(std::regex_match(c, hexadecimal)) {
                        lexeme << c;
                        // TOK = const
                        state = final_state;
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
    }

}
