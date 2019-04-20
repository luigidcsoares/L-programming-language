/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#ifndef CORE_GLOBAL_HPP_
#define CORE_GLOBAL_HPP_

#include <string>

#include "core/table_symbol.hpp"
#include "lexer/lexer.hpp"

using namespace core;
using namespace lexer;

// Global declarations
namespace core {
    // Lexical register.
    extern LexReg g_lex_reg;

    // Table of symbols.
    extern TSymbol g_tab_symbol;
}

#endif
