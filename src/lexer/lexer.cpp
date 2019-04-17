#include <iostream>
#include <regex>
#include <string>
#include <sstream>

#include "../../include/lexer.hpp"
#include "../../include/token.hpp"

namespace lexer {

    void next(std::ifstream &source) {
        int state = 0;
        int final_state = 15;
        
        std::stringstream lexeme;

        std::regex letter("[a-zA-Z]");
        std::regex others(",|%|+|-|*|=|[|]|(|)|{|}|;");

        while (state != final_state) {
            char aux;
            if (source >> aux) {
                // Se C inválido, erro.
            }
           
            // Turn to string for using with regex.
            std::string c(aux, 1);

            switch(state) {
                case 0:
                    // Identifier and reserved words.
                    if (c == " ");
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
                    else if (std::regex_match(c, others)) {
                        lexeme << c;
                        state = final_state;
                    }
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;
                case 10:
                    break;
                case 11:
                    break;
                case 12:
                    break;
                case 13:
                    break;
                case 14:
                    break;
            }
        }
    }

}
