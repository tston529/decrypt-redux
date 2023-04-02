#include "helper.hpp"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <algorithm>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool is_letter(const char c) noexcept
{
    return (c > 64 && c < 91) || (c > 96 && c < 123);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool is_punctuation(const char c) noexcept
{
    return (c > 31 && c < 48) || (c > 57 && c < 65);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::string to_lower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), 
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::string to_upper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), 
                   [](unsigned char c){ return std::toupper(c); });
    return s;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::string strip_end_punctuation(const std::string& word)
{
    int count = 0;
    while (is_punctuation(word[word.length()-(1+count)]))
    {
        ++count;
    }

    return word.substr(0, word.length()-count);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void decode(const std::vector<std::string>& encoded_word_list, const Cipher& cipher)
{
    for (const char c : cipher.real)
    {
        std::cout << c << ' ';
    }
    std::cout << '\n';

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
    std::cout << '\n';

    for (const std::string& word : encoded_word_list)
    {
        std::cout << partial_decode_word(word, cipher) << " ";
    }
    std::cout << std::endl;

}

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
std::string partial_decode_word(std::string word, const Cipher& current_cipher)
{
    for (int i = 0; i < 26; ++i)
    {
        if (current_cipher.encoding[i])
        {
            const char replace = toupper(current_cipher.encoding[i]);
            const char replace_with = tolower(current_cipher.real[i]);
            std::replace(
        word.begin(),
        word.end(),
        replace,
        replace_with);
        }
    }

    return word;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::vector<std::string> find_list_of_partial_matches(
    const std::unordered_multimap<std::string, std::string> dictionary,
    const std::string& encrypted_word,
    const Cipher& current_cipher)
{
    std::vector<std::string> partial_matches;
    std::size_t strlen = encrypted_word.size();
    const auto patternified_word = patternify_word(encrypted_word);
    const std::string partial_decode = partial_decode_word(encrypted_word, current_cipher);
    
    for (auto itr = dictionary.begin(); itr != dictionary.end(); ++itr)
    {
        bool found = true;
        if (itr->first == patternified_word)
        {
            for (std::size_t i = 0; i < strlen; ++i)
            {
                if (std::islower(partial_decode[i]) && itr->second[i] != partial_decode[i])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                partial_matches.push_back(itr->second);
            }
        }
    }

    return partial_matches;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::vector<std::string> find_list_of_partial_matches(
    const std::unordered_multimap<std::string, std::string> dictionary,
    const std::string& patternified_word,
    const std::string& partially_decrypted_word)
{
    std::vector<std::string> partial_matches;
    std::size_t strlen = partially_decrypted_word.size();
    
    for (auto itr = dictionary.begin(); itr != dictionary.end(); ++itr)
    {
        bool found = true;
        if (itr->first == patternified_word)
        {
            for (std::size_t i = 0; i < strlen; ++i)
            {
                if (std::islower(partially_decrypted_word[i]) && itr->second[i] != partially_decrypted_word[i])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                partial_matches.push_back(itr->second);
            }
        }
    }

    return partial_matches;
}