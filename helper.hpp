#include <string>

bool is_letter(const char c) noexcept
{
    return (c > 64 && c < 91) || (c > 96 && c < 123);
}

bool is_punctuation(const char c) noexcept
{
    return (c > 31 && c < 48) || (c > 57 && c < 65);
}

std::string strip_end_punctuation(const std::string& word)
{
    int count = 0;
    while (is_punctuation(word[word.length()-(1+count)]))
    {
        ++count;
    }

    return word.substr(0, word.length()-count);
}