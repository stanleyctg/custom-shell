#pragma once

#include "Command.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace shell {
namespace commands {

class TypeCommand : public Command {
public:
    explicit TypeCommand(const std::unordered_map<std::string, std::shared_ptr<Command>>& commands);
    
    void execute(const std::vector<std::string>& args) override;
    std::string name() const override;
    bool is_builtin() const override;

private:
    const std::unordered_map<std::string, std::shared_ptr<Command>>& commands_;
};

} // namespace commands
} // namespace shell