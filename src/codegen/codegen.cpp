/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#include <iostream>
#include <sstream>
#include "codegen/codegen.hpp"

namespace codegen {

    int new_tmp(Type type, int length) {
        int curr_addr = tmp_counter;

        int mult = type == Type::Integer
            ? 2
            : 1;

        int inc = length == 0
            ? mult
            : mult * length;

        tmp_counter += inc;
        return curr_addr;
    }

    void reset_tmp() {
        tmp_counter = 0;
    }

    int new_label() {
        return label_counter++;
    }

    void create_sseg() {
        writeln("sseg SEGMENT STACK\t\t; Início seg. pilha");
        writeln("\tbyte 4000h DUP(?)\t; Dimensiona pilha");
        writeln("sseg ENDS\t\t\t; Fim seg. pilha\n");
    }

    void init_dseg() {
        writeln("dseg SEGMENT PUBLIC\t\t; Início seg. dados");
        writeln("\tbyte 4000h DUP(?)\t; Temporários");
    }

    int put_dseg(Class cl, Type type, int len, int val) {
        std::string decl_type = type == Type::Char 
            ? "byte" 
            : "sword";

        std::string decl_val = val == -1
            ? "?"
            : std::to_string(val);

        std::string decl_tail = len == 0 
            ? decl_val
            : std::to_string(len) + " DUP(?)";

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
            << "\t\t\t"
            << decl_comment
            << " em "
            << dseg_counter;

        // Writing output.
        writeln(decl.str());

        int mult = type == Type::Char ? 1 : 2;
        int nbytes = len == 0
            ? mult
            : len * mult;

        int addr = dseg_counter;
        dseg_counter += nbytes;

        return addr;
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
        writeln("\tmov ah, 4Ch\t\t; Finalização do programa");
        writeln("\tint 21h\t\t\t; Finalização do programa");
        writeln("cseg ENDS\t\t\t; Fim seg. código");
        writeln("END strt\t\t\t; Fim programa");
    }
}
