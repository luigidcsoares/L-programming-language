#ifndef UTILS_REGEX_HPP_
#define UTILS_REGEX_HPP_

namespace utils::regex {
    /**
     * Return whether the character is a letter or not.
     * A letter is defined as [a-zA-Z].
     *
     * @param char c.
     *
     * @return bool.
     */
    bool is_letter(char c);

    /**
     * Return whether the character is a digit or not.
     * A digit is defined as [0-9].
     *
     * @param char c.
     *
     * @return bool.
     */
    bool is_digit(char c);

    /**
     * Return whether the character is a digit excluding zero or not.
     * A digit (without zero )is defined as [1-9].
     *
     * @param char c.
     *
     * @return bool.
     */
    bool is_digit_not_zero(char c);

    /**
     * Return whether the character is hexadecimal or not.
     * Hexadecimal value is defined as [0-9a-fA-F].
     *
     * @param char c.
     *
     * @return bool.
     */
    bool is_hexa(char c);

    /**
     * Return whether the character is a unit symbol or not.
     * A unit symbol is a token which it lexeme's length is one.
     * A unit symbol is defined as (,|%|\\+|-|\\*|=|\\[|\\]|\\(|\\)|\\{|\\}|;)
     * @param char c.
     *
     * @return bool.
     */
    bool is_unit_symbol(char c);

    /**
     * Return whether the character is a valid char or not.
     * A valid char is the combination of the above symbols plus (whitespace
     * |&|_|\"|'|\\/|\\^|@|!|\\?|<|>|=|$), where whitespace is defined as a
     * single whitespace or a (piece of) breakline.
     *
     * @param char c.
     *
     * @return bool.
     */
    bool is_valid_char(char c);

    /**
     * Return whether the character is a whitespace or not, where whitespace is
     * defined as a single whitespace or a (piece of) breakline.
     *
     * @param char c.
     *
     * @return bool.
     */
    bool is_whitespace(char c);
}

#endif
