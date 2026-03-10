#pragma once

#include "commands/Command.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace shell {

// Forward declaration
namespace commands {
    class ExternalCommand;
}

namespace core {

class CommandRegistry {
public:
    CommandRegistry();
    
    void register_command(std::shared_ptr<commands::Command> cmd);
    std::shared_ptr<commands::Command> get_command(const std::string& name) const;
    
    const std::unordered_map<std::string, std::shared_ptr<commands::Command>>& get_commands() const;

private:
    std::unordered_map<std::string, std::shared_ptr<commands::Command>> commands_;
    std::shared_ptr<commands::ExternalCommand> external_command_;
};

} // namespace core
} // namespace shell