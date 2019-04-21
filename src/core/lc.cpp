/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#include <iostream>
#include <string>

#include "core/global.hpp"
#include "core/table_symbol.hpp"
#include "core/token.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "utils/source.hpp"

using namespace utils;
using namespace core;
using namespace parser;

/**
 * ********************************************
 * *************** MAIN PROGRAM ***************
 * ********************************************
 */

int main(int argc, char *argv[]) {
    // Fill Table of Symbols with all reserved keywords.
    // Comparison operators (excluding equals) and div operator don't need
    // to be inserted since their tokens are set by the lexer without any need
    // of searching the table.
    g_tab_symbol.insert("const", TSymbolElem("const", Token::ConstKW));
    g_tab_symbol.insert("var", TSymbolElem("var", Token::Var));
    g_tab_symbol.insert("integer", TSymbolElem("integer", Token::Integer));
    g_tab_symbol.insert("char", TSymbolElem("char", Token::Char));
    g_tab_symbol.insert("for", TSymbolElem("for", Token::For));
    g_tab_symbol.insert("if", TSymbolElem("if", Token::If));
    g_tab_symbol.insert("else", TSymbolElem("else", Token::Else));
    g_tab_symbol.insert("and", TSymbolElem("and", Token::And));
    g_tab_symbol.insert("or", TSymbolElem("or", Token::Or));
    g_tab_symbol.insert("not", TSymbolElem("not", Token::Not));
    g_tab_symbol.insert("=", TSymbolElem("=", Token::EQ));
    g_tab_symbol.insert("to", TSymbolElem("to", Token::To));
    g_tab_symbol.insert("(", TSymbolElem("(", Token::LParen));
    g_tab_symbol.insert(")", TSymbolElem(")", Token::RParen));
    g_tab_symbol.insert("<", TSymbolElem("<", Token::LT));
    g_tab_symbol.insert(">", TSymbolElem(">", Token::GT));
    g_tab_symbol.insert("<>", TSymbolElem("<>", Token::NE));
    g_tab_symbol.insert(">=", TSymbolElem(">=", Token::GE));
    g_tab_symbol.insert("<=", TSymbolElem("<=", Token::LE));
    g_tab_symbol.insert(",", TSymbolElem(",", Token::Comma));
    g_tab_symbol.insert("+", TSymbolElem("+", Token::Add));
    g_tab_symbol.insert("-", TSymbolElem("-", Token::Sub));
    g_tab_symbol.insert("*", TSymbolElem("*", Token::Mult));
    g_tab_symbol.insert("/", TSymbolElem("/", Token::Div));
    g_tab_symbol.insert(";", TSymbolElem(";", Token::Semicolon));
    g_tab_symbol.insert("{", TSymbolElem("{", Token::LBrace));
    g_tab_symbol.insert("}", TSymbolElem("}", Token::RBrace));
    g_tab_symbol.insert("then", TSymbolElem("then", Token::Then));
    g_tab_symbol.insert("readln", TSymbolElem("readln", Token::Readln));
    g_tab_symbol.insert("step", TSymbolElem("step", Token::Step));
    g_tab_symbol.insert("do", TSymbolElem("do", Token::Do));
    g_tab_symbol.insert("write", TSymbolElem("write", Token::Write));
    g_tab_symbol.insert("writeln", TSymbolElem("writeln", Token::Writeln));
    g_tab_symbol.insert("%", TSymbolElem("%", Token::Mod));
    g_tab_symbol.insert("[", TSymbolElem("[", Token::LBracket));
    g_tab_symbol.insert("]", TSymbolElem("]", Token::RBracket));

    std::string input = argv[1];
    g_source.file.open(input);
    g_source.curr_line = 1;

    try {
        lexer::next();
        S();
        
        // ????.
        if (g_source.file.peek() != EOF) {
            std::cerr 
                << g_source.curr_line
                << ":"
                << "ERRO (?)" << std::endl;
        }
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
    }

    g_source.file.close();
    return 0;
}
