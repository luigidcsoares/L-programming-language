/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#ifndef CODEGEN_WRITER_HPP_
#define CODEGEN_WRITER_HPP_

#include <fstream>
#include <string>

namespace codegen {

    namespace {
        std::ofstream buffer;
    }

    /**
     * Initialize writer with filename.
     *
     * @param std::string: filename -> output filename.
     */
    void open(std::string filename);

    /**
     * Close current opened file.
     */
    void close();

    /**
     * Write in the buffer and flush it.
     */
    void writeln(std::string str);
}

#endif
