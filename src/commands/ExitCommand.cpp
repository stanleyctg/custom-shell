#include "commands/ExitCommand.h"
#include <cstdlib>
#include <string>
#include <vector>

namespace shell {
namespace commands {

void ExitCommand::execute(const std::vector<std::string>& /* args */) {
    std::exit(0);
}

std::string ExitCommand::name() const {
    return "exit";
}

bool ExitCommand::is_builtin() const {
    return true;
}

} // namespace commands
} // namespace shell
