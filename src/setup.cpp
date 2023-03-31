#include "helper.hpp"
#include "setup.hpp"
#include <string>
#include <unordered_map>
#include <fstream>
#include <set>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::string patternify_word(const std::string& word)
{
    std::string ss;
    ss.reserve(word.size());

    const std::size_t sz = word.size();
    char used_chars[sz];
    char replacement_chars[sz];
    
    int letters_replaced = 0;
    int base_replacement_char = 65; // start with capital 'A'
    for (int i = 0; i < sz; ++i)
    {
        const char current_char = word[i];
        if (!is_letter(current_char))
        {
            ss += current_char;
            continue;
        }

        const char lowercase_char = tolower(current_char);


        int found_idx;
        bool found = false;
        for (found_idx = 0; found_idx < letters_replaced; ++found_idx)
        {
            if (used_chars[found_idx] == lowercase_char)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            ss += replacement_chars[found_idx];
        }
        else
        {
            const int current_replacement_char = base_replacement_char + letters_replaced;
            ss += static_cast<char>(current_replacement_char);
            used_chars[letters_replaced] = lowercase_char;
            replacement_chars[letters_replaced] = current_replacement_char;
            ++letters_replaced;
        }
    }

    return ss;
}

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
        dictionary.insert({patternify_word(stripped_token), token});
    }

    return dictionary;
}