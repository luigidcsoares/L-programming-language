/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#include <iostream>
#include "codegen/writer.hpp"

namespace codegen {

    void open(std::string filename) {
        buffer.open(filename);
    }

    void close() {
        buffer.close();
    }

    void writeln(std::string str) {
        if (buffer.is_open()) {
            buffer << str << std::endl;
            buffer.flush();
        }   
    }

}
