/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#include <iostream>
#include "core/class.hpp"
#include "core/table_symbol.hpp"

namespace core {
    TSymbolElem::TSymbolElem(std::string lexeme, Token token) {
        this->lexeme = lexeme;
        this->token = token;
        this->cl = Class::Empty;
        this->end = -1;
    }

    TSymbolElem * TSymbol::search(std::string lexeme) {
        auto it = this->tab_symbol.find(lexeme);

        // it->first: key <string> (this is the lexeme).
        // it->second: element <TSymbolElem>.
        return it != this->tab_symbol.end() ? &it->second : NULL;
    }

    TSymbolElem * TSymbol::insert(std::string lexeme, TSymbolElem elem) {
        // unoredered_map::insert returns a pair made by an iterator
        // and a boolean. Iterator is made by the key and the element inserted.
        // From iterator we took the element inserted (TSymbolElem).
        return &this->tab_symbol.insert({ lexeme, elem }).first->second;
    }
}
