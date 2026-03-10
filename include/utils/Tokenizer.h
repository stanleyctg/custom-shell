#pragma once

#include <string>
#include <vector>

namespace shell {
namespace utils {

class Tokenizer {
public:
    static std::vector<std::string> tokenize(const std::string& cmd_line);
};

} // namespace utils
} // namespace shell