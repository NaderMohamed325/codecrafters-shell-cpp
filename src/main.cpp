#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << unitbuf;
    cerr << unitbuf;

    while (true) {
        cout << "$ ";

        string input;
        getline(cin, input);

        if (input == "exit") {
            exit(0);
        }

        if (input.substr(0, 4) == "echo") {
            if (input.size() > 5)
                cout << input.substr(5) << endl;
            else
                cout << endl;
        } else {
            cout << input << ": command not found" << endl;
        }
    }
}
