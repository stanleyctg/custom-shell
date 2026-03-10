#include "utils/PathResolver.h"
#include <sstream>
#include <string>
#include <string_view>
#include <optional>
#include <filesystem>
#include <cstdlib>
#include <unistd.h>

namespace shell {
namespace utils {

std::optional<std::filesystem::path> PathResolver::find_executable(std::string_view cmd) {
    const char* path_env = std::getenv("PATH");
    if (!path_env) {
        return std::nullopt;
    }
    
    std::stringstream path_stream(path_env);
    std::string directory;
    
    while (std::getline(path_stream, directory, ':')) {
        std::filesystem::path full_path = std::filesystem::path(directory) / cmd;
        if (is_executable(full_path)) {
            return full_path;
        }
    }
    
    return std::nullopt;
}

bool PathResolver::is_executable(const std::filesystem::path& path) {
    return access(path.c_str(), X_OK) == 0;
}

} // namespace utils
} // namespace shell