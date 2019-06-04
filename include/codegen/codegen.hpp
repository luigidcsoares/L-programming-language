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
#include "core/type.hpp"

using namespace core;

namespace codegen {
    
    namespace {
        int dseg_counter = 0x4000;
        int tmp_counter = 0;
        int label_counter = 0;
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
    int new_label();

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
}

#endif
