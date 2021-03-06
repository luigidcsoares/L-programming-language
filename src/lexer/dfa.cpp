/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#include <algorithm>
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
    
    /**
     *  Implementations of all language machine states
     */
    int state0(char c, std::stringstream &lexeme) {
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
        
        // Unit symbols are symbols made by only one char and have
        // a direct transition from initial state (0) to final
        // state (15).
        else if (utils::is_unit_symbol(c)) {
            // We guarantee that these symbols are in the table since
            // they have to be inserted in the beginning of the program.
            // Thus, no need to check for null case.
            TSymbolElem *p = g_tab_symbol.search(lexeme.str());
            g_lex_reg.fill(p->token, lexeme.str(), p);
        
            next_state = 15;
        }
     
        // If the character read was EOF we can safely assume
        // that our compilation process ended correctly. We're setting
        // the global lexical register token field as EOFL for handling
        // the end of parser and thus the end of program. There's no
        // need to save EOF in table of symbols so we're setting addr
        // field as NULL.
        else if (c == EOF) {
            g_lex_reg.fill(Token::EOFL, "eof", NULL);
            next_state = 15;
        }

        // Lexeme unidentified.
        else {
            std::stringstream err;
            err << g_source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";
            
            // Showing newline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");
            throw std::runtime_error(s);
        }

        return next_state;
    }

    int state1(char c, std::stringstream &lexeme) {
        int next_state = 1;

        if (utils::is_letter(c) || utils::is_digit(c) ||
                c == '_' || c == '.') {
            lexeme << c;
        } else {
            // L is case insensitive.
            std::string lower_lex = lexeme.str();
            std::transform(
                    lower_lex.begin(), lower_lex.end(),
                    lower_lex.begin(), ::tolower
            );

            // Search for the lexeme.
            TSymbolElem *p = g_tab_symbol.search(lower_lex);
            Token tok;

            // If the search returns null this is a new identifier
            // and thus must be inserted in the table.
            if (p == NULL) {
                tok = Token::Id;
                TSymbolElem elem(lexeme.str(), tok);
                p = g_tab_symbol.insert(lower_lex, elem);
            } 
            
            // Else we just need to get that token to pass to
            // the lexical register.
            else tok = p->token;

            g_lex_reg.fill(tok, lower_lex, p);

            // Put character back to be read again and go to the
            // final state.
            g_source.file.putback(c);
            next_state = 15;
        }

        return next_state;
    }

    int state2(char c, std::stringstream &lexeme) {
        int next_state = 2;
        lexeme << c;

        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << g_source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        // Since we didn't reach EOF, we can go on.
        else if (utils::is_letter(c) || utils::is_digit(c))
            next_state = 1;

        else if (c != '.' && c != '_') {
            std::stringstream err;
            err << g_source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";

            // Showing newline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");

            throw std::runtime_error(s);
        }

        return next_state;
    }


    int state3(char c, std::stringstream &lexeme) {
        int next_state;

        if (c == '*') {
            lexeme.str("");
            next_state = 4;
        } else {
            TSymbolElem *p = g_tab_symbol.search(lexeme.str());
            g_lex_reg.fill(p->token, lexeme.str(), p);

            // Put character back to be read again.
            g_source.file.putback(c);
            next_state = 15;
        }

        return next_state;
    }

    int state4(char c, std::stringstream &lexeme) {
        int next_state = 4;
        
        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << g_source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        else if (c == '*') next_state = 5;

        return next_state;
    }

    int state5(char c, std::stringstream &lexeme) {
        int next_state = 5;
        
        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << g_source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        else if (c == '/') next_state = 0;
        else if (c != '*') next_state = 4;

        return next_state;
    }

    int state6(char c, std::stringstream &lexeme) {
        // Token: >=
        if (c == '=') lexeme << c;
        
        // Token: >
        // Put character back to be read again.
        else g_source.file.putback(c);

        TSymbolElem *p = g_tab_symbol.search(lexeme.str());
        g_lex_reg.fill(p->token, lexeme.str(), p);

        return 15;
    }

    int state7(char c, std::stringstream &lexeme) {
        // Token: <= or <>
        if (c == '>' || c == '=') lexeme << c;
        
        // Token: <
        // Put character back to be read again.
        else g_source.file.putback(c);

        TSymbolElem *p = g_tab_symbol.search(lexeme.str());
        g_lex_reg.fill(p->token, lexeme.str(), p);

        return 15;
    }

    int state8(char c, std::stringstream &lexeme) {
        int next_state = 8;

        if (utils::is_digit(c)) lexeme << c;
        else {
            TSymbolElem *p = g_tab_symbol.search(lexeme.str());
            g_lex_reg.fill(Token::Const, lexeme.str(), 
                    Type::Integer, 0);
           
            // Put character back to be read again.
            g_source.file.putback(c);
            next_state = 15;
        }

        return next_state;
    }

    int state9(char c, std::stringstream &lexeme) {
        lexeme << c;
        
        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << g_source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        // Since this state represents a alphanum char, we know
        // that every valid char will be accepted, so no need
        // for checking this. 
        return 10;
    }
    
    int state10(char c, std::stringstream &lexeme) {
        lexeme << c;

        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << g_source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
       
        // Handling unidentified lexeme.
        else if (c != '\'') {
            std::stringstream err;
            err << g_source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";
            
            // Showing newline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");

            throw std::runtime_error(s);
        }

        TSymbolElem *p = g_tab_symbol.search(lexeme.str());
        g_lex_reg.fill(Token::Const, lexeme.str(), Type::Char, 0);

        return 15;
    }

    int state11(char c, std::stringstream &lexeme) {
        int next_state;

        if (utils::is_digit(c)) {
            lexeme << c;
            next_state = 8;
        } else if (c == 'X' || c == 'x') {
            lexeme << c;
            next_state = 12;
        } else {
            TSymbolElem *p = g_tab_symbol.search(lexeme.str());
            g_lex_reg.fill(Token::Const, lexeme.str(), 
                    Type::Integer, 0);
            
            // Put character back to be read again.
            g_source.file.putback(c);
            next_state = 15;
        }

        return next_state;
    }

    int state12(char c, std::stringstream &lexeme) {
        lexeme << c;
        
        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << g_source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 

        // Handling unidentified lexeme.
        else if (!utils::is_hexa(c)) {
            std::stringstream err;
            err << g_source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";

            // Showing newline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");

            throw std::runtime_error(s);
        }

        return 13;
    }

    
    int state13(char c, std::stringstream &lexeme) {
        lexeme << c;
       
        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << g_source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        // Handling unidentified lexeme.
        else if (!utils::is_hexa(c)) {
            std::stringstream err;
            err << g_source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";
            
            // Showing newline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");

            throw std::runtime_error(s);
        }

        TSymbolElem *p = g_tab_symbol.search(lexeme.str());
        g_lex_reg.fill(Token::Const, lexeme.str(), Type::Char, 0);

        return 15;
    }

    int state14(char c, std::stringstream &lexeme) {
        int next_state = 14;
        lexeme << c;

        // Handling unexpected EOF.
        if (c == EOF) {
            std::stringstream err;
            err << g_source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        // Handling unidentified lexeme.
        else if (c == '$' || c == '\r' || c == '\n') {
            std::stringstream err;
            err << g_source.curr_line << ":lexema nao identificado ["
                << lexeme.str() << "].";
            
            // Showing newline properly.
            std::string s = err.str();
            s = std::regex_replace(s, std::regex("\r"), "\\r");
            s = std::regex_replace(s, std::regex("\n"), "\\n");

            throw std::runtime_error(s);
        } 
        
        // If we read a second quote, it is a valid string.
        else if (c == '"') {
            TSymbolElem *p = g_tab_symbol.search(lexeme.str());
            g_lex_reg.fill(Token::Const, lexeme.str(), 
                    Type::String, lexeme.str().length() - 2);

            next_state = 15;
        }

        return next_state;
    }
}
