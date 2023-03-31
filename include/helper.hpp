#include <string>

/// @brief returns if a character is an uppercase or lowercase letter
/// @param c the character to be verified
/// @return true if a character is in [A-Za-z], false otherwise
bool is_letter(const char c) noexcept
{
    return (c > 64 && c < 91) || (c > 96 && c < 123);
}

/// @brief returns if a character is a punctuation character
/// @param c the character to be verified
/// @return true if a character is punctuation-adjacent, false otherwise
bool is_punctuation(const char c) noexcept
{
    return (c > 31 && c < 48) || (c > 57 && c < 65);
}

/// @brief Removes ending punctuation characters from a string
/// @param word the word to be cleaned
/// @return a copy of the word without trailing punctuation characters
std::string strip_end_punctuation(const std::string& word)
{
    int count = 0;
    while (is_punctuation(word[word.length()-(1+count)]))
    {
        ++count;
    }

    return word.substr(0, word.length()-count);
}