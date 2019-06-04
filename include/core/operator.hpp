/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#ifndef CORE_OPERATOR_HPP_
#define CORE_OPERATOR_HPP_

#include <string>
#include "core/type.hpp"

namespace core {

    // Enum containing all operators of the language
    enum class Operator {
        None, // Used to simplify semantic actions.

        Add,
        Sub,
        Or,
        Mult,
        Div,
        And,
        Mod,
        Eq,
        Neq,
        Lt,
        Lte,
        Gt,
        Gte
    };

}

#endif
