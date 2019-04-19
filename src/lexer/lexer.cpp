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
                c = tolower(c); // Since L is case insensitive.

                // Handling the current line number.
                if (c == '\n') source.curr_line++;

                // If it isn't a valid char, throw error and exit program.
                if (!utils::regex::is_valid_char(c)) {
                    std::stringstream err;
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
                    state = dfa::state8(c, lexeme, source);
                    break;
                case 9:
                    state = dfa::state9(c, lexeme, source);
                    break;
                case 10:
                    state = dfa::state10(c, lexeme, source);
                    break;
                case 11:
                    state = dfa::state11(c, lexeme, source);
                    break;
                case 12:
                    state = dfa::state12(c, lexeme, source);
                    break;
                case 13:
                    state = dfa::state13(c, lexeme, source);
                    break;
                case 14:
                    state = dfa::state14(c, lexeme, source);
            }
        }

        std::cout << lexeme.str() << std::endl;
    }
}
