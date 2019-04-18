#include <iostream>
#include <string>

#include "lexer.hpp"

int main(int argc, char *argv[]) {
    // RegistroToken: (Lexema, Token, Classe, Tipo, Tamanho);
    
    std::string input = argv[1];
    std::ifstream source(input);

    lexer::next(source);

    // Token token = lexer::next();
    // Procedimento simbolo inicial;
    // Se não EOF: erro;
    
    source.close();
}
