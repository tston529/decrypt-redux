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

bool attempt_guess(
    const std::set<std::string>& dictionary,
    const std::unordered_multimap<std::string, std::string>& encoded_phrase,
    const std::unordered_multimap<std::string, std::string>& encoded_dictionary,
    Cipher mainCipher)
{
    std::stack<std::vector<std::string>> fewest_matches;
    std::stack<std::string> encoded_word_with_fewest_matches;
    int amt_words_fully_decoded = 0;
    for (auto itr = encoded_phrase.begin(); itr != encoded_phrase.end(); ++itr)
    {
        const std::string encoded_word = partial_decode_word(itr->second, mainCipher);
        if (to_lower(encoded_word) == encoded_word)
        {
            if (!dictionary.contains(encoded_word))
            {
                std::cout << "encoded word not found: " << encoded_word << std::endl;
                return false;
            }
            ++amt_words_fully_decoded;
        }
        std::cout << encoded_word << std::endl;
        auto partial_matches = find_list_of_partial_matches(encoded_dictionary, encoded_word, mainCipher);
        if (fewest_matches.empty() || partial_matches.size() < fewest_matches.top().size())
        {
            fewest_matches.push(partial_matches);
            partial_matches.shrink_to_fit();
            encoded_word_with_fewest_matches.push(encoded_word);
        }
    }

    if (amt_words_fully_decoded == encoded_phrase.size())
    {
        std::cout << "Yay!" << std::endl;
        return true;
    }

    std::cout << "-------------------" << std::endl;
    for (const auto& val : fewest_matches.top())
    {
        std::cout << val << std::endl;
    }
    std::cout << "-------------------" << std::endl;

    while (!fewest_matches.empty() && !fewest_matches.top().empty())
    {
        // I think I need to hold the ciphers in a stack too and have the attempt_guess in the if.
        // Pop the cipher off the stack if it's a bad attempt
        if (mainCipher.add_word_to_cipher(encoded_word_with_fewest_matches.top(), fewest_matches.top()[0]) == 0)
        {
            fewest_matches.pop();
            encoded_word_with_fewest_matches.pop();
        }
        return attempt_guess(dictionary, encoded_phrase, encoded_dictionary, mainCipher);
    }
    return attempt_guess(dictionary, encoded_phrase, encoded_dictionary, mainCipher);
}


int main()
{
    std::set<std::string> dictionary{};

    std::cout << "Creating dictionary..." << std::endl;

    std::ifstream file("data_files/dictionary.txt");
    if (file.is_open())
    {
        std::string token;
        while (file >> token)
        {
            dictionary.insert(token);
        }
    }

    const auto encoded_dictionary = create_dictionary(dictionary);
    const auto encoded_phrase = create_dictionary("data_files/english_cipher.txt");

    
    Cipher mainCipher{};

    attempt_guess(dictionary, encoded_phrase, encoded_dictionary, mainCipher);
}