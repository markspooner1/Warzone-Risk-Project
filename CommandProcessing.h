

# pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include "LoggingObserver.h"

using namespace std;

class Command: public Subject, public ILoggable {
    public:
        string theCommand; // command that was types
        string theEffect; // effect of command or error message
        void saveEffect(string effect);

        Command();
        Command(string command, string effect);
        Command(string command);
        ~Command();
        //ostream& operator<<(ostream& os, const Command& c);


    //this funtion is for ILoggable class in LoggingObserver.h
    std::string stringToLog() override;
};

class CommandProcessing: public Subject, public ILoggable {
    private:
         void readCommand(string * currentState); // get command from console
    public:
        vector<Command> gameCommands; // the command sequence of a game
         void getCommand(string * currentState); // gets command from user (console/file)
         void saveCommand(string command, string effect, string * currentState); // saves command to gameCommands
         CommandProcessing();
         ~CommandProcessing();

    //this funtion is for ILoggable class in LoggingObserver.h
    std::string stringToLog() override;

};

class CommandProcessor {
    public:
        static string validate(string str, string * cs);
};


class FileCommandProcessorAdapter : CommandProcessing {
    private:
         void readCommand(string * currentState, string mode); // get command from console
    public:
        vector<Command> gameCommands; // the command sequence of a game
        void getCommand(string * currentState, string mode); // gets command from user (console/file)

        FileCommandProcessorAdapter();
        ~FileCommandProcessorAdapter();
};

void testCommandProcessor();