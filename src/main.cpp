#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "handlers.h"

using namespace std;



// Command Processing
void processCommand(const string &input) {
    vector<string> args = splitString(input, ' ');

    if (args.empty()) {
        return;
    }

    const string &command = args[0];

    // Handle built-in commands
    if (command == "exit") {
        handleExitCommand();
    } else if (command == "echo") {
        handleEchoCommand(args);
    } else if (command == "type") {
        handleTypeCommand(args);
    } else if (command == "pwd") {
        handlePwdCommand();
    } else {
        executeExternalCommand(args);
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
