#pragma once

#include <string>
#include <vector>

namespace shell {
namespace commands {

class Command {
public:
    virtual ~Command() = default;
    
    virtual void execute(const std::vector<std::string>& args) = 0;
    virtual std::string name() const = 0;
    virtual bool is_builtin() const = 0;
};

} // namespace commands
} // namespace shell