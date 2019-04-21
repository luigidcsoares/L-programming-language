/**
 * @author: gabriel luciano
 * @author: geovane fonseca
 * @author: luigi domenico
 */

#include <sstream>
#include "core/global.hpp"
#include "core/token.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

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
        // While token belongs to First of {D},
        // call D.
        while (g_lex_reg.token == Token::Var
                || g_lex_reg.token == Token::ConstKW)
            D();

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
    }

    void D() {
        if (g_lex_reg.token == Token::Var) {
            match_token(Token::Var);

            // Repeat until token isn't integer nor char.
            do {
                if (g_lex_reg.token == Token::Integer) 
                    match_token(Token::Integer);
                else match_token(Token::Char);

                DV();
                match_token(Token::Semicolon);

            } while (g_lex_reg.token == Token::Integer
                    || g_lex_reg.token == Token::Char);

        } else {
            match_token(Token::ConstKW);
            match_token(Token::Id);
            match_token(Token::EQ);
            
            if (g_lex_reg.token == Token::Add) 
                match_token(Token::Add);
            else if (g_lex_reg.token == Token::Sub)
                match_token(Token::Sub);

            match_token(Token::Const);
            match_token(Token::Semicolon);
        }
    }

    void DV() {
        match_token(Token::Id);
        DVO();

        while (g_lex_reg.token == Token::Comma) {
            match_token(Token::Comma);
            match_token(Token::Id);
            DVO();
        }
    }
    
    void DVO() {
        if (g_lex_reg.token == Token::EQ) {
            match_token(Token::EQ);

            if (g_lex_reg.token == Token::Add)
                match_token(Token::Add);
            else if (g_lex_reg.token == Token::Sub)
                match_token(Token::Sub);

            match_token(Token::Const);
        } else if (g_lex_reg.token == Token::LBracket) {
            match_token(Token::LBracket);
            match_token(Token::Const);
            match_token(Token::RBracket);
        }
    }

    void C() {
        if (g_lex_reg.token == Token::Id) {
            match_token(Token::Id);

            if (g_lex_reg.token == Token::RBracket) {
                match_token(Token::RBracket);
                Exp();
                match_token(Token::LBracket);
            }

            match_token(Token::EQ);
            Exp();
            match_token(Token::Semicolon);
        } else if (g_lex_reg.token == Token::For) {
            match_token(Token::For);
            match_token(Token::Id);
            match_token(Token::EQ);
            Exp();
            match_token(Token::To);
            Exp();

            if (g_lex_reg.token == Token::Step) {
                match_token(Token::Step);
                match_token(Token::Const);
            }

            match_token(Token::Do);
            LC();
        } else if (g_lex_reg.token == Token::If) {
            match_token(Token::If);
            Exp();
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
            match_token(Token::Id);
            match_token(Token::RParen);
            match_token(Token::Semicolon);
        } else {
            if (g_lex_reg.token == Token::Write)
                match_token(Token::Write);
            else match_token(Token::Writeln);

            match_token(Token::LParen);

            Exp();
            while (g_lex_reg.token == Token::Comma) {
                match_token(Token::Comma);
                Exp();
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

    void Exp() {
        ExpS();

        if (g_lex_reg.token == Token::EQ) {
            match_token(Token::EQ);
            ExpS();
        } else if (g_lex_reg.token == Token::NE) {
            match_token(Token::NE);
            ExpS();
        } else if (g_lex_reg.token == Token::LT){
            match_token(Token::LT);
            ExpS();
        } else if (g_lex_reg.token == Token::GT){
            match_token(Token::GT);
            ExpS();
        } else if (g_lex_reg.token == Token::LE){
            match_token(Token::LE);
            ExpS();
        } else if (g_lex_reg.token == Token::GE){
            match_token(Token::GE);
            ExpS();
        }       
    }

    void ExpS() {
        if (g_lex_reg.token == Token::Add) match_token(Token::Add);
        else if (g_lex_reg.token == Token::Sub) match_token(Token::Sub);

        T();
        while (g_lex_reg.token == Token::Add
                || g_lex_reg.token == Token::Sub
                || g_lex_reg.token == Token::Or) {
        
            if (g_lex_reg.token == Token:: Add) match_token(Token::Add);
            else if (g_lex_reg.token == Token:: Sub) match_token(Token::Sub);
            else match_token(Token::Or);
            
            T();
        } 
    }

    void T() {
        F();
        
        while (g_lex_reg.token == Token::Mult 
                || g_lex_reg.token == Token::Div
                || g_lex_reg.token == Token::And
                || g_lex_reg.token == Token::Mod) {

            if (g_lex_reg.token == Token::Mult) match_token(Token::Mult);
            else if (g_lex_reg.token == Token::Div) match_token(Token::Div);
            else if (g_lex_reg.token == Token::And) match_token(Token::And);
            else match_token(Token::Mod);
            
            F();
        }
    }

    void F() {
        if (g_lex_reg.token == Token::Not) {
            match_token(Token::Not);
            F();
        } else if (g_lex_reg.token == Token::LParen) {
            match_token(Token::LParen);
            Exp();
            match_token(Token::RParen);
        } else if (g_lex_reg.token == Token::Const) {
            match_token(Token::Const);
        } else {
            match_token(Token::Id);
            if (g_lex_reg.token == Token::LBracket) {
                match_token(Token::LBracket);
                Exp();
                match_token(Token::RBracket);
            }
        }
    }
}
