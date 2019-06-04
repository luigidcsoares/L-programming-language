/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#ifndef CODEGEN_CODEGEN_HPP_
#define CODEGEN_CODEGEN_HPP_

#include <string>
#include "codegen/writer.hpp"
#include "core/class.hpp"
#include "core/operator.hpp"
#include "core/type.hpp"

using namespace core;

namespace codegen {
    
    namespace {
        int dseg_counter = 0x4000;
        int tmp_counter = 0;
        int label_counter = 1;
    }

    /**
     * Return the current valid address and increment it.
     */
    int new_tmp(Type type, int length);

    /**
     * Reset tmp counter.
     */
    void reset_tmp();

    /**
     * Return the next label and increment it.
     */
    std::string new_label();

    /**
     * Create the output file.
     *
     * @param string: filename -> output.
     */
    inline void create_ofile(std::string filename) {
        open(filename);
    }

    /**
     * Finish code generation.
     */
    inline void close_ofile() {
        close();
    }

    /**
     * Create stack segment.
     */
    void create_sseg();

    /**
     * Initiate the data segment.
     */
    void init_dseg();

    /**
     * Declare variable or const.
     *
     * @param Class: cl -> class for debug.
     * @param Type: type -> integer, char.
     * @param int: len -> length (0 or vector size).
     * @param int: val -> val (-1 if it wasn't set).
     */
    int put_dseg(Class cl, Type type, int len, int val);

    /**
     * Finish the data segment.
     */
    void end_dseg();

    /**
     * Init code segment.
     */
    void init_cseg();

    /**
     * Finish the code segment.
     */
    void end_cseg();

    /**
     * Code gen for "not" operation.
     * F-> not F1
     */
    int write_not(Type F1_type, int F1_length, int F1_addr);

    /**
     * Code gen for const (string or int/char).
     * F -> const
     */
    int write_const(Type const_type,
            int const_length, 
            std::string const_lex);

    /**
     * Code gen for access to vector element.
     * F -> id '[' Exp ']'
     * 
     * Here we are considering that we entered in the vector access.
     */
    int write_vec(Type id_type, int id_length, 
            int id_addr, int Exp_addr);

    /**
     * Code gen for negate term.
     * ExpS -> - T
     */
    void write_neg_term(int T_addr);

    /**
     * Code gen for term.
     */
    int write_term(Type T_type, Operator op, 
            int T_addr, int F1_addr);

    /**
     * Code gen for ExpS.
     */
    int write_exps(Type ExpS_type, Operator op,
            int ExpS_addr, int T1_addr);

    /**
     * Code gen for Exp.
     */
    int write_exp(Type Exp_type, Operator op,
            int Exp_addr, int ExpS1_addr,
            int Exp_length);

    /**
     * Code gen for assigment.
     */
    void write_assign_id(Type id_type, bool cond, 
            int Exp_addr, int id_addr, int Exp1_addr);
}

#endif
