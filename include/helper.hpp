#include <cctype>
#include <string>
#include <unordered_map>
#include <vector>

struct Cipher
{
    const char real[26]{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char encoding[26]{};

public:
    [[nodiscard]] const char getReal(const char encoded) const noexcept
    {
        return real[tolower(encoded)-97];
    }

    [[nodiscard]] const char getEncoded(const char real) const noexcept
    {
        return encoding[tolower(real)-97];
    }
};

/// @brief returns if a character is an uppercase or lowercase letter
/// @param c the character to be verified
/// @return true if a character is in [A-Za-z], false otherwise
bool is_letter(const char c) noexcept;

/// @brief returns if a character is a punctuation character
/// @param c the character to be verified
/// @return true if a character is punctuation-adjacent, false otherwise
bool is_punctuation(const char c) noexcept;

/// @brief Creates a pattern based on letter frequency
///        example: "stringify" yields "ABCDEFDGH"
/// @param word the word to follow the pattern
/// @return the word in the form of the pattern
std::string patternify_word(const std::string& word);

/// @brief Removes ending punctuation characters from a string
/// @param word the word to be cleaned
/// @return a copy of the word without trailing punctuation characters
std::string strip_end_punctuation(const std::string& word);

/// @brief Any characters with 1:1 encodings in the cipher will be replaced in the given word.
/// @param word The word to be decoded
/// @param current_cipher the cipher to use to decode the word
/// @return The partially decoded word
std::string partial_decode_word(std::string word, const Cipher& current_cipher);

/// @brief Creates a list of words that might be matches to the given word
///        based on the current cipher.
/// @param dictionary The collection of patternified words to their real word counterparts
/// @param encrypted_word The word we want to find potential matches for
/// @param urrent_cipher The current state of the cipher for decryption
/// @return The list of potential matches
std::vector<std::string> find_list_of_partial_matches(
    const std::unordered_multimap<std::string, std::string> dictionary,
    const std::string& encrypted_word,
    const Cipher& current_cipher);