#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


const string BUILTIN_COMMANDS[] = {"exit", "echo", "type"};


vector<string> splitString(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(str);

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


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
    if (args.size() > 1) {
        const string &searchedCommand = args[1];
        cout << searchedCommand << " is a shell builtin" << endl;
    } else {
        cout << "Invalid syntax" << endl;
    }
}

void handleUnknownCommand(const string &input) {
    cout << input << ": command not found" << endl;
}


void processCommand(const string &input) {
    const vector<string> args = splitString(input, ' ');

    if (args.empty()) {
        return;
    }

    if (const string &command = args[0]; command == "exit") {
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
[[noreturn]] int main() {
    cout << unitbuf;
    cerr << unitbuf;


    while (true) {
        cout << "$ ";

        string input;
        getline(cin, input);

        processCommand(input);
    }

}
