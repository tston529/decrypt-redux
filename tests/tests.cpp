#include "helper.hpp"
#include "setup.hpp"
#include <algorithm>
#include <ios>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>

/// @brief If set true, tests will have std::cout printed to the console
bool verbose = false;

/// @brief Struct representing test methods
struct Test
{
    /// @brief Holds the method to be run as a test
    std::function<bool()> test;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/// @brief      Tests the patternify_word method
/// @param      input     The string to be pattern-ified
/// @param      expected  What we expect the patternify function to output
/// @return     A Test object containing the patternify_word test
Test test_patternify_word(const std::string& input, const std::string& expected)
{
    const auto patternTest = [input, expected]() -> bool {
        const std::string output = patternify_word(input);
        std::cout << "\ninput: " << input << "\n"
              << "expected: " << expected << "\n"
              << "paternified word: " << output << "\n";
        return output == expected;
    };

    return Test{patternTest};
}

/// @brief      Tests the strip_end_punctuation method
/// @param[in]  input     the string to have its ending punctuation stripped
/// @param[in]  expected  what we expect the function to output
/// @return     A Test object containing the strip_end_punctuation test
Test test_strip_punctuation(const std::string& input, const std::string& expected)
{
    const auto stripTest = [input, expected]() -> bool {
        const std::string output = strip_end_punctuation(input);
        std::cout << "\ninput: " << input << "\n"
              << "expected: " << expected << "\n"
              << "modified string: " << output << "\n";
        return output == expected;
    };

    return Test{stripTest};
}

/// @brief      Tests the create_dictionary overload that turns a set of words
///             into a patternified multimap
/// @return     A Test object containing the create_dictionary test
Test test_create_dict_from_set()
{
    const auto createDictTest = []() -> bool {
        const std::unordered_multimap<std::string, std::string> expected {
            {"ABBC", "good"},
            {"ABBC", "book"},
            {"ABBA", "poop"},
            {"ABCCDEDFG", "different"}
        };
        const std::set<std::string> input{"good", "book", "poop", "different"};
        
        const auto newDict = create_dictionary(input);

        return expected == newDict;
    };

    return Test{createDictTest};
}

/// @brief      Creates a test for the partial_decode_word function
/// @param[in]  input          The input string
/// @param[in]  partialCipher  The partial cipher
/// @param[in]  expected       The value we expect the partial_decode_word
/// @return     A Test object for the partial_decode_word function
Test test_partial_decode_word(const std::string& input, const Cipher& partialCipher, const std::string& expected)
{
    const auto createPartialDecodeTest = [input, expected, partialCipher]()-> bool {
        const std::string partial_decoded_word = partial_decode_word(input, partialCipher);
        std::cout << "\ninput word: " << input
                << "\nexpected: " << expected 
                << "\npartial decode: " << partial_decoded_word
                << std::endl;
        return partial_decoded_word == expected;
    };
    return Test{createPartialDecodeTest};
}

/// @brief      Creates a test for the find_list_of_partial_matches function.
/// @param[in]  input          The input string
/// @param[in]  partialCipher  The partial cipher
/// @param[in]  expected       The value we expect the find_list_of_partial_matches function to return
/// @return     A Test object for the find_list_of_partial_matches function
Test test_find_list_of_partial_matches(const std::string& input, const Cipher& partialCipher, const std::vector<std::string>& expected)
{
    const auto dict = create_dictionary("./data_files/english_3000.txt");
    const auto createFindListOfPartialMatchesTest = [dict, input, partialCipher, expected]() -> bool {
        auto partial_matches = find_list_of_partial_matches(dict, input, partialCipher);
        return expected.size() == partial_matches.size() && std::is_permutation(expected.begin(), expected.end(), partial_matches.begin());
    };

    return Test{createFindListOfPartialMatchesTest};
}

/// @brief      Runs a list of tests, returns whether they all passed
/// @param[in]  tests  the list of tests to be run
/// @return     True if all tests passed, False otherwise
bool run_tests(const std::vector<Test>& tests)
{
    bool passed = true;
    for (const Test& test : tests)
    {
        const bool state = test.test();
        if (state)
        {
            std::cerr << ".";
        }
        else
        {
            std::cerr << 'x';
        }

        passed &= state;
    }

    std::cerr << std::endl;

    return passed;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

int main()
{
    if (!verbose)
    {
        std::cout.setstate(std::ios_base::failbit);
    }
    Cipher halfCipher{.encoding={'t', '\0', 'y', '\0', 'l', '\0', 'r', '\0', 'm', '\0', 'o', '\0', 'u', '\0', 's', '\0', 'c', '\0', 'g', '\0', 'k', '\0', 'v', '\0', 'x', '\0'}};
    Cipher emptyCipher{.encoding={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'}};
    Cipher partialCostanzaCipher{.encoding={'g', '\0', '\0', 'r', '\0', '\0', 'n', '\0', '\0', 's', '\0', 'l', 'c', '\0', 'b', 'h', '\0', '\0', 'm', '\0', '\0', 'u', '\0', '\0', 'x', 'y'}};
    
    // Register tests
    std::vector<Test> tests{};
    tests.emplace_back(test_patternify_word("googlegoggles", "ABBACDABAACDE"));
    tests.emplace_back(test_strip_punctuation("this is a test...()", "this is a test"));
    tests.emplace_back(test_create_dict_from_set());
    // Original word: "dinosaur"
    tests.emplace_back(test_partial_decode_word("IMPSGTKF", halfCipher, "IiPosauF"));
    // Original word: "alone"; encoded with the Costanza cipher
    tests.emplace_back(test_find_list_of_partial_matches("GLBZF", partialCostanzaCipher, {"alone", "aloud", "along"}));
    
    std::cerr << "Running tests..." << std::endl;
    if (!run_tests(tests))
    {
        std::cerr << "One or more tests failed." << std::endl;
        return 1;
    }
    else
    {
        std::cerr << "All tests passed!" << std::endl;
        return 0;
    }
}