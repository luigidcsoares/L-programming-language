#include <iostream>
#include <sstream>

#include "lexer/dfa.hpp"
#include "utils/regex.hpp"

namespace lexer::dfa {
    int state0(char c, std::stringstream &lexeme, int curr_line) {
        int next_state = 0;

        // Skipping whitespace.
        if (utils::regex::is_whitespace(c)) return next_state;

        // Concatenate char to the lexeme.
        lexeme << c;

        // Identifier and reserved words.
        if (utils::regex::is_letter(c)) next_state = 1;
        else if (c == '_' || c == '.') next_state = 2;

        // Comment or division.
        else if (c == '/') next_state = 3;

        // Greater (than or equal).
        else if (c == '>') next_state = 6;

        // Less (than or equal) or not equal.
        else if (c == '<') next_state = 7;

        // Const.
        else if (c == '"') next_state = 14;
        else if (c == '\'') next_state = 9;
        else if (utils::regex::is_digit_not_zero(c)) next_state = 8;
        else if (c == '0') next_state = 11;
        
        // Unit symbols.
        else if (utils::regex::is_unit_symbol(c)) {
            // TODO: TOK = pesquisarToken
            next_state = 15;
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

    int state1(char c, std::stringstream &lexeme, Source &source) {

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
            source.file.putback(c);
        }
       
        return next_state;
    }

    int state2(char c, std::stringstream &lexeme, int curr_line) {
        int next_state = 2;
        lexeme << c;

        if (c == '_' || c == '.');
        else if (utils::regex::is_letter(c) || utils::regex::is_digit(c))
            next_state = 1;
        else {
            std::stringstream err;
            err << curr_line << ": lexema nao identificado ["
                << lexeme.str() << "].";
            throw std::runtime_error(err.str());
        }

        return next_state;
    }
}
