

# pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

class Command {
    public:
        string theCommand; // command that was types
        string theEffect; // effect of command or error message
        void saveEffect(string effect);

        Command();
        Command(string command, string effect);
        Command(string command);
        ~Command();
        //ostream& operator<<(ostream& os, const Command& c);
};

class CommandProcessing {
    private:
         void readCommand(string * currentState); // get command from console
    public:
        vector<Command> gameCommands; // the command sequence of a game
         void getCommand(string * currentState); // gets command from user (console/file)
         void saveCommand(string command, string effect, string * currentState); // saves command to gameCommands
         CommandProcessing();
         ~CommandProcessing();
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