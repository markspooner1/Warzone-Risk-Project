# include "CommandProcessing.h"
// #include <ifstream>

using namespace std;

// using namespace std;

void testCommandProcessor(){

    // Intro
    cout << "\nCommands: loadmap, validatemap, addplayer, gamestart, replay or quit. And has to be at a an acceptable state\n\n";
    string * currentState = new string("start");

    // Option of taking commands from console or file
    string mode;
    cout << "\n\tChoose mode (-console/-file<path>):";
    cin.ignore();
    getline(cin, mode);

    if (mode.find("-console") != string::npos) {

        // using console
        
        CommandProcessing * a = new CommandProcessing();
        while(true){
            string prevstate = *currentState;
            a->getCommand(currentState);
            if(*currentState == "ERROR") *currentState = prevstate;
            cout << "currentState: " + *currentState;
        }



        // for (int i = 0; i < a->gameCommands.size(); i++)
        // {
        //     cout << a->gameCommands.at(i);
        // }

        // Avoiding memory leaks
        delete a;
        a = NULL;

    } else if (mode.find("-file") != string::npos) {
        
        // using file (adapter)
        //string mode = "-file <C:\\Users\\slava\\OneDrive\\Desktop\\game_scenario.txt>";
        FileCommandProcessorAdapter * f = new FileCommandProcessorAdapter();
        f->getCommand(currentState, mode);

        // Avoiding memory leaks
        delete f;
        f = NULL;

    } else {

        cout << "\n Invalid entry. Exiting";
        exit(0);
    }

    



}