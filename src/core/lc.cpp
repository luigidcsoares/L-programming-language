#include <iostream>
#include <string>

#include "lexer/lexer.hpp"
#include "utils/source.hpp"
#include "core/lc.hpp"

using namespace utils::source;
using namespace core::lc;

int main(int argc, char *argv[]) {
    int exit_code = EXIT_SUCCESS;

    // RegistroToken: (Lexema, Token, Classe, Tipo, Tamanho);
    std::string input = argv[1];
    Source source(input);
  
    // Declaring global token register.
    // This should only be declared here.
    TokenReg token_reg;

    // !!!!!!!!!!! EXEMPLO !!!!!!!!!!!!
    token_reg.token = Token::Comma;
    
    try {
        lexer::next(source);
        
        // Token token = lexer::next();
        // Procedimento simbolo inicial, 
        // Se não EOF: erro;
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }

    source.file.close();
    return exit_code;
}
