#include "handlers.h"


using namespace std;

// Constants
const string BUILTIN_COMMANDS[] = {"exit", "echo", "type", "pwd", "cd"};
const char *PATH_ENV = getenv("PATH");

// Forward declarations of utility functions


string findExecutable(const string &command);

// Utility Functions
vector<string> splitString(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(str);

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

string findExecutable(const string &command) {
    if (!PATH_ENV) {
        return "";
    }

    for (vector<string> paths = splitString(PATH_ENV, ':'); const string &dir: paths) {
        string fullPath = dir + "/" + command;

        if (access(fullPath.c_str(), X_OK) == 0) {
            return fullPath;
        }
    }

    return "";
}

// Command Handlers
void handleExitCommand() {
    exit(0);
}

void handleEchoCommand(const string &input) {

/*
    *
    Command	Expected output	Explanation
    echo 'hello    world'	hello    world	Spaces are preserved within quotes.
    echo hello    world	hello world	Consecutive spaces are collapsed unless quoted.
    echo 'hello''world'	helloworld	Adjacent quoted strings 'hello' and 'world' are concatenated.
    echo hello''world	helloworld	Empty quotes '' are ignored.
 */
    bool inQuotes = false;
    string output;

    for (char ch: input) {
        if (ch == '\'') {
            inQuotes = !inQuotes;
        } else if (ch == ' ' && !inQuotes) {
            if (!output.empty() && output.back() != ' ') {
                output += ' ';
            }
        } else {
            output += ch;
        }
    }

    if (!output.empty() && output.back() == ' ') {
        output.pop_back();
    }

    cout << output << endl;

}

void handleTypeCommand(const vector<string> &args) {
    if (args.size() <= 1) {
        cout << "Invalid syntax" << endl;
        return;
    }

    const string &searchedCommand = args[1];

    for (const string &cmd: BUILTIN_COMMANDS) {
        if (cmd == searchedCommand) {
            cout << searchedCommand << " is a shell builtin" << endl;
            return;
        }
    }

    if (const string pathTo = findExecutable(searchedCommand); !pathTo.empty()) {
        cout << searchedCommand << " is " << pathTo << endl;
        return;
    }

    // Not found
    cout << searchedCommand << ": not found" << endl;
}

void handlePwdCommand() {
    char buf[256];
    if (getcwd(buf, sizeof(buf)) != nullptr) {
        cout << buf << endl;
    } else {
        cerr << "pwd error" << strerror(errno) << endl;
    }
}

void moveToHome() {
    const char *home = getenv("HOME");
    if (home != nullptr) {
        handleCdCommand(home);
    } else {
        std::cerr << "HOME not set\n";
    }
}

void handleCdCommand(const char *path) {
    if (chdir(path) != 0) {
        cout << "cd: " << path << ": No such file or directory" << endl;
    }
}

void executeExternalCommand(const vector<string> &args) {
    const string &command = args[0];
    string executablePath = findExecutable(command);

    if (executablePath.empty()) {
        cout << command << ": command not found" << endl;
        return;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        vector<char *> argv;
        for (const string &arg: args) {
            argv.push_back(const_cast<char *>(arg.c_str()));
        }
        argv.push_back(nullptr);

        execv(executablePath.c_str(), argv.data());

        // If execv returns, it failed
        perror("execv failed");
        exit(1);
    }
    if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    } else {
        // Fork failed
        perror("fork failed");
    }
}
