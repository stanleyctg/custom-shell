#include "commands/ExternalCommand.h"
#include "utils/PathResolver.h"
#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <filesystem>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace shell {
namespace commands {

void ExternalCommand::execute(const std::vector<std::string>& args) {
    if (args.empty()) return;
    
    auto executable_path = utils::PathResolver::find_executable(args[0]);
    if (!executable_path) {
        std::cout << args[0] << ": command not found\n";
        return;
    }
    
    execute_process(executable_path->string(), args);
}

std::string ExternalCommand::name() const {
    return "external";
}

bool ExternalCommand::is_builtin() const {
    return false;
}

void ExternalCommand::execute_process(const std::string& filepath, const std::vector<std::string>& args) {
    std::vector<char*> argv;
    argv.reserve(args.size() + 1);
    
    for (const auto& arg : args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr);
    
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        execv(filepath.c_str(), argv.data());
        perror("execv");
        _exit(127);
    } else if (pid > 0) {
        // Parent process
        int status = 0;
        waitpid(pid, &status, 0);
    } else {
        perror("fork");
    }
}

} // namespace commands
} // namespace shell