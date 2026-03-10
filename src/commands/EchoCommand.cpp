#include "commands/EchoCommand.h"
#include <iostream>
#include <string>
#include <vector>

namespace shell {
namespace commands {

void EchoCommand::execute(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "\n";
        return;
    }
    
    for (size_t i = 1; i < args.size(); ++i) {
        std::cout << args[i];
        if (i < args.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "\n";
}

std::string EchoCommand::name() const {
    return "echo";
}

bool EchoCommand::is_builtin() const {
    return true;
}

} // namespace commands
} // namespace shell