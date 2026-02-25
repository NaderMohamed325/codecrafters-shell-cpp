#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Constants
const string BUILTIN_COMMANDS[] = {"exit", "echo", "type"};

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

// Command Handlers
void handleExitCommand() {
    exit(0);
}

void handleEchoCommand(const vector<string> &args) {
    if (args.size() > 1) {
        for (size_t i = 1; i < args.size(); ++i) {
            cout << args[i];
            if (i < args.size() - 1) {
                cout << " ";
            }
        }
    }
    cout << endl;
}

void handleTypeCommand(const vector<string> &args) {
    if (args.size() <= 1) {
        cout << "Invalid syntax" << endl;
        return;
    }

    const string &searchedCommand = args[1];

    for (const string &cmd : BUILTIN_COMMANDS) {
        if (cmd == searchedCommand) {
            cout << searchedCommand << " is a shell builtin" << endl;
            return;
        }
    }

    cout << searchedCommand << ": not found" << endl;
}

void handleUnknownCommand(const string &input) {
    cout << input << ": command not found" << endl;
}

// Command Processing
void processCommand(const string &input) {
    vector<string> args = splitString(input, ' ');

    if (args.empty()) {
        return;
    }

    const string &command = args[0];

    if (command == "exit") {
        handleExitCommand();
    } else if (command == "echo") {
        handleEchoCommand(args);
    } else if (command == "type") {
        handleTypeCommand(args);
    } else {
        handleUnknownCommand(input);
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

    return 0;
}
