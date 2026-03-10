#include "utils/Tokenizer.h"
#include <sstream>
#include <string>
#include <vector>

namespace shell {
namespace utils {

std::vector<std::string> Tokenizer::tokenize(const std::string& cmd_line) {
    std::stringstream cmd_ss(cmd_line);
    std::vector<std::string> tokens;
    std::string word;
    
    while (cmd_ss >> word) {
        tokens.push_back(word);
    }
    
    return tokens;
}

} // namespace utils
} // namespace shell
