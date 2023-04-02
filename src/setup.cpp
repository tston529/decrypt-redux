#include "helper.hpp"
#include "setup.hpp"
#include <string>
#include <unordered_map>
#include <fstream>
#include <set>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
auto create_dictionary(const std::string& filename) -> std::unordered_multimap<std::string, std::string> 
{
    std::unordered_multimap<std::string, std::string> dictionary{};

    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string token;
        while (file >> token)
        {
            const std::string stripped_token = strip_end_punctuation(token);
            dictionary.insert({patternify_word(stripped_token), stripped_token});
        }
    }

    return dictionary;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
auto create_dictionary(const std::set<std::string>& dict) -> std::unordered_multimap<std::string, std::string> 
{
    std::unordered_multimap<std::string, std::string> dictionary{};
    for (const auto& token : dict)
    {
        const std::string stripped_token = strip_end_punctuation(token);
        dictionary.insert({patternify_word(stripped_token), stripped_token});
    }

    return dictionary;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
auto create_dictionary(const std::vector<std::string>& word_list) -> std::unordered_multimap<std::string, std::string> 
{
    std::unordered_multimap<std::string, std::string> dictionary{};
    for (const auto& token : word_list)
    {
        const std::string stripped_token = strip_end_punctuation(token);
        if (dictionary.contains(stripped_token))
        {
            continue;
        }
        dictionary.insert({patternify_word(stripped_token), stripped_token});
    }

    return dictionary;
}