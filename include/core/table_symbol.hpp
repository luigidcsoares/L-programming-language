/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */

#ifndef CORE_TABLE_SYMBOL_HPP_
#define CORE_TABLE_SYMBOL_HPP_

#include <string>
#include <unordered_map>
#include "core/class.hpp"
#include "core/token.hpp"

namespace core {

    // Table of symbols struct
    struct TSymbolElem {
        std::string lexeme;
        Token token;
        Class cl;
        Type type;
        int length;
        int addr;
        
        TSymbolElem(std::string lexeme, Token token);
    };

    class TSymbol {
        // Table of symbols itself
        private:
            std::unordered_map<std::string, TSymbolElem> tab_symbol;

        public:
            /**
             * Search an element in table of symbols
             * @param: string, lexeme -> Element to be searched.
             * return: true: pointer to the position of the element, false: NULL
             */ 
            TSymbolElem * search(std::string lexeme);

            /**
             * Insert an element into table of symbols
             * @param: string, lexeme -> Element to be inserted
             * @param: TSymbolElement, elem -> Table of symbols struct
             * @return: true: inserted value memory position
             */ 
            TSymbolElem * insert(std::string lexeme, TSymbolElem elem);
    };
}


#endif
