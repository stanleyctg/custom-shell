#include "core/Shell.h"
#include "core/CommandRegistry.h"
#include "utils/Tokenizer.h"
#include "commands/Command.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace shell {
namespace core {

Shell::Shell() 
    : registry_(), running_(true) {}

void Shell::run() {
    while (running_) {
        display_prompt();
        
        std::string input;
        if (!std::getline(std::cin, input)) {
            break;
        }
        
        execute_command(input);
    }
}

void Shell::stop() {
    running_ = false;
}

void Shell::display_prompt() const {
    std::cout << "$ " << std::flush;
}

void Shell::execute_command(const std::string& input) {
    auto tokens = utils::Tokenizer::tokenize(input);
    if (tokens.empty()) {
        return;
    }
    
    auto command = registry_.get_command(tokens[0]);
    command->execute(tokens);
}

} // namespace core
} // namespace shell