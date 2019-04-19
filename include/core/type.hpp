#ifndef CORE_TYPE_HPP_
#define CORE_TYPE_HPP_

namespace core::type {
   
    // List of types (implicit and explicit).
    enum class Type {
        // Explicit types.
        Integer,
        Char,

        // Implicit types.
        Bool, // Defined as 0 (false) or 1 (true).
        String // Defined as a vector of chars, with a $ at the end.
    };
}

#endif
