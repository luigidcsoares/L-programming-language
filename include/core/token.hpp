/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#ifndef CORE_TOKEN_HPP_
#define CORE_TOKEN_HPP_

#include <string>
#include "core/type.hpp"

namespace core {

    // Enum containing all language reserved words
    enum class Token {
        // Reserved words:
        ConstKW, // KW to diff from constants.
        Var,
        Integer,
        Char,
        For,
        If,
        Else,
        And,
        Or,
        Not,
        EQ, // Comparison or assignment.
        To,
        LParen, // '('.
        RParen, // ')'.
        LT, // Less than.
        GT, // Greater than.
        NE, // Not equal.
        GE, // Greater than or equal.
        LE, // Less than or equal.
        Comma,
        Add,
        Sub,
        Mult,
        Div, // Used for division or comments.
        Semicolon,
        LBrace, // '{'.
        RBrace, // '}'.
        Then,
        Readln,
        Step,
        Do,
        Write,
        Writeln,
        Mod, // Mod operator (%).
        LBracket, // '['.
        RBracket, // ']'.

        // Other tokens (defined in runtime).
        Id,
        Const, // String, char (including hexa) or integer.

        // EOFL (End of file) is a special token used in both lexer
        // and parser. Every program written in L have the following
        // structure: Declarations Commands EOFL.
        //
        // Lexer: EOFL appears in the initial state, being used to
        // help ending the lexical analysis.
        //
        // Parser: EOLF appears as the last token in the rule of
        // initial non-terminal symbol. In that case, it helps
        // handling errors correctly.
        EOFL
    };
}

#endif
