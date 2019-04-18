#include <iostream>

#include "lexer/dfa.hpp"
#include "utils/regex.hpp"

namespace lexer::dfa {

    int state0(char c, std::stringstream &lexeme, int curr_line) {
        int next_state = 0;

        // Whitespace or newline (skip).
        if (utils::regex::is_whitespace(c));

        // Identifier and reserved words.
        else if (utils::regex::is_letter(c)) {
            lexeme << c;
            next_state = 1;
        } else if (c == '_' || c == '.') {
            lexeme << c;
            next_state = 2;
        }

        // Comment or division.
        else if (c == '/') {
            lexeme << c;
            next_state = 3;
        }

        // Greater (than or equal).
        else if (c == '>') {
            lexeme << c;
            next_state = 6;
        }

        // Less (than or equal) or not equal.
        else if (c == '<') {
            lexeme << c;
            next_state = 7;
        }

        // Unit symbols.
        else if (utils::regex::is_unit_symbol(c)) {
            lexeme << c;
            // TODO: TOK = pesquisarToken
            next_state = 15;
        }

        // Const.
        else if (c == '"') { // String.
            lexeme << c;
            next_state = 14;
        } else if (c == '\'') { // Char (alphanum).
            lexeme << c;
            next_state = 9;
        } else if (utils::regex::is_digit_not_zero(c)) { // Digit.
            lexeme << c;
            next_state = 8;
        } else if (c == '0') { // Digit or hexa.
            lexeme << c;
            next_state = 11;
        }
        
        // Lexeme unidentified.
        else { 
            std::stringstream err;
            err << curr_line << ": lexema nao identificado ["
                << lexeme.str() << "].";
            throw std::runtime_error(err.str());
        }

        return next_state;
    }

    int state1(char c, std::stringstream &lexeme, int curr_line, 
            std::ifstream &source) {
       
        int next_state = 1;

        if (utils::regex::is_letter(c) ||
                utils::regex::is_digit(c) ||
                c == '_' || 
                c == '.') {

            lexeme << c;
        } else {
            // TODO: TOK = pesquisarToken
            next_state = 15;

            // Put character back to be read again.
            source.putback(c);
        }
       
        return next_state;
    }
}
