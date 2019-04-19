#include <iostream>
#include <regex>
#include <sstream>

#include "core/global.hpp"
#include "core/type.hpp"
#include "core/token.hpp"
#include "lexer/dfa.hpp"
#include "lexer/lexer.hpp"
#include "utils/regex.hpp"

using namespace core;

namespace lexer {
    int state0(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 0;

        // Skipping whitespace.
        if (utils::is_whitespace(c)) return next_state;

        // Concatenate char to the lexeme.
        lexeme << c;

        // Identifier and reserved words.
        if (utils::is_letter(c)) next_state = 1;
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
        else if (utils::is_digit_not_zero(c)) next_state = 8;
        else if (c == '0') next_state = 11;
        
        // Unit symbols.
        else if (utils::is_unit_symbol(c)) {
            // TODO: TOK = pesquisarToken
            next_state = 15;
        }

        // End of file: if we reach it, just accept since it isn't an
        // unexpected EOF.
        else if (c == EOF) next_state = 15;

        // Lexeme unidentified.
        else {
            std::stringstream err;
            err << source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";
            
            // Showing breakline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");
        }

        return next_state;
    }

    int state1(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 1;

        if (utils::is_letter(c) ||
                utils::is_digit(c) ||
                c == '_' || 
                c == '.') {

            lexeme << c;
        } else {
            // TODO: TOK = pesquisarToken

            // Put character back to be read again.
            source.file.putback(c);

            next_state = 15;
        }
       

        return next_state;
    }

    int state2(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 2;
        lexeme << c;

        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        // Since we didn't reach EOF, we can go on.
        else if (utils::is_letter(c) || utils::is_digit(c))
            next_state = 1;

        else if (c != '.' && c != '_') {
            std::stringstream err;
            err << source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";

            // Showing breakline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");

            throw std::runtime_error(s);
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
            g_lex_reg.token = Token::Div;

            // Put character back to be read again.
            source.file.putback(c);

            next_state = 15;
        }

        return next_state;
    }

    int state4(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 4;
        
        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        else if (c == '*') next_state = 5;

        return next_state;
    }

    int state5(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 5;
        
        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        else if (c == '/') next_state = 0;
        else if (c != '*') next_state = 4;

        return next_state;
    }

    int state6(char c, std::stringstream &lexeme, Source &source) {
        if (c == '=') {
            lexeme << c;
            g_lex_reg.token = Token::GE;
        } else {
            g_lex_reg.token = Token::GT;

            // Put character back to be read again.
            source.file.putback(c);
        }

        return 15;
    }

    int state7(char c, std::stringstream &lexeme, Source &source) {
        if (c == '>') {
            lexeme << c;
            g_lex_reg.token = Token::NE;
        } else if (c == '=') {
            lexeme << c;
            g_lex_reg.token = Token::LE;
        } else {
            g_lex_reg.token = Token::LT;
            
            // Put character back to be read again.
            source.file.putback(c);
        }

        return 15;
    }

    int state8(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 8;

        if (utils::is_digit(c)) lexeme << c;
        else {
            g_lex_reg.token = Token::Const;
            g_lex_reg.type = Type::Integer;
            g_lex_reg.length = 0;

            // Put character back to be read again.
            source.file.putback(c);

            next_state = 15;
        }

        return next_state;
    }

    int state9(char c, std::stringstream &lexeme, Source &source) {
        lexeme << c;
        
        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        // Since this state represents a alphanum char, we know
        // that every valid char will be accepted, so no need
        // for checking this. 
        return 10;
    }
    
    int state10(char c, std::stringstream &lexeme, Source &source) {
        lexeme << c;

        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
       
        // Handling unidentified lexeme.
        else if (c != '\'') {
            std::stringstream err;
            err << source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";
            
            // Showing breakline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");

            throw std::runtime_error(s);
        }

        g_lex_reg.token = Token::Const;
        g_lex_reg.type = Type::Char;
        g_lex_reg.length = 0;

        return 15;
    }

    int state11(char c, std::stringstream &lexeme, Source &source) {
        int next_state;

        if (utils::is_digit(c)) {
            lexeme << c;
            next_state = 8;
        } else if (c == 'X' || c == 'x') {
            lexeme << c;
            next_state = 12;
        } else {
            g_lex_reg.token = Token::Const;
            g_lex_reg.type = Type::Integer; 
            g_lex_reg.length = 0;

            // Put character back to be read again.
            source.file.putback(c);

            next_state = 15;
        }

        return next_state;
    }

    int state12(char c, std::stringstream &lexeme, Source &source) {
        lexeme << c;
        
        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 

        // Handling unidentified lexeme.
        else if (!utils::is_hexa(c)) {
            std::stringstream err;
            err << source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";

            // Showing breakline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");

            throw std::runtime_error(s);
        }

        return 13;
    }

    
    int state13(char c, std::stringstream &lexeme, Source &source) {
        lexeme << c;
       
        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        // Handling unidentified lexeme.
        else if (!utils::is_hexa(c)) {
            std::stringstream err;
            err << source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";
            
            // Showing breakline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");

            throw std::runtime_error(s);
        }

        g_lex_reg.token = Token::Const;
        g_lex_reg.type = Type::Char;
        g_lex_reg.length = 0;

        return 15;
    }

    int state14(char c, std::stringstream &lexeme, Source &source) {
        int next_state = 14;
        lexeme << c;

        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        // Handling unidentified lexeme.
        else if (c == '$' || c == '\r' || c == '\n') {
            std::stringstream err;
            err << source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";
            
            // Showing breakline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");

            throw std::runtime_error(s);
        } 
        
        // If we read a second quote, it is a valid string.
        else if (c == '"') {
            g_lex_reg.token = Token::Const;
            g_lex_reg.type = Type::String;
            g_lex_reg.length = 0;

            next_state = 15;
        }

        return next_state;
    }
}
