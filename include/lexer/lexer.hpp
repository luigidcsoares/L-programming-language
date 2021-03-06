/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#ifndef LEXER_LEXER_HPP_
#define LEXER_LEXER_HPP_

#include <fstream>

#include "utils/source.hpp"
#include "core/token.hpp"
#include "core/type.hpp"

using namespace core;
using namespace utils;

namespace lexer {

    /**
     * Read and return the next valid token or the first error found.
     */
    void next();

    /**
     * A tagged union used to represent the lexical register.
     */
    struct LexReg {
        // Control field used to track what we've assigned to
        // the union piece.
        enum { Const, Id_Kw } tag;

        // Common fields.
        Token token;  
        std::string lexeme;

        // By variable field we mean that for a const token we'll
        // use the type and length fields, but for identifiers and
        // reserved keywords we'll use a pointer to the element
        // in the table of symbols.
        union {
            struct { 
                Type type;
                int length;
            };

            struct {
                TSymbolElem * p_tab_elem;
            };
        };

        /**
         * Fill all the fields with the received values.
         *
         * This function assumes (from the type of params it receives)
         * that you'll be using the const piece of the union.
         *
         * @param: core::Token, token -> token
         * @param: string, lexeme -> lexeme
         * @param: core::Type, type -> type
         * @param: int, length -> length
         *
         */
        void fill(Token token, std::string lexeme,
                Type type, int length);

        /**
         * Fill all the fields with the received values.
         *
         * This function assumes (from the type of params it receives)
         * that you'll be using the id or keyword piece of the union.
         *
         * @param: core::Token token -> token
         * @param: string lexeme -> lexeme
         * @param: TSymbolEleme * p_tab_elem -> pointer to tyble of symbols position
         *
         */
        void fill(Token token, std::string lexeme,
                TSymbolElem * p_tab_elem);
    };
}

#endif
