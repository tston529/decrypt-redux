#include <string>
#include <unordered_map>
#include <set>
#include <vector>

/// @brief Creates a map of patterned-words to a list of words that
///        yielded that pattern. Example entry: {"ABBC" : ["book", "good", "poop"]}
/// @param filename name of the file from which to create the dictionary
/// @return the populated multimap of patterns to list of origin words
auto create_dictionary(const std::string& filename) -> std::unordered_multimap<std::string, std::string>;

/// @brief Creates a map of patterned-words to a list of words that
///        yielded that pattern. Example entry: {"ABBC" : ["book", "good", "poop"]}
/// @param dict a set of words to be patternified
/// @return the populated multimap of patterns to list of origin words
auto create_dictionary(const std::set<std::string>& dict) -> std::unordered_multimap<std::string, std::string>;

/// @brief Creates a map of patterned-words to a list of words that
///        yielded that pattern. Example entry: {"ABBC" : ["book", "good", "poop"]}
/// @param dict a set of words to be patternified
/// @return the populated multimap of patterns to list of origin words
auto create_dictionary(const std::vector<std::string>& word_list) -> std::unordered_multimap<std::string, std::string>;