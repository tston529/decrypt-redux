#include <string>

/// @brief returns if a character is an uppercase or lowercase letter
/// @param c the character to be verified
/// @return true if a character is in [A-Za-z], false otherwise
bool is_letter(const char c) noexcept;

/// @brief returns if a character is a punctuation character
/// @param c the character to be verified
/// @return true if a character is punctuation-adjacent, false otherwise
bool is_punctuation(const char c) noexcept;

/// @brief Removes ending punctuation characters from a string
/// @param word the word to be cleaned
/// @return a copy of the word without trailing punctuation characters
std::string strip_end_punctuation(const std::string& word);