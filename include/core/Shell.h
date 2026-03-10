#pragma once

#include "CommandRegistry.h"
#include <string>

namespace shell {
namespace core {

class Shell {
public:
    Shell();
    
    void run();
    void stop();

private:
    void display_prompt() const;
    void execute_command(const std::string& input);
    
    CommandRegistry registry_;
    bool running_;
};

} // namespace core
} // namespace shell