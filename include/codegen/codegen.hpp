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
        unsigned int dseg_counter = 0x4000;
        unsigned int tmp_counter = 0x0;
    }

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
     * @param int: val -> val (-1 if wasn't setted yet).
     */
    unsigned int put_dseg(Class cl, Type type, int len, int val);

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
