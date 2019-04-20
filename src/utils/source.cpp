/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#include "utils/source.hpp"

namespace utils {
    /**
     * Source.hpp implementation
     */ 
    Source::Source(std::string file_path) {
        curr_line = 1;
        file.open(file_path);
    }
}
