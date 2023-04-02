#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stack>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include "helper.hpp"
#include "setup.hpp"

/// @brief      Attempts to determine the best un-decrypted word to use as a key,
///             puts the mapping of that word to its encrypted counterpart in the cipher,
///             and recursively tries to decrypt the whole phrase word-by-word.
/// @param[in]  dictionary                       The dictionary
/// @param[in]  encoded_phrase_map               The encoded phrase map
/// @param[in]  encoded_dictionary               The encoded dictionary
/// @param[in]  encoded_word_list                The encoded word list
/// @param[in]  amount_words_decoded_previously  The amount of words that were decoded previously
/// @param[in]  cipher                       The cipher; passed by value to let the recursive stack fix blunders
/// @return     True if a decoding was successful, False otherwise.
bool attempt_guess(
    const std::set<std::string>& dictionary,
    const std::unordered_multimap<std::string, std::string>& encoded_phrase_map,
    const std::unordered_multimap<std::string, std::string>& encoded_dictionary,
    const std::vector<std::string>& encoded_word_list,
    int amount_words_decoded_previously,
    Cipher cipher)
{
    std::stack<std::vector<std::string>> fewest_matches;
    std::stack<std::string> encoded_word_with_fewest_matches;
    int amt_words_fully_decoded = 0;
    for (auto itr = encoded_phrase_map.begin(); itr != encoded_phrase_map.end(); ++itr)
    {
        const std::string encoded_word = partial_decode_word(itr->second, cipher);
        if (to_lower(encoded_word) == encoded_word)
        {
            if (!dictionary.contains(encoded_word))
            {
                return false;
            }

            // std::cout << " - " << encoded_word << std::endl;

            ++amt_words_fully_decoded;
            continue;
        }

        // decode(encoded_word_list, cipher);

        // std::cout << encoded_word << std::endl;
        auto partial_matches = find_list_of_partial_matches(encoded_dictionary, itr->first, encoded_word);
        if (!partial_matches.empty() && (fewest_matches.empty() || (partial_matches.size() <= fewest_matches.top().size())))
        {

            // std::cout << "Pushing " << encoded_word << " onto stack with " << partial_matches.size() << " partial matches.\n";
            fewest_matches.push(partial_matches);
            partial_matches.shrink_to_fit();
            encoded_word_with_fewest_matches.push(encoded_word);
        }
    }

    if (amount_words_decoded_previously > 0 && amt_words_fully_decoded >= amount_words_decoded_previously)
    {
        printf("%s%i%s", "\33[0FConfidence: ", (int)(100*(float)amt_words_fully_decoded/(float)encoded_phrase_map.size()), "%\n");
        // std::cout << "Confidence: " << (float)amt_words_fully_decoded/(float)encoded_phrase_map.size() << "\33[0G" << std::flush(0);
    }

    if (amt_words_fully_decoded == encoded_phrase_map.size())
    {
        std::cout << "Decryption complete!" << std::endl;
        decode(encoded_word_list, cipher);
        return true;
    }

    if (amt_words_fully_decoded < amount_words_decoded_previously ||
        fewest_matches.empty() ||
        fewest_matches.top().empty())
    {
        return false;
    }

    while (!fewest_matches.empty() && !fewest_matches.top().empty())
    {
        for (int i = 0; i < fewest_matches.top().size(); ++i)
        {

            Cipher newCipher{cipher};        
            if (newCipher.add_word_to_cipher(
                encoded_word_with_fewest_matches.top(), 
                fewest_matches.top()[i]) != 1)
            {
                continue;
            }

            if (attempt_guess(dictionary, encoded_phrase_map, encoded_dictionary, encoded_word_list, amt_words_fully_decoded, newCipher))
            {
                return true;
            }
        }
        fewest_matches.pop();
        encoded_word_with_fewest_matches.pop();
    }

    return attempt_guess(dictionary, encoded_phrase_map, encoded_dictionary, encoded_word_list, amt_words_fully_decoded, cipher);
}

int main()
{
    std::set<std::string> dictionary{};

    std::cout << "Creating dictionary...";

    // // slow to read, slow to extract, gargantuan amount of words, will have tons of false positives
    // std::ifstream file("data_files/dictionary.txt");
    // 
    // // fast to read, fast to extract, fewest words so it will miss a lot
    // std::ifstream file("data_files/english_3000.txt");

    // TODO: need to fix the retry logic for cases where all un-decoded words have multiple options
    std::ifstream file("data_files/eng.txt");
    if (file.is_open())
    {
        std::string token;
        while (file >> token)
        {
            dictionary.insert(token);
        }
    }
    file.close();
    const auto encoded_dictionary = create_dictionary(dictionary);
    std::cout << " Done!\n" << std::endl;

    std::cout << "Reading ciphered text...";
    std::vector<std::string> ciphered_text;
    std::ifstream ciphered_file("data_files/english_cipher.txt");
    if (ciphered_file.is_open())
    {
        std::string token;
        while (ciphered_file >> token)
        {
            ciphered_text.push_back(token);
        }
    }
    std::cout << std::endl;
    ciphered_file.close();

    const auto encoded_phrase = create_dictionary(ciphered_text);
    std::cout << " Done!\n" << std::endl;
    for (const auto& token : ciphered_text)
    {
        std::cout << token << " ";
    }
    std::cout << '\n';
    
    std::cout << "Starting decryption!\nConfidence: 0%" << std::endl;
    Cipher mainCipher{};
    attempt_guess(dictionary, encoded_phrase, encoded_dictionary, ciphered_text, 0, mainCipher);
}