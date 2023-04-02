#include <cctype>
#include <string>
#include <unordered_map>
#include <vector>

/// @brief      Holds a mapping of alphabet characters to their potential ciphered encoding counterparts.
struct Cipher
{
    const char real[26]{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char encoding[26]{};

    /// @brief      Gets the decrypted character for the given ciphered character.
    /// @param[in]  encoded  The encoded character
    /// @return     The decrypted character
    [[nodiscard]] const char getReal(const char encoded) const noexcept
    {
        return real[tolower(encoded)-97];
    }

    /// @brief      Gets the ciphered character for the given "real" character.
    /// @param[in]  real  The real character
    /// @return     The encoded character
    [[nodiscard]] const char getEncoded(const char real) const noexcept
    {
        return encoding[tolower(real)-97];
    }


    ///@brief      Adds letters to the cipher based on a partially decoded word and a real word
    ///@param[in]  partially_decoded_word  The partially decoded word
    ///@param[in]  real_word               The real word
    ///@return     -1 if the words are mismatched
    ///             1 ("true") if we successfully added new letters
    ///             0 ("false") if no new letters were added
    int add_word_to_cipher(const std::string& partially_decoded_word, const std::string& real_word)
    {
        if (partially_decoded_word.size() != real_word.size())
        {
            return -1;
        }

        int amt_new_chars_decoded = 0;
        for (int i = 0; i < real_word.size(); ++i)
        {
            // Ignore:
            // - lowercase letters: a lowercase letter was already decoded, meaning a 1:1
            //   match exists in the cipher
            // - if we already have a 1:1 match for the word, don't overwrite it. Let the 
            //   recursion stack handle that.
            if (std::islower(partially_decoded_word[i]) || getEncoded(real_word[i]))
            {
                continue;
            }

            int idx = tolower(real_word[i])-97;
            encoding[idx] = tolower(partially_decoded_word[i]);
            ++amt_new_chars_decoded;
        }

        return amt_new_chars_decoded != 0;
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

///@brief      Converts a string to uppercase
///@param[in]  s     the string to be converted
///@return     a copy of the given string, converted to uppercase
std::string to_upper(std::string s);

///@brief      Converts a string to lowercase
///@param[in]  s     the string to be converted
///@return     a copy of the given string, converted to lowercase
std::string to_lower(std::string s);

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

/// @brief Creates a list of words that might be matches to the given word based on the current cipher.
/// @param dictionary The collection of patternified words to their real word counterparts
/// @param encrypted_word The word we want to find potential matches for
/// @param current_cipher The current state of the cipher for decryption
/// @return The list of potential matches
std::vector<std::string> find_list_of_partial_matches(
    const std::unordered_multimap<std::string, std::string> dictionary,
    const std::string& encrypted_word,
    const Cipher& current_cipher);

/// @brief Creates a list of words that might be matches to the given wordbased on the current cipher.
/// @param[in]  dictionary                The collection of patternified words to their real word counterparts
/// @param[in]  patternified_word         The patternified word for which to search for potential matches
/// @param[in]  partially_decrypted_word  The partially decrypted word
/// @return The list of potential matches
std::vector<std::string> find_list_of_partial_matches(
    const std::unordered_multimap<std::string, std::string> dictionary,
    const std::string& patternified_word,
    const std::string& partially_decrypted_word);