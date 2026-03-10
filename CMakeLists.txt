cmake_minimum_required(VERSION 3.20)
project(shell VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/core/Shell.cpp
    src/core/CommandRegistry.cpp
    src/commands/EchoCommand.cpp
    src/commands/ExitCommand.cpp
    src/commands/TypeCommand.cpp
    src/commands/ExternalCommand.cpp
    src/utils/Tokenizer.cpp
    src/utils/PathResolver.cpp
)

# Create executable
add_executable(shell ${SOURCES})

# Include directories
target_include_directories(shell PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

# Installation
install(TARGETS shell DESTINATION bin)