#pragma once

#include <filesystem>
#include <optional>
#include <string_view>

namespace shell {
namespace utils {

class PathResolver {
public:
    static std::optional<std::filesystem::path> find_executable(std::string_view cmd);

private:
    static bool is_executable(const std::filesystem::path& path);
};

} // namespace utils
} // namespace shell