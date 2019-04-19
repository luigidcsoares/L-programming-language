#include <iostream>
#include <string>

#include "lexer/lexer.hpp"
#include "utils/source.hpp"
#include "core/global.hpp"

using namespace utils::source;
using namespace core::global;

int main(int argc, char *argv[]) {
    int exit_code = EXIT_SUCCESS;

    // RegistroToken: (Lexema, Token, Classe, Tipo, Tamanho);
    std::string input = argv[1];
    Source source(input);
    
    try {
        while (source.file.peek() != EOF)
            lexer::next(source);
        
        // Procedimento simbolo inicial, 
        // Se não EOF: erro;
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }

    source.file.close();
    return exit_code;
}
