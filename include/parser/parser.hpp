/**
 * @author: gabriel luciano
 * @author: geovane fonseca
 * @author: luigi domenico
 */

#ifndef PARSER_PARSER_HPP_
#define PARSER_PARSER_HPP_

#include "core/token.hpp"
#include "core/table_symbol.hpp"

using namespace core;

namespace parser {

    /**
     * Call lexer to match the current token with the expected.
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
     *
     * @param Type: DV_type -> Char or Integer.
     */
    void DV(Type DV_type);

    /**
     * The optional part of declaring a variable.
     *
     * @param TSymbolElem*: DVO_id -> Position of id in the table of symbols.
     */
    void DVO(TSymbolElem* DVO_id);

    /**
     * Command.
     * Should begin with an identifier or with the following keywords:
     * for, if, ; (nullable command), readln, write, writeln.
     */
    void C();

    /**
     * List of commands.
     * Could be either a single command or a list of
     * zero or more commands between curly braces.
     */
    void LC();

    /**
     * Exp is the first non-terminal symbol that refers to an expression.
     * Should call the ExpS non-terminal symbol.
     * Its rule is responsible to operators of less precedence (comparison
     * operators)
     *
     * Attributes:
     * @param Type&: Exp_type
     * @param int&: Exp_length
     * @param int&: Exp_addr
     */
    void Exp(Type &Exp_type, int &Exp_length, int &Exp_addr);

    /**
     * ExpS is a non-terminal symbol called by Exp.
     * It is responsible by the add (arithmetic and logical) and sub
     * operators.
     *
     * Attributes:
     * @param Type&: ExpS_type
     * @param int&: ExpS_length
     * @param int&: ExpS_addr
     */
    void ExpS(Type &ExpS_type, int &ExpS_length, int &ExpS_addr);

    /**
     * T refers to the terms of an expression.
     * It is a non-terminal symbol responsible the the mult (arithmetic and 
     * logical), div and mod (%) operators.
     *
     * Attributes:
     * @param Type&: T_type
     * @param int&: T_length
     * @param int&: T_addr
     */
    void T(Type &T_type, int &T_length, int &T_addr);

    /**
     * F is the last non-terminal symbol that refers to an expression.
     * It is responsible by the operators of greater precedence.
     *
     * Attributes:
     * @param Type&: F_type
     * @param int&:  F_length
     * @param int&:  F_addr
     */
    void F(Type &F_type, int &F_length, int &F_addr);

}

#endif
