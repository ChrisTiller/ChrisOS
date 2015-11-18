#include "../include/command.h"


Command::Command() {

};

Command::Command(string command) {
    parseCommand(command);
}

void Command::parseCommand(string command) {

    tokens.clear();

    // got this solution from stackoverflow by user Evan Teran
    // http://stackoverflow.com/questions/236129/split-a-string-in-c

    stringstream ss(command);
    string token;
    while (getline(ss, token, ' ')) {
        tokens.push_back(token);
    }
}

string Command::getMainCommand() {

    // returns the first element of the vector
    if (tokens.size() > 0) {
        return tokens.at(0);
    }
    return "";
}

vector<string> Command::getCommandParams() {

    // returns all the elements passed the first element
    if (tokens.size() > 1) {
        return vector<string>(tokens.begin()+1, tokens.begin() + tokens.size());
    }
    return vector<string>();
}
