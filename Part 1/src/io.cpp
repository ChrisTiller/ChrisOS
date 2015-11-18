#include "../include/io.h"

string IO::getString(string strPrompt) {

    string input;

    print(strPrompt);

    getline(cin, input);

    return input;
}

int IO::getInt(string strPrompt) {

    int input;

    print(strPrompt);

    cin >> input;

    return input;
}
