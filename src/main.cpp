#include  <bits/stdc++.h>
using namespace std;

int main() {
    // Flush after every std::cout / std:cerr
    while (true) {
        cout << std::unitbuf;
        cerr << std::unitbuf;
        cout << "$ ";
        string command;
        cin >> command;
        if ( command == "exit" ) {
            exit(0);
        }
        cout << command << ": command not found" << endl;
    }
}
