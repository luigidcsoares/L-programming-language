/**
 * @author: gabriel luciano
 * @author: geovane fonseca
 * @author: luigi domenico
 */

#include <iostream>
#include <sstream>
#include "codegen/codegen.hpp"
#include "core/class.hpp"
#include "core/global.hpp"
#include "core/operator.hpp"
#include "core/token.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

using namespace codegen;
using namespace core; 

namespace parser {

    void match_token(Token expected_tok) {
        if (g_lex_reg.token == expected_tok) lexer::next();

        // First handle unexpected EOF error.
        else if (g_lex_reg.token == Token::EOFL) {
            std::stringstream err;
            err << g_source.curr_line << ":fim de arquivo nao esperado.";
            throw std::runtime_error(err.str());
        } 
        
        // Then handle unexpected token error.
        else {
            std::stringstream err;
            err << g_source.curr_line << ":token nao esperado ["
                << g_lex_reg.lexeme << "].";
            throw std::runtime_error(err.str());
        }
    }

    void S() {
        // Create stack segment & init data segment.
        create_sseg();
        init_dseg();

        // While token belongs to First of {D},
        // call D.
        while (g_lex_reg.token == Token::Var
                || g_lex_reg.token == Token::ConstKW)
            D();

        // End dseg & init code segment;
        end_dseg();
        init_cseg();

        // While token belongs to First of {C},
        // call C.
        while (g_lex_reg.token == Token::Id
                || g_lex_reg.token == Token::For
                || g_lex_reg.token == Token::If
                || g_lex_reg.token == Token::Semicolon
                || g_lex_reg.token == Token::Readln
                || g_lex_reg.token == Token::Write
                || g_lex_reg.token == Token::Writeln)
            C();

        // End code segment & program.
        end_cseg();
    }

    void D() {
        Type DV_type;
        bool cond;
        int signal;
        TSymbolElem* id;

        if (g_lex_reg.token == Token::Var) {
            match_token(Token::Var);

            // Repeat until token isn't integer nor char.
            do {
                if (g_lex_reg.token == Token::Integer) {
                    match_token(Token::Integer);
                    DV_type = Type::Integer;
                } else {
                    match_token(Token::Char);
                    DV_type = Type::Char;
                }

                DV(DV_type);
                match_token(Token::Semicolon);

            } while (g_lex_reg.token == Token::Integer
                    || g_lex_reg.token == Token::Char);

        } else {
            match_token(Token::ConstKW);

            id = g_lex_reg.p_tab_elem;
            int curr_line = g_source.curr_line;
            match_token(Token::Id);

            // Error if ID was already declared.
            if (id->cl != Class::Empty) {
                std::stringstream err;
                err << curr_line << ":identificador ja declarado ["
                    << id->lexeme << "].";
                throw std::runtime_error(err.str());
            }

            match_token(Token::EQ);
            cond = false;

            if (g_lex_reg.token == Token::Add) {
                cond = true;
                signal = 1;

                match_token(Token::Add);
            } else if (g_lex_reg.token == Token::Sub) {
                cond = true;
                signal = -1;

                match_token(Token::Sub);
            }

            std::string const_lex = g_lex_reg.lexeme;
            Type const_type = g_lex_reg.type;
            int const_length = g_lex_reg.length;
            curr_line = g_source.curr_line;

            match_token(Token::Const);

            if (cond && const_type != Type::Integer) {
                std::stringstream err;
                err << curr_line << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            } else if (const_type == Type::String) {
                std::stringstream err;
                err << curr_line << ":classe de identificador incompatível ["
                    << const_lex << "].";
                throw std::runtime_error(err.str());
            } else {
                id->type = const_type;
                id->length = const_length;
                id->cl = Class::Const;
            }

            int val;
            if (id->type == Type::Integer) {
                val = std::stoi(const_lex);

                if (cond) val = signal * val;
            } else {
                val = const_lex[1];
            }

            id->end = put_dseg(id->cl, id->type, id->length, val);
            match_token(Token::Semicolon);
        }
    }

    void DV(Type DV_type) {
        TSymbolElem *DVO_id;
        TSymbolElem *DVO1_id;

        TSymbolElem *id = g_lex_reg.p_tab_elem;
        int curr_line = g_source.curr_line;
        match_token(Token::Id);

        // Error if ID was already declared.
        if (id->cl != Class::Empty) {
            std::stringstream err;
            err << curr_line << ":identificador ja declarado ["
                << id->lexeme << "].";
            throw std::runtime_error(err.str());
        }

        // Else set variable class and type.
        else {
            id->cl = Class::Var;
            id->type = DV_type;
        }

        DVO_id = id;
        DVO(DVO_id);

        while (g_lex_reg.token == Token::Comma) {
            match_token(Token::Comma);

            id = g_lex_reg.p_tab_elem;
            int curr_line = g_source.curr_line;
            match_token(Token::Id);

            // Error if ID was already declared.
            if (id->cl != Class::Empty) {
                std::stringstream err;
                err << curr_line << ":identificador ja declarado ["
                    << id->lexeme << "].";
                throw std::runtime_error(err.str());
            }

            // Else set variable class and type.
            else {
                id->cl = Class::Var;
                id->type = DV_type;
                DVO1_id = id;
            }

            DVO(DVO1_id);
        }
    }
    
    void DVO(TSymbolElem* DVO_id) {
        DVO_id->length = 0;
        int signal;
        bool cond;

        if (g_lex_reg.token == Token::EQ) {
            cond = false;
            match_token(Token::EQ);

            if (g_lex_reg.token == Token::Add) {
                match_token(Token::Add);
                signal = 1;
                cond = true;
            } else if (g_lex_reg.token == Token::Sub) {
                match_token(Token::Sub);
                signal = -1;
                cond = true;
            }

            Type const_type = g_lex_reg.type;
            match_token(Token::Const);

            bool error = false;
            if (cond && const_type != Type::Integer) {
                error = true;
            } else if (DVO_id->type != const_type) {
                error = true;
            }
        
            if (error) {
                std::stringstream err;
                err << g_source.curr_line 
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            }
        } else if (g_lex_reg.token == Token::LBracket) {
            match_token(Token::LBracket);
            
            std::string const1_lex = g_lex_reg.lexeme;
            Type const1_type = g_lex_reg.type;
            match_token(Token::Const);

            if (const1_type != Type::Integer) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            }

            if (std::stoi(const1_lex) <= 0) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tamanho do vetor insuficiente.";
                throw std::runtime_error(err.str());
            }

            if (DVO_id->type == Type::Integer) {
                if (std::stoi(const1_lex) > 2048) {
                    std::stringstream err;
                    err << g_source.curr_line
                        << ":tamanho do vetor excede o máximo permitido.";
                    throw std::runtime_error(err.str());
                }       
            } else if (std::stoi(const1_lex) > 4096) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tamanho do vetor excede o máximo permitido.";
                throw std::runtime_error(err.str());
            }

            DVO_id->length = std::stoi(const1_lex);
            match_token(Token::RBracket);
        }
    }

    void C() {
        TSymbolElem* id;
        bool cond;

        Type Exp_type;
        int Exp_length;
        Type Exp1_type;
        int Exp1_length;

        if (g_lex_reg.token == Token::Id) {
            id = g_lex_reg.p_tab_elem;
            int curr_line = g_source.curr_line;
            match_token(Token::Id);

            if (id->cl == Class::Empty) {
                std::stringstream err;
                err << curr_line
                    << ":identificador nao declarado ["
                    << id->lexeme << "].";
                throw std::runtime_error(err.str());
            }

            if (id->cl == Class::Const) {
                std::stringstream err;
                err << curr_line
                    << ":classe de identificador incompatível ["
                    << id->lexeme << "].";
                throw std::runtime_error(err.str());
            }

            cond = false;
            if (g_lex_reg.token == Token::LBracket) {
                cond = true;
        
                match_token(Token::LBracket);
                Exp(Exp_type, Exp_length);

                bool error = false;
                if (Exp_type != Type::Integer) {
                    error = true;
                } else if (id->length == 0) {
                    error = true;
                }

                if (error) {
                    std::stringstream err;
                    err << g_source.curr_line
                        << ":tipos incompatíveis.";
                    throw std::runtime_error(err.str());
                }

                match_token(Token::RBracket);
            }

            match_token(Token::EQ);
            Exp(Exp1_type, Exp1_length);

            bool error = false;
            if (Exp1_type == Type::Bool) {
                error = true;

                // Accessing element of vector.
            } else if (cond) {
                if (id->type != Exp1_type) {
                    error = true;
                } else if (Exp1_length != 0) {
                    error = true;
                }
            } else if (id->type == Type::Integer) {
                if (Exp1_type != Type::Integer) {
                    error = true;
                } else if (id->length != 0 || Exp1_length != 0) {
                    error = true;
                }
            } else if (id->length == 0 && Exp1_length != 0) {
                error = true;
            } else if (! (Exp1_type == Type::Char || Exp1_type == Type::String)) {
                error = true;
            } else if (Exp1_type == Type::String) {
                if (id->length < Exp1_length + 1) {
                    error = true;
                }
            } else if (id->length < Exp1_length) {
                error = true;
            }

            if (error) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            }

            match_token(Token::Semicolon);
        } else if (g_lex_reg.token == Token::For) {
            match_token(Token::For);

            id = g_lex_reg.p_tab_elem;
            int curr_line = g_source.curr_line;
            match_token(Token::Id);

            if (id->cl == Class::Empty) {
                std::stringstream err;
                err << curr_line
                    << ":identificador nao declarado ["
                    << id->lexeme << "].";
                throw std::runtime_error(err.str());
            }

            if (id->cl == Class::Const) {
                std::stringstream err;
                err << curr_line
                    << ":classe de identificador incompatível ["
                    << id->lexeme << "].";
                throw std::runtime_error(err.str());
            }

            match_token(Token::EQ);
            Exp(Exp_type, Exp_length);

            if (Exp_type != Type::Integer) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            }

            match_token(Token::To);
            Exp(Exp1_type, Exp1_length);

            if (Exp1_type != Type::Integer) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            }

            if (g_lex_reg.token == Token::Step) {
                match_token(Token::Step);

                if (g_lex_reg.type != Type::Integer) {
                    std::stringstream err;
                    err << g_source.curr_line
                        << ":tipos incompatíveis.";
                    throw std::runtime_error(err.str());
                }

                match_token(Token::Const);
            }

            match_token(Token::Do);
            LC();
        } else if (g_lex_reg.token == Token::If) {
            match_token(Token::If);
            Exp(Exp_type, Exp_length);

            if (Exp_type != Type::Bool) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            }

            match_token(Token::Then);
            LC();

            if (g_lex_reg.token == Token::Else) {
                match_token(Token::Else);
                LC();
            }
        } else if (g_lex_reg.token == Token::Semicolon) {
            match_token(Token::Semicolon);
        } else if (g_lex_reg.token == Token::Readln) {
            match_token(Token::Readln);
            match_token(Token::LParen);

            id = g_lex_reg.p_tab_elem;
            int curr_line = g_source.curr_line;
            match_token(Token::Id);

            if (id->cl == Class::Empty) {
                std::stringstream err;
                err << curr_line
                    << ":identificador nao declarado ["
                    << id->lexeme << "].";
                throw std::runtime_error(err.str());
            }

            if (id->cl == Class::Const) {
                std::stringstream err;
                err << curr_line
                    << ":classe de identificador incompatível ["
                    << id->lexeme << "].";
                throw std::runtime_error(err.str());
            }

            if (id->type == Type::Integer && id->length != 0) {
                std::stringstream err;
                err << curr_line
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            }

            match_token(Token::RParen);
            match_token(Token::Semicolon);
        } else {
            if (g_lex_reg.token == Token::Write) {
                match_token(Token::Write);
            } else {
                match_token(Token::Writeln);
            }

            match_token(Token::LParen);
            Exp(Exp_type, Exp_length);

            bool error = false;
            if (Exp_type == Type::Integer && Exp_length != 0) {
                error = true;
            } else if (Exp_type == Type::Bool) {
                error = true;
            }
           
            if (error) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            }

            while (g_lex_reg.token == Token::Comma) {
                match_token(Token::Comma);
                Exp(Exp1_type, Exp1_length);

                error = false;
                if (Exp1_type == Type::Integer && Exp1_length != 0) {
                    error = true;
                } else if (Exp1_type == Type::Bool) {
                    error = true;
                }
               
                if (error) {
                    std::stringstream err;
                    err << g_source.curr_line
                        << ":tipos incompatíveis.";
                    throw std::runtime_error(err.str());
                }
            }

            match_token(Token::RParen);
            match_token(Token::Semicolon);
        }
    }

    void LC() {
        if (g_lex_reg.token == Token::LBrace) {
            match_token(Token::LBrace);

            while (g_lex_reg.token == Token::Id
                    || g_lex_reg.token == Token::For
                    || g_lex_reg.token == Token::If
                    || g_lex_reg.token == Token::Semicolon
                    || g_lex_reg.token == Token::Readln
                    || g_lex_reg.token == Token::Write
                    || g_lex_reg.token == Token::Writeln)
                C();

            match_token(Token::RBrace);
        } else C();
    }

    void Exp(Type &Exp_type, int &Exp_length) {
        Operator op = Operator::None;

        Type ExpS_type;
        int ExpS_length;
        Type ExpS1_type;
        int ExpS1_length;

        ExpS(ExpS_type, ExpS_length);

        Exp_type = ExpS_type;
        Exp_length = ExpS_length;

        if (g_lex_reg.token == Token::EQ) {
            op = Operator::Eq;
            match_token(Token::EQ);
        } else if (g_lex_reg.token == Token::NE) {
            op = Operator::Eq;
            match_token(Token::NE);
        } else if (g_lex_reg.token == Token::LT){
            op = Operator::Eq;
            match_token(Token::LT);
        } else if (g_lex_reg.token == Token::GT){
            op = Operator::Eq;
            match_token(Token::GT);
        } else if (g_lex_reg.token == Token::LE){
            op = Operator::Eq;
            match_token(Token::LE);
        } else if (g_lex_reg.token == Token::GE){
            op = Operator::Eq;
            match_token(Token::GE);
        }

        if (op != Operator::None) {
            ExpS(ExpS1_type, ExpS1_length);

            bool error = false;
            if (Exp_type == Type::Bool || ExpS1_type == Type::Bool) {
                error = true;
            } else if (Exp_length != 0 || ExpS1_length != 0) {
                if (Exp_type == Type::Integer || ExpS1_type == Type::Integer) {
                    error = true;
                } else if (op != Operator::Eq) {
                    error = true;
                } else if (Exp_length == 0 || ExpS1_length == 0) {
                    error = true;
                }
            } else if (Exp_type != ExpS1_type) {
                error = true;
            }

            if (error) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            }

            Exp_type = Type::Bool;
            Exp_length = 0;
        }
    }

    void ExpS(Type &ExpS_type, int &ExpS_length) {
        int signal = 1;
        Operator op;

        Type T_type;
        int T_length;
        Type T1_type;
        int T1_length;

        if (g_lex_reg.token == Token::Add) {
            match_token(Token::Add);
        } else if (g_lex_reg.token == Token::Sub) {
            signal = -1;
            match_token(Token::Sub);
        }

        T(T_type, T_length);

        ExpS_type = T_type;
        ExpS_length = T_length;

        while (g_lex_reg.token == Token::Add
                || g_lex_reg.token == Token::Sub
                || g_lex_reg.token == Token::Or) {
        
            if (g_lex_reg.token == Token:: Add) {
                op = Operator::Add;
                match_token(Token::Add);
            } else if (g_lex_reg.token == Token:: Sub) {
                op = Operator::Sub;
                match_token(Token::Sub);
            } else {
                op = Operator::Or;
                match_token(Token::Or);
            }
            
            T(T1_type, T1_length);

            bool error = false;
            if (op == Operator::Or) {
                if (ExpS_type != Type::Bool || T1_type != Type::Bool) {

                    error = true;
                }   
            } else if (ExpS_length != 0 || T1_length != 0) {
                error = true;
            } else if (! ((ExpS_type == Type::Integer && 
                            T1_type == Type::Integer) ||
                        (ExpS_type == Type::Char &&
                         T1_type == Type::Char))) {

                error = true;
            }

            if (error) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            }
        } 
    }

    void T(Type &T_type, int &T_length) {
        Operator op;

        Type F_type;
        int F_length;
        Type F1_type;
        int F1_length;

        F(F_type, F_length);
        
        T_type = F_type;
        T_length = F_length;

        while (g_lex_reg.token == Token::Mult 
                || g_lex_reg.token == Token::Div
                || g_lex_reg.token == Token::And
                || g_lex_reg.token == Token::Mod) {

            if (g_lex_reg.token == Token::Mult) {
                op = Operator::Mult;
                match_token(Token::Mult);
            } else if (g_lex_reg.token == Token::Div) {
                op = Operator::Div;
                match_token(Token::Div);
            } else if (g_lex_reg.token == Token::And) {
                op = Operator::And;
                match_token(Token::And);
            } else { 
                op = Operator::Mod;
                match_token(Token::Mod);
            }
            
            F(F1_type, F1_length);

            bool error = false;
            if (op == Operator::And) {
                if (T_type != Type::Bool || F1_type != Type::Bool) {

                    error = true;
                }
            } else if (T_length != 0 || F1_length != 0) {
                error = true;
            } else if (! ((T_type == Type::Integer && 
                            F1_type == Type::Integer) ||
                        (T_type == Type::Char &&
                         F1_type == Type::Char))) {

                error = true;
            }

            if (error) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            }        
        }
    }

    void F(Type &F_type, int &F_length) {
        Type F1_type;
        int F1_length;

        Type Exp_type;
        int Exp_length;

        TSymbolElem* id;

        if (g_lex_reg.token == Token::Not) {
            match_token(Token::Not);
            F(F1_type, F1_length);
        
            if (F1_type != Type::Bool) {
                std::stringstream err;
                err << g_source.curr_line
                    << ":tipos incompatíveis.";
                throw std::runtime_error(err.str());
            } else {
                F_type = F1_type;
                F_length = F1_length;
            }

        } else if (g_lex_reg.token == Token::LParen) {
            match_token(Token::LParen);
            Exp(Exp_type, Exp_length);
            match_token(Token::RParen);
            
            F_type = Exp_type;
            F_length = Exp_length;
        } else if (g_lex_reg.token == Token::Const) {
            F_type = g_lex_reg.type;
            F_length = g_lex_reg.length;

            match_token(Token::Const);
        } else {
            id = g_lex_reg.p_tab_elem;
            int curr_line = g_source.curr_line;
            match_token(Token::Id);

            if (id->cl == Class::Empty) {
                std::stringstream err;
                err << curr_line
                    << ":identificador nao declarado ["
                    << g_lex_reg.lexeme << "].";
                throw std::runtime_error(err.str());
            }

            F_type = id->type;
            F_length = id->length;

            if (g_lex_reg.token == Token::LBracket) {
                match_token(Token::LBracket);
                Exp(Exp_type, Exp_length);
               
                bool error = false;
                if (Exp_type != Type::Integer) {
                    error = true;
                } else if (id->length == 0) {
                    error = true;
                } else {
                    F_length = 0;
                }

                if (error) {
                    std::stringstream err;
                    err << g_source.curr_line
                        << ":tipos incompatíveis.";
                    throw std::runtime_error(err.str());
                }

                match_token(Token::RBracket);
            }
        }
    }
}
