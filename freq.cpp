#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include "helper.hpp"
#include "setup.hpp"


void decode(const std::vector<std::string>& encoded_word_list, const Cipher& cipher)
{
    for (const char c : cipher.real)
    {
        std::cout << c << ' ';
    }
    std::cout << std::endl;

    for (const char c : cipher.encoding)
    {
        if (c)
        {
            std::cout << c << ' ';
        }
        else
        {
            std::cout << "- ";
        }
    }
    std::cout << std::endl;

    for (const std::string& word : encoded_word_list)
    {
        std::cout << partial_decode_word(word, cipher) << " ";
    }
    std::cout << std::endl;

}

bool attempt_guess(
    const std::set<std::string>& dictionary,
    const std::unordered_multimap<std::string, std::string>& encoded_phrase_map,
    const std::unordered_multimap<std::string, std::string>& encoded_dictionary,
    const std::vector<std::string>& encoded_word_list,
    int amount_words_decoded_previously,
    Cipher mainCipher)
{
    std::stack<std::vector<std::string>> fewest_matches;
    std::stack<std::string> encoded_word_with_fewest_matches;
    int amt_words_fully_decoded = 0;
    for (auto itr = encoded_phrase_map.begin(); itr != encoded_phrase_map.end(); ++itr)
    {
        const std::string encoded_word = partial_decode_word(itr->second, mainCipher);
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

        // decode(encoded_word_list, mainCipher);

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

    // std::cout << amt_words_fully_decoded << std::endl;

    if (amt_words_fully_decoded == encoded_phrase_map.size())
    {
        std::cout << "Decryption complete!" << std::endl;
        decode(encoded_word_list, mainCipher);
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

            Cipher newCipher{mainCipher};        
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

    return attempt_guess(dictionary, encoded_phrase_map, encoded_dictionary, encoded_word_list, amt_words_fully_decoded, mainCipher);
}

int main()
{
    std::set<std::string> dictionary{};

    std::cout << "Creating dictionary..." << std::endl;

    // std::ifstream file("data_files/dictionary.txt");

    // Program is faster and more accurate for this particular ciphered text with english_3000.txt;
    // need to fix the retry logic for cases where all un-decoded words have multiple options
    std::ifstream file("data_files/english_3000.txt");
    if (file.is_open())
    {
        std::string token;
        while (file >> token)
        {
            dictionary.insert(token);
        }
    }
    file.close();

    std::vector<std::string> ciphered_text;
    std::ifstream ciphered_file("data_files/english_cipher_2.txt");
    if (ciphered_file.is_open())
    {
        std::string token;
        while (ciphered_file >> token)
        {
            ciphered_text.push_back(token);
        }
    }
    ciphered_file.close();

    const auto encoded_dictionary = create_dictionary(dictionary);
    const auto encoded_phrase = create_dictionary(ciphered_text);
    
    Cipher mainCipher{};

    attempt_guess(dictionary, encoded_phrase, encoded_dictionary, ciphered_text, 0, mainCipher);
}