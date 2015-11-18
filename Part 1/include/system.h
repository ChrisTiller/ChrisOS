#ifndef _SYSTEM_H_INCLUDED_
#define _SYSTEM_H_INCLUDED_

#include <cstdlib>
#include <ctime>
#include <string>
#include <map>
#include <curses.h>

#include "io.h"
#include "command.h"

#ifndef NULL
#define NULL 0
#endif // NULL

using std::map;

class System {

public:
    static System* getInstance();

    void init();
    void close();
    void systemLoop();

    void alias(const vector<string>& params);

    void getDateTime(const vector<string>& params);
    void getTime(const vector<string>& params);
    void getDate(const vector<string>& params);
    void getVersion(const vector<string>& params);

    void help(const vector<string>& params);

private:
    System() {
        initscr();
        mWidth = COLS;
        mHeight = LINES;
        endwin();

        loadSystemFunctions();
    };

    static System* mInstance;

    System (System const&) = delete;
    void operator=(System const&) = delete;

    void loadSystemFunctions();
    bool findCommand(Command& command);

    int mWidth;
    int mHeight;

    typedef void (System::*systemFunction)(const vector<string>&);

    map<string, systemFunction> systemFunctions;
    map<string, string> aliasCommands;
};


#endif
