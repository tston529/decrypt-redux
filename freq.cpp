#include <fstream>
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <array>
#include <string>
#include "helper.hpp"
#include "setup.hpp"

int rate_guess(
    const std::set<std::string> dictionary,
    const std::unordered_map<std::string, 
    std::string>& cipher,
    const Cipher& current_codex)
{
    return 0;
}


int main()
{
    std::set<std::string> dictionary{};

    std::cout << "Creating dictionary..." << std::endl;

    // std::ifstream file("data_files/dictionary.txt");
    // if (file.is_open())
    // {
    //     std::string token;
    //     while (file >> token)
    //     {
    //         dictionary.insert(token);
    //     }
    // }

    const auto encoded_dictionary = create_dictionary("data_files/dictionary.txt");
    std::cout << encoded_dictionary.size() << std::endl;
    
    const auto cipher = create_dictionary("data_files/english_cipher.txt");
    std::cout << cipher.size() << std::endl;

    std::vector<std::string> fewest_matches;
    fewest_matches.reserve(encoded_dictionary.size()/2);
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
    } 
}