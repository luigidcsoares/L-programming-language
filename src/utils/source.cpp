#include "utils/source.hpp"

namespace utils {
    Source::Source(std::string file_path) {
        curr_line = 1;
        file.open(file_path);
    }
}
