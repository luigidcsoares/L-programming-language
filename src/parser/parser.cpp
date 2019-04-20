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
                || g_lex_reg.token == Token::Const)
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

        // Match the current token with the next.
        // The next token is expected to be EOFL.
        match_token(Token::EOFL);
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
        }
    }

    void DV() {
        match_token(Token::Id);
     
        if (g_lex_reg.token == Token::EQ) {
            match_token(Token::EQ);


        }
    }
}
