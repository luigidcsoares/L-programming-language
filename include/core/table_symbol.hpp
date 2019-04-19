#ifndef CORE_TABLE_SYMBOL_HPP_
#define CORE_TABLE_SYMBOL_HPP_

#include <string>
#include <unordered_map>
#include "core/token.hpp"

namespace core {

    struct TSymbolElem {
        std::string lexeme;
        Token token;

        // TODO: other fields (class, type, length...).
    };

    class TSymbol {
        private:
            std::unordered_map<std::string, TSymbolElem> tab_symbol;

        public:
            TSymbolElem * search(std::string lexeme);
            TSymbolElem * insert(std::string lexeme, TSymbolElem elem);
    };
}


#endif
