#include "core/CommandRegistry.h"
#include "commands/Command.h"
#include "commands/EchoCommand.h"
#include "commands/ExitCommand.h"
#include "commands/TypeCommand.h"
#include "commands/ExternalCommand.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace shell {
namespace core {

CommandRegistry::CommandRegistry() {
    // Register built-in commands
    register_command(std::make_shared<commands::ExitCommand>());
    register_command(std::make_shared<commands::EchoCommand>());
    
    // TypeCommand needs reference to commands map
    auto type_cmd = std::make_shared<commands::TypeCommand>(commands_);
    register_command(type_cmd);
    
    // External command handler
    external_command_ = std::make_shared<commands::ExternalCommand>();
}

void CommandRegistry::register_command(std::shared_ptr<commands::Command> cmd) {
    commands_[cmd->name()] = std::move(cmd);
}

std::shared_ptr<commands::Command> CommandRegistry::get_command(const std::string& name) const {
    auto it = commands_.find(name);
    if (it != commands_.end()) {
        return it->second;
    }
    return external_command_;
}

const std::unordered_map<std::string, std::shared_ptr<commands::Command>>& 
CommandRegistry::get_commands() const {
    return commands_;
}

} // namespace core
} // namespace shell