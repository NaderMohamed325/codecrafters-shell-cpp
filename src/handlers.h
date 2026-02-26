#ifndef HANDLERS_H
#define HANDLERS_H
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
std::vector<std::string> splitString(const std::string &str, char delimiter);
void handleExitCommand();

void handleEchoCommand(const std::vector<std::string> &args);

void handleTypeCommand(const std::vector<std::string> &args);

void handlePwdCommand();

void executeExternalCommand(const std::vector<std::string> &args);
void handleCdCommand(const char * path);
void moveToHome();

#endif // HANDLERS_H
