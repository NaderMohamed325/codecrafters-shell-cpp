#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "handlers.h"

using namespace std;


// Command enumeration
enum class Command {
    EXIT,
    ECHO,
    TYPE,
    PWD,
    CD,
    EXTERNAL
};

// Map string command to enum
Command getCommandType(const string &cmd) {
    if (cmd == "exit") return Command::EXIT;
    if (cmd == "echo") return Command::ECHO;
    if (cmd == "type") return Command::TYPE;
    if (cmd == "pwd") return Command::PWD;
    if (cmd == "cd") return Command::CD;
    return Command::EXTERNAL;
}

// Command Processing
void processCommand(const string &input) {
    vector<string> args = splitString(input, ' ');

    if (args.empty()) {
        return;
    }

    const string &command = args[0];

    // Handle built-in commands
    switch (getCommandType(command)) {
        case Command::EXIT:
            handleExitCommand();
            break;
        case Command::ECHO:
            handleEchoCommand(args);
            break;
        case Command::TYPE:
            handleTypeCommand(args);
            break;
        case Command::PWD:
            handlePwdCommand();
            break;
        case Command::CD:
            if (args.size() > 1) {
                if (args[1] == "~") {
                    moveToHome();
                } else {
                    handleCdCommand(args[1].c_str());
                }
            } else {
                moveToHome();
            }
            break;
        case Command::EXTERNAL:
            executeExternalCommand(args);
            break;
    }
}

// Main Loop
int main() {
    // Set output buffers to flush immediately
    cout << unitbuf;
    cerr << unitbuf;

    // REPL (Read-Eval-Print Loop)
    while (true) {
        cout << "$ ";

        string input;
        getline(cin, input);

        processCommand(input);
    }
}
