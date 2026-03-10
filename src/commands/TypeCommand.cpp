#include "commands/TypeCommand.h"
#include "utils/PathResolver.h"
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>

namespace shell {
namespace commands {

TypeCommand::TypeCommand(const std::unordered_map<std::string, std::shared_ptr<Command>>& commands)
    : commands_(commands) {}

void TypeCommand::execute(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "type: missing argument\n";
        return;
    }
    
    const std::string& cmd_name = args[1];
    
    // Check if it's a builtin
    auto it = commands_.find(cmd_name);
    if (it != commands_.end() && it->second->is_builtin()) {
        std::cout << cmd_name << " is a shell builtin\n";
        return;
    }
    
    // Check if it's in PATH
    if (auto path = utils::PathResolver::find_executable(cmd_name)) {
        std::cout << cmd_name << " is " << path->string() << "\n";
    } else {
        std::cout << cmd_name << ": not found\n";
    }
}

std::string TypeCommand::name() const {
    return "type";
}

bool TypeCommand::is_builtin() const {
    return true;
}

} // namespace commands
} // namespace shell