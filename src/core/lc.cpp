#include <iostream>
#include <string>

#include "lexer/lexer.hpp"

int main(int argc, char *argv[]) {
    int exit_code = EXIT_SUCCESS;

    // RegistroToken: (Lexema, Token, Classe, Tipo, Tamanho);
    std::string input = argv[1];
    std::ifstream source(input);
    int curr_line = 0;

    try {
        lexer::next(source, curr_line);
        
        // Token token = lexer::next();
        // Procedimento simbolo inicial, 
        // Se não EOF: erro;
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }

    source.close();
    return exit_code;
}
