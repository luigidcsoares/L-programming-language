#include <iostream>
#include <string>

#include "core/global.hpp"
#include "core/table_symbol.hpp"
#include "core/token.hpp"
#include "lexer/lexer.hpp"
#include "utils/source.hpp"

using namespace utils;
using namespace core;

int main(int argc, char *argv[]) {
    int exit_code = EXIT_SUCCESS;

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
    g_tab_symbol.insert(",", TSymbolElem(",", Token::Comma));
    g_tab_symbol.insert("+", TSymbolElem("+", Token::Add));
    g_tab_symbol.insert("-", TSymbolElem("-", Token::Sub));
    g_tab_symbol.insert("*", TSymbolElem("*", Token::Mult));
    g_tab_symbol.insert(";", TSymbolElem(";", Token::Semicolon));
    g_tab_symbol.insert("{", TSymbolElem("{", Token::LBrace));
    g_tab_symbol.insert("}", TSymbolElem("}", Token::RBrace));
    g_tab_symbol.insert("then", TSymbolElem("then", Token::Then));
    g_tab_symbol.insert("readln", TSymbolElem("readln", Token::Readln));
    g_tab_symbol.insert("step", TSymbolElem("step", Token::Step));
    g_tab_symbol.insert("do", TSymbolElem("do", Token::Do));
    g_tab_symbol.insert("write", TSymbolElem("write", Token::Write));
    g_tab_symbol.insert("writeln", TSymbolElem("writeln", Token::Writeln));
    g_tab_symbol.insert("%", TSymbolElem("%", Token::Percent));
    g_tab_symbol.insert("[", TSymbolElem("[", Token::LBracket));
    g_tab_symbol.insert("]", TSymbolElem("]", Token::RBracket));
    
    std::string input = argv[1];
    Source source(input);
    
    try {
        while (source.file.peek() != EOF)
            lexer::next(source);
        
        // Procedimento simbolo inicial, 
        // Se não EOF: erro;
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }

    source.file.close();
    return exit_code;
}
