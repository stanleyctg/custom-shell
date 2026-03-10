#pragma once

#include "Command.h"
#include <string>
#include <vector>

namespace shell {
namespace commands {

class EchoCommand : public Command {
public:
    void execute(const std::vector<std::string>& args) override;
    std::string name() const override;
    bool is_builtin() const override;
};

} // namespace commands
} // namespace shell