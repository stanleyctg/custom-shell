#pragma once

#include "Command.h"
#include <string>
#include <vector>

namespace shell {
namespace commands {

class ExternalCommand : public Command {
public:
    void execute(const std::vector<std::string>& args) override;
    std::string name() const override;
    bool is_builtin() const override;

private:
    void execute_process(const std::string& filepath, const std::vector<std::string>& args);
};

} // namespace commands
} // namespace shell