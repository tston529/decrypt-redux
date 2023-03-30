#include <fstream>
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include "helper.hpp"

// example: "stringify" yields "ABCDEFDGH"
std::string patternify_word(const std::string& word)
{
    std::string ss;
    ss.reserve(word.size());

    std::unordered_map<char, char> used_chars{};
    used_chars.reserve(word.size());
    
    int current_replacement_char = 65; // start with capital 'A'
    for (int i = 0; i < word.size(); ++i)
    {
        const char current_char = word[i];
        if (!is_letter(current_char))
        {
            ss += current_char;
            continue;
        }

        const char lowercase_char = tolower(current_char);
        if (const auto x = used_chars.find(lowercase_char); x != used_chars.end())
        {
            ss += x->second;
        }
        else
        {
            ss += static_cast<char>(current_replacement_char);
            used_chars[lowercase_char] = current_replacement_char;
            ++current_replacement_char;
        }
    }

    return ss;
}

auto create_dictionary(const std::string& filename) -> std::unordered_multimap<std::string, std::string> 
{
    std::unordered_multimap<std::string, std::string> dictionary{};

    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string token;
        while (file >> token)
        {
            token = strip_end_punctuation(token);
            dictionary.insert({patternify_word(token), token});
        }
    }

    return dictionary;
}

auto create_dictionary(const std::set<std::string>& dict) -> std::unordered_multimap<std::string, std::string> 
{
    std::unordered_multimap<std::string, std::string> dictionary{};
    for (const auto& token : dict)
    {
        const std::string s = strip_end_punctuation(token);
        dictionary.insert({s, token});
    }

    return dictionary;
}

int rate_guess(const std::set<std::string> dictionary, const std::unordered_map<std::string, std::string>& cipher, const std::unordered_map<char, char>& current_codex)
{

}


int main()
{
    std::set<std::string> dictionary{};

    std::ifstream file("dictionary.txt");
    if (file.is_open())
    {
        std::string token;
        while (file >> token)
        {
            dictionary.insert(token);
        }
    }

    std::cout << dictionary.size() << std::endl;

    // return 0;

    const auto encoded_dictionary = create_dictionary(dictionary);
    std::cout << encoded_dictionary.size() << std::endl;
    /* const auto cipher = create_dictionary("english_cipher.txt");
    std::cout << cipher.size() << std::endl;

    for (auto itr = cipher.begin(); itr != cipher.end(); ++itr)
    {

        // Not final - we're not guaranteed to have any with only a single match between dictionary and cipher
        if (encoded_dictionary.count(itr->first) == 1)
        {
            std::cout << itr->second << " : " << (encoded_dictionary.find(itr->first))->second << std::endl;
        }
        else
        {
            std::cout << itr->second << " : " << encoded_dictionary.count(itr->first) << std::endl;
        }

    } */
}