/**
 *  @author: Gabriel Luciano 
 *  @author: Geovane Fonseca 
 *  @author: Luigi Domenico
 */ 

#include <regex>
#include <string>

#include "utils/regex.hpp"

namespace utils {
    
    // Anonymous namespace for private members.
    namespace {
        std::string letter_str = "[a-zA-Z]";
        std::regex letter(letter_str);

        std::string digit_str = "[0-9]";
        std::regex digit(digit_str);

        std::regex digit_not_zero("[1-9]");
        std::regex hexa("[0-9a-fA-F]");

        std::string
            unit_symbol_str(",|%|\\+|-|\\*|=|\\[|\\]|\\(|\\)|\\{|\\}|;|_|\\.");
        std::regex unit_symbol(unit_symbol_str);

        std::string whitespace_str = " |\t|\r|\n";
        std::regex whitespace(whitespace_str);

        std::string valid_char_str
            = letter_str
            + '|' 
            + digit_str
            + '|'
            + unit_symbol_str
            + "|"
            + whitespace_str
            + "|&|_|:|\"|'|\\/|\\^|@|!|\\?|<|>|=|\\$";
        std::regex valid_char(valid_char_str);
    }

    bool is_letter(char c) {
        // Convert to string to use within regex_match.
        std::string str(1, c);
        return std::regex_match(str, letter);
    }

    bool is_digit(char c) {
        // Convert to string to use within regex_match.
        std::string str(1, c);
        return std::regex_match(str, digit);
    }

    bool is_digit_not_zero(char c) {
        // Convert to string to use within regex_match.
        std::string str(1, c);
        return std::regex_match(str, digit_not_zero);
    }

    bool is_hexa(char c) {
        // Convert to string to use within regex_match.
        std::string str(1, c);
        return std::regex_match(str, hexa);
    }

    bool is_unit_symbol(char c) {
        // Convert to string to use within regex_match.
        std::string str(1, c);
        return std::regex_match(str, unit_symbol);
    }

    bool is_valid_char(char c) {
        // Convert to string to use within regex_match.
        std::string str(1, c);
        return std::regex_match(str, valid_char);
    }

    bool is_whitespace(char c) {
        // Convert to string to use within regex_match.
        std::string str(1, c);
        return std::regex_match(str, whitespace);
    }
}
