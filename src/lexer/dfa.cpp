#include <iostream>
#include <sstream>

#include "core/global.hpp"
#include "core/token.hpp"
#include "lexer/dfa.hpp"
#include "utils/regex.hpp"

using namespace core;
using namespace core::token;

namespace lexer::dfa {
    int state0(char c, std::stringstream &lexeme, Source &source) {
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
            err << source.curr_line << ": lexema nao identificado ["
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

    int state2(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 2;
        lexeme << c;

        if (utils::regex::is_letter(c) || utils::regex::is_digit(c))
            next_state = 1;

        else if (c != '.' && c != '_') {
            std::stringstream err;
            err << source.curr_line << ": lexema nao identificado ["
                << lexeme.str() << "].";
            throw std::runtime_error(err.str());
        }

        return next_state;
    }


    int state3(char c, std::stringstream &lexeme, Source &source) {
        int next_state;

        if (c == '*') {
            lexeme.str("");
            next_state = 4;
        } else {
            // Set token as div operator.
            global::token_reg.token = Token::Div;

            // Put character back to be read again.
            source.file.putback(c);

            next_state = 15;
        }

        return next_state;
    }

    int state4(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 4;
        if (c == '*') next_state = 5;
        return next_state;
    }

    int state5(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 5;
        if (c == '/') next_state = 0;
        else if (c != '*') next_state = 4;
        return next_state;
    }

    int state6(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 15;

        if (c == '=') {
            lexeme << c;
            global::token_reg.token = Token::GE;
        } else {
            global::token_reg.token = Token::GT;

            // Put character back to be read again.
            source.file.putback(c);
        }

        return next_state;
    }

    int state7(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 15;

        if (c == '>') {
            lexeme << c;
            global::token_reg.token = Token::NE;
        } else if (c == '=') {
            lexeme << c;
            global::token_reg.token = Token::LE;
        } else {
            global::token_reg.token = Token::LT;
            
            // Put character back to be read again.
            source.file.putback(c);
        }

        return next_state;
    }

    int state8(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 8;

        if (utils::regex::is_digit(c)) lexeme << c;
        else {
            global::token_reg.token = Token::Const;
            global::token_reg.type = "integer";
            global::token_reg.length = 0;

            // Put character back to be read again.
            source.file.putback(c);

            next_state = 15;
        }

        return next_state;
    }

    int state9(char c, std::stringstream &lexeme, Source &source) {
        lexeme << c;

        // Since this state represents a alphanum char, we know
        // that every valid char will be accepted, so no need
        // for checking this. 
        //
        // TODO: handle EOF (?)
        return 9;
    }
}
