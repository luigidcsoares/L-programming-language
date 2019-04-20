/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#ifndef UTILS_SOURCE_HPP_
#define UTILS_SOURCE_HPP_

#include <string>
#include <fstream>

namespace utils {
    /**
     * Link source code to its current line number.
     */ 
    struct Source {
        std::ifstream file;
        int curr_line;

        /**
         * Constructor
         * @param: string, file_path -> source code file path.
         */
        Source(std::string file_path);
    };
}

#endif
