#include "helper.hpp"
#include "frequency_setup.hpp"
#include <iostream>
#include <functional>
#include <vector>

/// @brief If set true, tests will have std::cout printed to the console
bool verbose = false;

/// @brief Struct representing test methods
struct Test
{
    /// @brief Holds the method to be run as a test
    std::function<bool()> test;
};

/// @brief tests the patternify_word method
/// @param input the string to be pattern-ified
/// @param expected what we expect the patternify function to output
/// @return a Test object containing the patternify_word test
Test test_patternify_word(const std::string& input, const std::string& expected)
{
    const auto patternTest = [input, expected]() -> bool {
        const std::string output = patternify_word(input);
        std::cout << "input: " << input << "\n"
              << "expected: " << expected << "\n"
              << "paternified word: " << output << "\n";
        return output == expected;
    };

    return Test{patternTest};
}

/// @brief runs a list of tests, returns whether they all passed
/// @param tests the list of tests to be run
/// @return true of all tests passed, false otherwise
bool run_tests(const std::vector<Test>& tests)
{
    bool passed = true;
    for (const Test& test : tests)
    {
        bool state = test.test();
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

int main()
{
    if (!verbose)
    {
        std::cout.setstate(std::ios_base::failbit);
    }

    // Register tests
    std::vector<Test> tests{};
    tests.emplace_back(test_patternify_word("googlegoggles", "ABBACDABAACDE"));
    
    std::cerr << "Running tests..." << std::endl;
    if (!run_tests(tests))
    {
        std::cerr << "tests failed" << std::endl;
        return 1;
    }
    else
    {
        std::cerr << "All tests passed!" << std::endl;
        return 0;
    }
}