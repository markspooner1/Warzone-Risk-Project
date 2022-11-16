# include "CommandProcessing.h"

// stream insertion operator overload
ostream& operator<<(ostream& os, const Command& c)
{
    os << "Command: " + c.theCommand + ", Effect: (Transitions to) " + c.theEffect + "\n";
    return os;
}


void CommandProcessing::getCommand(string * currentState) {
    readCommand(currentState);
    //cout << "\nin getCom: this: " << this; 
}

void CommandProcessing::readCommand(string * currentState) {
    // parsing the command in this method
    cout << "\n******************************\n";
    cout << "Write command here: ";
    string str;
    getline(cin, str);

    string effect = CommandProcessor::validate(str, currentState);
    CommandProcessing::saveCommand(str, effect, currentState);
    cout << "\n******************************\n";
}

void CommandProcessing::saveCommand(string command, string effect, string * currentState){
    // cout << "In saveCommand\n";

    // If effect is not empty, means that the command is valid and passed through, and got assigned an effect
    if (effect != "") {
        cout << "Command is valid. Saving.";
        *currentState = effect;
    } else {
        cout << "Command is NOT valid. Saving.";
        effect = "ERROR";
        *currentState = "ERROR";
    }

    Command c = Command(command);

    this->gameCommands.push_back(c);
    Notify(this);

    c.saveEffect(effect);

    cout << c;



}
std::string CommandProcessing::stringToLog(){
    return "Command: " + gameCommands.back().theCommand;
}


void Command::saveEffect(string effect) {
    theEffect = effect;
    Notify(this);
}

std::string Command::stringToLog(){
    return "Command's effect: " + theEffect;
}

string CommandProcessor::validate(string str, string * currentState){
    // first looks for the keyword, then sees if it's in the right state to run this command
    string effect = "";

    if (str.find("loadmap") != string::npos) {
        //cout << "\nthe entered command is loadmap\n";
        if (*currentState == "start" || *currentState == "maploaded") {
            effect = "maploaded";
            //cout << "Command is valid\n";
        } else {
            cout << "Command is invalid because its unrelated to current state\n";
        }
    } else if (str.find("validatemap") != string::npos) {
        if (*currentState == "maploaded") {
            effect = "mapvalidated";
            //cout << "Command is valid\n";
        } else {
            cout << "Command is invalid because its unrelated to current state\n";
        }
    } else if (str.find("addplayer") != string::npos) {
        if (*currentState == "mapvalidated" || *currentState == "playersadded") {
            effect = "playersadded";
            //cout << "Command is valid\n";
        } else {
            cout << "Command is invalid because its unrelated to current state\n";
        }
    } else if (str.find("gamestart") != string::npos) {
        if (*currentState == "playersadded") {
            effect = "assignreinforcement";
            //cout << "Command is valid\n";
        } else {
            cout << "Command is invalid because its unrelated to current state\n";
        }
    } else if (str.find("replay") != string::npos){
        if (*currentState == "assignreinforcement") {
            effect = "start";
            //cout << "Command is valid\n";
        } else {
            cout << "Command is invalid because its unrelated to current state\n";
        }
    } else if (str.find("quit") != string::npos) {
        if (*currentState == "win") {
            effect = "exit program";
            //cout << "Command is valid\n";
        } else {
            cout << "Command is invalid because its unrelated to current state\n";
        }
    } else {
        cout << "The command is invalid";
    }

    return effect;
}

// FileCommandProcessorAdapter version of getCommand
void FileCommandProcessorAdapter::getCommand(string * currentState, string mode) {
    readCommand(currentState, mode);
}

// FileCommandProcessorAdapter version of readCommand
void FileCommandProcessorAdapter::readCommand(string * currentState, string mode) {
    // parsing the command in this method
    
    stack<int> dels;
    string path = "";
    for (int i = 0; i < mode.size(); i++) {
        // If opening delimeter
        // is encountered
        if (mode[i] == '<') {
            dels.push(i);
        }else if (mode[i] == '>' && !dels.empty()) {
            // Extract the position
            // of opening delimeter
            int pos = dels.top();
            dels.pop();
            // Length of substring
            int len = i - 1 - pos;
            // Extract the substring
            path = mode.substr(pos + 1, len);
            cout << "\n\npath: " + path;
        }
    }

    //std::ifstream file("C:\\Users\\slava\\OneDrive\\Desktop\\game_scenario.txt");
    std::ifstream file (path);
    std::string str; 
    cout << "Printing file contents\n";
    while (std::getline(file, str))
    {
        // Processing string
        cout << str << endl;

        // still calling CommandProcessor methods as there is no change there
        cout << "\n******************************\n";
        string effect = CommandProcessor::validate(str, currentState);
        CommandProcessing::saveCommand(str, effect, currentState);
        cout << "\nCurrentState: " + *currentState;
        cout << "\n******************************\n";
    }
}



Command::Command(string command, string effect) : theCommand(command), theEffect(effect) 
{}
Command::Command(string command) : theCommand(command)
{}

Command::Command() {}

Command::~Command() {}

CommandProcessing::CommandProcessing(){}

CommandProcessing::~CommandProcessing(){}

FileCommandProcessorAdapter::FileCommandProcessorAdapter() {}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){}
