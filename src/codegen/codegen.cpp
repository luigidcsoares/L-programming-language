/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#include <iostream>
#include <sstream>
#include "codegen/codegen.hpp"

namespace codegen {

    void create_sseg() {
        writeln("sseg SEGMENT STACK\t\t; Início seg. pilha");
        writeln("\tbyte 4000h DUP(?)\t; Dimensiona pilha");
        writeln("sseg ENDS\t\t\t; Fim seg. pilha\n");
    }

    void init_dseg() {
        writeln("dseg SEGMENT PUBLIC\t\t; Início seg. dados");
        writeln("\tbyte 4000h DUP(?)\t; Temporários");
    }

    unsigned int put_dseg(Class cl, Type type, int len, int val) {
        std::string decl_type = type == Type::Char 
            ? "byte" 
            : "sword";

        std::string decl_val = val == -1
            ? "?"
            : std::to_string(val);

        std::string decl_tail = len == 0 
            ? decl_val
            : std::to_string(len) + "DUP(?)";

        std::string comment_type = type == Type::Integer
            ? len == 0 ? "int" : "vec. int"
            : len == 0 ? "char" : "vec. char";

        std::string decl_comment = cl == Class::Var
            ? "; Var. " + comment_type
            : "; Const. " + comment_type;

        std::stringstream decl;
        decl 
            << "\t" 
            << decl_type
            << " "
            << decl_tail
            << "\t\t"
            << decl_comment
            << " em "
            << dseg_counter;

        // Writing output.
        writeln(decl.str());

        int mult = type == Type::Char ? 1 : 2;
        int nbytes = len == 0
            ? mult
            : len * mult;

        int end = dseg_counter;
        dseg_counter += nbytes;

        return end;
    }

    void end_dseg() {
        writeln("dseg ENDS\t\t\t; Fim seg. dados\n");
    }

    void init_cseg() {
        writeln("cseg SEGMENT PUBLIC\t\t; Início seg. código");
        writeln("\tASSUME CS:cseg, DS:dseg");
        writeln("\nstrt:\t\t\t\t; Início do programa");
    }

    void end_cseg() {
        writeln("cseg ENDS\t\t\t; Fim seg. código");
        writeln("END strs\t\t\t; Fim programa");
    }
}
