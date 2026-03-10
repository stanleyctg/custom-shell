#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <optional>
#include <unistd.h>
#include <filesystem>
#include <span>
#include <sys/types.h>
#include <sys/wait.h>   // waitpid
#include <unistd.h>     // fork, exec
#include <unordered_map>

using namespace std;
namespace fs = std::filesystem;

class Tokenizer {
  public:
    static std::vector<std::string> tokenize(const std::string& cmd_line) {
    std::stringstream cmd_ss(cmd_line);
    std::vector<std::string> toks;
    std::string word;

    while (cmd_ss >> word) {
      toks.push_back(word);
    }
    return toks;
  } 
};

class PathResolver {
  public:
    static optional<fs::path> find_executable(string_view cmd) {
      const char* path_env = getenv("PATH");
      if (!path_env) return nullopt;
        
      std::stringstream path_stream(path_env);
      std::string directory;
        
      while (getline(path_stream, directory, ':')) {
        fs::path full_path = fs::path(directory) / cmd;
        if (is_executable(full_path)) {
          return full_path;
        }
      }
        
      return std::nullopt;
    }
      
  private:
      static bool is_executable(const fs::path& path) {
        return access(path.c_str(), X_OK) == 0;
      }
};


class Command {
  public:
    virtual ~Command() = default;
    virtual void execute(const vector<string>& args) = 0;
    virtual string name() const = 0;
    virtual bool is_builtin() const = 0;
};

class EchoCommand : public Command {
  public:
     void execute(const vector<string>& args) override {
        if (args.size() < 2) {
            std::cout << "";
        } else {
            for (size_t i = 1; i < args.size(); ++i) {
                std::cout << args[i] << " ";
            }
            std::cout << "\n";
        }
    }
    string name() const override { return "echo"; }
    bool is_builtin() const override { return true; }
};

class ExitCommand: public Command {
  public:
    void execute(const vector<string>& args) override {
      exit(0);
    }
    string name() const override { return "exit"; }
    bool is_builtin() const override { return true; }    
};

class TypeCommand : public Command {
  public:
    explicit TypeCommand(const unordered_map<std::string, shared_ptr<Command>>& commands)
      : commands_(commands) {}
    
    void execute(const vector<string>& args) override {
      if (args.size() < 2) {
        std::cerr << "type: missing argument\n";
        return;
      }
        
      const string& cmd_name = args[1];
        
      // Check if it's a builtin
      auto it = commands_.find(cmd_name);
      if (it != commands_.end() && it->second->is_builtin()) {
        cout << cmd_name << " is a shell builtin\n";
        return;
      }
        
      // Check if it's in PATH
      if (auto path = PathResolver::find_executable(cmd_name)) {
        cout << cmd_name << " is " << path->string() << "\n";
      } else {
        cout << cmd_name << ": not found\n";
      }
    }
    
    string name() const override { return "type"; }
    bool is_builtin() const override { return true; }
      
  private:
    const std::unordered_map<string, shared_ptr<Command>>& commands_;
};

class ExternalCommand : public Command {
public:
    void execute(const vector<string>& args) override {
        if (args.empty()) return;
        
        auto executable_path = PathResolver::find_executable(args[0]);
        if (!executable_path) {
            cout << args[0] << ": command not found\n";
            return;
        }
        
        execute_process(executable_path->string(), args);
    }
    
    string name() const override { return "external"; }
    bool is_builtin() const override { return false; }
    
private:
  void execute_process(const string& filepath, const vector<string>& args) {
    vector<char*> argv;
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
};

class CommandRegistry {
  public:
    CommandRegistry () {
      register_command(make_shared<ExitCommand>());
      register_command(make_shared<EchoCommand>());
      
      auto type_cmd = make_shared<TypeCommand>(commands_);
      register_command(type_cmd);

      external_command_ = make_shared<ExternalCommand>();
    }

    void register_command(shared_ptr<Command> cmd) {
      commands_[cmd->name()] = move(cmd);
    }

    shared_ptr<Command> get_command(const string& name) const {
      auto it = commands_.find(name);
      if (it != commands_.end()) {
        return it->second;
      }
      return external_command_;
    }

  private:
    unordered_map<string, shared_ptr<Command>> commands_;
    shared_ptr<ExternalCommand> external_command_;
};

class Shell {
  public:
    Shell(): registry_(), running_(true) {}

    void run() {
      while (running_) {
        display_prompt();

        string input;
        if (!getline(cin, input)) {
          break;
        }
        execute_command(input);
      }
    }

    void stop() {
      running_ = false;
    }

    private:
      void display_prompt() {
        cout << "$" << flush;
      }

      void execute_command(const string& input) {
        auto tokens = Tokenizer::tokenize(input);
        if (tokens.empty()) return;

        auto command = registry_.get_command(tokens[0]);
        command->execute(tokens);
      }

      CommandRegistry registry_;
      bool running_;
};

int main() {
  Shell shell;
  shell.run();
  return 0;
}


// Refactor the code into classes to support more commands
// Main class loop
// A shell class, responsible for displaying prompts and executing commands
// Deals with commands
// A registry of commands, in order to get commands by name
// A command interface that describes different command names
// Class of these commands implementing the interface
// Utility
// A path resolver to determine executability and finding executable files
// A tokenize class to break down the input