/**
 * @author: gabriel luciano
 * @author: geovane fonseca
 * @author: luigi domenico
 */

#ifndef PARSER_PARSER_HPP_
#define PARSER_PARSER_HPP_

#include "core/token.hpp"

using namespace core;

namespace parser {

    /**
     * Call lexer to match the current token with the next.
     *
     * @param: core::Token, expected_tok -> The next expected token
     */
    void match_token(Token expected_tok);

    /**
     * Initial non-terminal symbol of the grammar.
     * Every L program must be in the following format:
     * {D} {C} EOFL
     * where D := declaration (var or const)
     * and   C := command (if, for, do...).
     */
    void S();

    /**
     * Variable or constant declaration.
     * Should begin with Var or Const keywords.
     */
    void D();

    /**
     * Variable declaration.
     * Should begin with an identifier.
     */
    void DV();

    /**
     * Command.
     * Should begin with an identifier or with the following keywords:
     * for, if, ; (nullable command), readln, write, writeln.
     */
    void C();

    /**
     * Exp is the first non-terminal symbol that refers to an expression.
     * Should call the ExpS non-terminal symbol.
     * Its rule is responsible to operators of less precedence (comparison
     * operators)
     */
    void Exp();

    /**
     * ExpS is a non-terminal symbol called by Exp.
     * It is responsible by the add (arithmetic and logical) and sub
     * operators.
     */
    void ExpS();

    /**
     * T refers to the terms of an expression.
     * It is a non-terminal symbol responsible the the mult (arithmetic and 
     * logical), div and mod (%) operators.
     */
    void T();

    /**
     * F is the last non-terminal symbol that refers to an expression.
     * It is responsible by the operators of greater precedence.
     */
    void F();

}

#endif
