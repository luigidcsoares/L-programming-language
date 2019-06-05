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
        writeln("\tmov AX, dseg");
        writeln("\tmov DS, AX");
    }

    void end_cseg() {
        writeln("\n\tmov ah, 4Ch\t\t; Finalização do programa");
        writeln("\tint 21h\t\t\t; Finalização do programa");
        writeln("cseg ENDS\t\t\t; Fim seg. código");
        writeln("END strt\t\t\t; Fim programa");
    }

    int write_not(Type F1_type, int F1_length, int F1_addr) {
        int F_addr = new_tmp(F1_type, F1_length);

        writeln("\t; ============ Op. NOT ===========");
        writeln("\n\tmov AX, DS:[" + std::to_string(F1_addr) + 
                "]");
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
            writeln("\n\t; ============ Decl. de String ===========");
            writeln("\tdseg SEGMENT PUBLIC\t\t; String em " +
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

            writeln("\n\t; ============ Temp. Const. (" +
                    const_lex + ") ===========");

            std::string reg = const_type == Type::Integer
                ? "AX"
                : "AL";

            writeln("\tmov " + reg + ", " + std::to_string(val));
            writeln("\tmov DS:[" + std::to_string(F_addr) + "], " +
                    reg);
        }

        return F_addr;
    }

    int write_vec(
            Type id_type, int id_length, 
            int id_addr, int Exp_addr
    ) {
        int F_addr = new_tmp(id_type, id_length);

        writeln("\n\t; ============ Acesso a vetor ===========");
        writeln("\tmov DI, DS:[" + std::to_string(Exp_addr) + "]");

        if (id_type == Type::Integer) {
            writeln("\tadd DI, DI");
        }

        writeln("\tadd DI, " + std::to_string(id_addr));
        writeln("\tmov AX, DS:[DI]");
        writeln("\tmov DS:[" + std::to_string(F_addr) + "], AX");

        return F_addr;
    }

    void write_neg_term(int T_addr) {
        writeln("\n\t; ============ Neg. Termo ===========");
        writeln("\tmov AX, DS:[" + std::to_string(T_addr) +
                "]");
        writeln("\tneg AX");
        writeln("\tmov DS:[" + std::to_string(T_addr) + "], AX");
    }

    int write_term(
            Type T_type, Operator op, 
            int T_addr, int F1_addr
    ) {
        writeln("\n\t; ============ Op. Termo ===========");
        writeln("\tmov AX, DS:[" + std::to_string(T_addr) + "]");
        writeln("\tmov BX, DS:[" + std::to_string(F1_addr) + "]");

        if (T_type != Type::Integer) {
            writeln("\tmov AH, 0");
            writeln("\tmov BH, 0");
        }

        if (op == Operator::Mult || op == Operator::And) {
            writeln("\timul BX");
        } else {
            if (T_type == Type::Integer) {
                writeln("\tcwd");
            }

            writeln("\tidiv BX");

            if (op == Operator::Mod) {
                writeln("\tmov AX, DX");
            }
        }

        T_addr = new_tmp(T_type, 0);

        if (T_type == Type::Integer) {
            writeln("\tmov DS:[" + std::to_string(T_addr) +
                    "], AX");
        } else {
            writeln("\tmov DS:[" + std::to_string(T_addr) +
                    "], AL");
        }

        return T_addr;
    }

    int write_exps(
            Type ExpS_type, Operator op,
            int ExpS_addr, int T1_addr
    ) {
        writeln("\n\t; ============ Op. ExpS ===========");
        writeln("\tmov AX, DS:[" + std::to_string(ExpS_addr) + "]");
        writeln("\tmov BX, DS:[" + std::to_string(T1_addr) + "]");

        if (ExpS_type != Type::Integer) {
            writeln("\tmov AH, 0");
            writeln("\tmov BH, 0");
        }

        if (op == Operator::Add) {
            writeln("\tadd AX, BX");
        } else if (op == Operator::Sub){
            writeln("\tsub AX, BX");
        } else {
            writeln("\tmov CX, AX");
            writeln("\tadd CX, BX");
            writeln("\timul BX");
            writeln("\tsub CX, AX");
            writeln("\tmov AX, CX");
        }

        ExpS_addr = new_tmp(ExpS_type, 0);

        if (ExpS_type == Type::Integer) {
            writeln("\tmov DS:[" + std::to_string(ExpS_addr) +
                    "], AX");
        } else {
            writeln("\tmov DS:[" + std::to_string(ExpS_addr) +
                    "], AL");
        }

        return ExpS_addr;
    }

    int write_exp(
            Type Exp_type, Operator op,
            int Exp_addr, int ExpS1_addr,
            int Exp_length, int ExpS1_length
    ) {
        writeln("\n\t; ============ Op. Exp ===========");
        // First we're doing non-vector comp.
        if (Exp_length == 0) {
            std::string label_true;
            std::string label_end;

            writeln("\tmov AX, DS:[" + std::to_string(Exp_addr) + 
                    "]");
            writeln("\tmov BX, DS:[" + std::to_string(ExpS1_addr) +
                    "]");

            if (Exp_type != Type::Integer) {
                writeln("\tmov AH, 0");
                writeln("\tmov BH, 0");
            }

            writeln("\tcmp AX, BX");
            label_true = new_label();
            std::string cmp = op == Operator::Eq ? "je "
                : op == Operator::Neq ? "jne "
                : op == Operator::Lt ? "jl "
                : op == Operator::Gt ? "jg "
                : op == Operator::Lte ? "jle "
                : "jge ";
            cmp += label_true;

            writeln("\t" + cmp);
            writeln("\tmov AL, 0");

            label_end = new_label();
            writeln("\tjmp " + label_end);

            writeln(label_true + ":");
            writeln("\tmov AL, 1");

            writeln(label_end + ":");
            Exp_addr = new_tmp(Exp_type, 0);
            writeln("\tmov DS:[" + std::to_string(Exp_addr) +
                    "], AL");
        }

        // Comparing vector of char/string.
        else {
            writeln("\tmov AX, " + std::to_string(Exp_length));
            writeln("\tmov BX, " + std::to_string(ExpS1_length));
            writeln("\tcmp AX, BX");

            std::string label_false = new_label();
            writeln("\tjne " + label_false);

            writeln("\tmov DI, " + std::to_string(Exp_addr));
            writeln("\tmov SI, " + std::to_string(ExpS1_addr));
            writeln("\tadd AX, DI");
            writeln("\tmov BH, 0");
            writeln("\tmov CH, 0");

            std::string label_init = new_label();
            std::string label_true = new_label();
            writeln(label_init + ":");

            writeln("\tcmp DI, AX");
            writeln("\tje " + label_true);

            writeln("\tmov BL, DS:[DI]");
            writeln("\tmov CL, DS:[SI]");
            writeln("\tcmp BX, CX");
            writeln("\tjne " + label_false);

            writeln("\tadd DI, 1");
            writeln("\tadd SI, 1");
            writeln("\tjmp " + label_init);

            writeln(label_true + ":");
            writeln("\tmov AL, 1");

            std::string label_end = new_label();
            writeln("\tjmp " + label_end);

            writeln(label_false + ":");
            writeln("\tmov AL, 0");

            writeln(label_end + ":");

            Exp_addr = new_tmp(Exp_type, Exp_length);
            writeln("\tmov DS:[" + std::to_string(Exp_addr) + 
                    "], AL");
        }

        return Exp_addr;
    }       

    void write_assign_id(
            Type id_type, bool cond, 
            int Exp_addr, int id_addr,
            int Exp1_addr
    ) {
        std::string reg = id_type == Type::Integer
            ? "AX"
            : "AL";

        writeln("\n\t; ============ Atrib. id ===========");
        writeln("\tmov " + reg + 
                ", DS:[" + std::to_string(Exp1_addr) + "]");

        if (cond) {
            writeln("\tmov DI, DS:[" + std::to_string(Exp_addr) +
                    "]");

            if (id_type == Type::Integer) {
                writeln("\tadd DI, DI");
            }

            writeln("\tadd DI, " + std::to_string(id_addr));
            writeln("\tmov DS:[DI], " + reg);
        } else {
            writeln("\tmov DS:[" + std::to_string(id_addr) +
                    "], " + reg);
        }
    }

    std::string write_if(int Exp_addr) {
        writeln("\n\t; ============ If ===========");

        std::string label_false = new_label();
        writeln("\tmov AX, DS:[" + std::to_string(Exp_addr) +
                "]");
        writeln("\tmov AH, 0");
        writeln("\tcmp AX, 0");
        writeln("\tje " + label_false);

        return label_false;
    }

    std::string write_else(std::string label_false) {
        std::string label_end = new_label();
        writeln("\n\t; ============ Else ===========");
        writeln("\tjmp " + label_end);
        writeln(label_false + ":");

        return label_end;
    }

    void write_end_if(std::string label_false) {
        writeln("\n\t; ============ If sem Else ===========");
        writeln(label_false + ":");
    }

    void write_end_else(std::string label_end) {
        writeln("\n\t; ============ If com Else ===========");
        writeln(label_end + ":");
    }

    std::string write_init_for(int Exp_addr, int id_addr) {
        writeln("\n\t; ============ Inicio For ===========");
        writeln("\tmov AX, DS:[" + std::to_string(Exp_addr) + "]");
        writeln("\tmov DS:[" + std::to_string(id_addr) + "], AX");

        std::string label_init = new_label();
        writeln(label_init + ":");

        return label_init;
    }

    std::string write_test_for(int Exp1_addr, int id_addr) {
        writeln("\n\t; ============ Teste For ===========");
        writeln("\tmov AX, DS:[" + std::to_string(id_addr) + "]");
        writeln("\tmov BX, DS:[" + std::to_string(Exp1_addr) + "]");
        writeln("\tcmp AX, BX");

        std::string label_end = new_label();
        writeln("\tjg " + label_end);

        return label_end;
    }

    void write_end_for(
            int id_addr, std::string step,
            std::string label_init, std::string label_end
    ) {
        writeln("\n\t; ============ Fim For ===========");
        writeln("\tmov AX, DS:[" + std::to_string(id_addr) + "]");
        writeln("\tmov BX, " + step);
        writeln("\tadd AX, BX");
        writeln("\tmov DS:[" + std::to_string(id_addr) + "], AX");
        writeln("\tjmp " + label_init);
        writeln(label_end + ":");
    }
}
