#include "utils/source.hpp"

namespace utils::source {
    Source::Source(std::string file_path) {
        curr_line = 0;
        file.open(file_path);
    }
}