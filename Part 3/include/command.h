#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::stringstream;
using std::getline;

class Command {

public:
    Command();
    Command(string command);

    void parseCommand(string command);

    string getMainCommand();
    vector<string> getCommandParams();

private:
    vector<string> tokens;
};

#endif // COMMAND_H_INCLUDED
