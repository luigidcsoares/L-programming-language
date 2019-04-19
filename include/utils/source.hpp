#ifndef UTILS_SOURCE_HPP_
#define UTILS_SOURCE_HPP_

#include <string>
#include <fstream>

namespace utils {
    struct Source {
        std::ifstream file;
        int curr_line;

        Source(std::string file_path);
    };
}

#endif
