/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#include <string>
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

    std::string new_label() {
        std::stringstream ss;
        ss << "R" << label_counter;
        label_counter++;
        return ss.str();
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
        writeln("\n\tmov ah, 4Ch\t\t; Finalização do programa");
        writeln("\tint 21h\t\t\t; Finalização do programa");
        writeln("cseg ENDS\t\t\t; Fim seg. código");
        writeln("END strt\t\t\t; Fim programa");
    }

    int write_not(Type F1_type, int F1_length, int F1_addr) {
        int F_addr = new_tmp(F1_type, F1_length);

        writeln("\n\tmov AX, DS:[" + std::to_string(F1_addr) + 
                "] \t\t; Not");
        writeln("\tneg AX");
        writeln("\tadd AX, 1");
        writeln("\tmov DS:[" + std::to_string(F_addr) + "], AX");

        return F_addr;
    }

    int write_const(
            Type const_type,
            int const_length, 
            std::string const_lex
    ) {

        int F_addr;

        if (const_type == Type::String) {
            const_lex = const_lex.substr(1, const_lex.length() - 2);
            writeln("\n\tdseg SEGMENT PUBLIC\t\t; String em " +
                    std::to_string(dseg_counter));
            writeln("\t\tbyte \"" + const_lex + "$\"");
            writeln("\tdseg ENDS");

            F_addr = dseg_counter;
            dseg_counter += const_length + 1;

        } else {
            F_addr = new_tmp(const_type, const_length);

            int val;
            if (const_type == Type::Integer) {
                val = std::stoi(const_lex);
            } else if (const_lex.length() == 4) { // hexadecimal
                val = std::stoi(const_lex, nullptr, 16);
            } else {
                val = const_lex[1];
            }

            writeln("\n\tmov AX, " + std::to_string(val) + 
                    "\t\t\t; Temp. const.: " + const_lex);
            writeln("\tmov DS:[" + std::to_string(F_addr) + "], AX");
        }

        return F_addr;
    }

    int write_vec(
            Type id_type, int id_length, 
            int id_addr, int Exp_addr
    ) {
        int F_addr = new_tmp(id_type, id_length);

        writeln("\n\tmov AX, DS:[" + std::to_string(Exp_addr) + 
                "]\t\t; Acesso a vetor");

        if (id_type == Type::Integer) {
            writeln("\tadd AX, AX");
        }

        writeln("\tadd AX, " + std::to_string(id_addr));
        writeln("\tmov AX, DS:[AX]");
        writeln("\tmov DS:[" + std::to_string(F_addr) + "], AX");

        return F_addr;
    }
}
