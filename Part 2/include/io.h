#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;

namespace IO {

    // output functions
    template <class T>
    void print(T output) {
        cout << output;
    }

    template <class T>
    void println(T output) {
        cout << output << endl;
    }

    // intput functions
    string getString(string strPrompt);

    int getInt(string strPrompt);
}
#endif // IO_H_INCLUDED
