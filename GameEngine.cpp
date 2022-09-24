#include "gameEngine.h"

#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <regex>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

// loadmap asks the user to load map(s)

void Startup::loadmap()
{
    string load;
    cout << "Please enter loadmap <filename>:";
    cin >> load;

    do
    {

        if (load == "loadmap <canada.map>" || load == "loadmap <germany.map>" || load == "loadmap <greece.map>")
        {
            cout << "The map is loaded\n";
        }

        cout << "If you wish to load another map. Enter loadmap.\n If not enter done\n"
             << endl;
        cin >> load;

        if (load == "done")
        {
            cout << "No more maps to be loaded.\n";
        }

        stack<int> dels;
        for (int i = 0; i < load.size(); i++)
        {
            // If opening delimeter
            // is encountered
            if (load[i] == '<')
            {
                dels.push(i);
            }

            // If closing delimeter
            // is encountered
            else if (load[i] == '>' && !dels.empty())
            {

                // Extract the position
                // of opening delimeter
                int pos = dels.top();

                dels.pop();

                // Length of substring
                int len = i - 1 - pos;

                // Extract the substring
                string ans = load.substr(pos + 1, len);
                cout << "\n◤◢◣◥◤ ◢◣◆◢◣◥◤◢◣◥◤◢◣◥◤ ◢◣◆◢◣◥◤◢◣◥\n"
                        "You have loaded the following map. \n"
                     << endl;
                cout << "                 " + ans << endl;
                cout << "◣◥◤◢◣ ◥◤◆◥◤◢◣◥◤◢◣◥◤◢◣ ◥◤◆◥◤◢◣◥◤◢\n"
                     << endl;
            }
        }

    } while (load == "loadmap <canada>" || load == "loadmap <germany>" || load == "loadmap <greece>");
}

// validateMap checks of the player validates the loaded map

void Startup::validateMap()
{
    string validate;
    cout << "Type validatemap if you validate the map you entered.\n";
    cin >> validate;
    if (validate == "validatemap")
    {
        cout << "Your map has been validated\n";
    }
    else
    {
        cout << "╞╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╡\n";
        cout << "Invalid Entry.";
        exit(0);
    }
}

// addPlayer asks the user to add all the player(s)

void Startup::addPlayer()
{
    // ofstream MyFile("players.txt");

    string confirm;
    cout << "\nIf you wish to add a player. "
            "Please enter: \n addplayer <playername>.\n";
    cin >> confirm;

    // using regex to check that the format entered by the user respect the format addplayer <playername>
    auto const regex = std::regex("addplayer\\s*(.*)+");
    auto const myText = std::string(confirm);
    bool const myTextContainsRegex = std::regex_search(myText, regex);

    while (confirm != "done" || myTextContainsRegex == true)
    {
        if (myTextContainsRegex == true)
        {
            cout << "\n\nDo you wish to add another player\n? "
                    "If so enter addplayer <playername>. \n"
                    "Otherwise enter done\n";

            cin >> confirm;
        }

        // terminate adding players
        cin >> confirm;

        if (confirm == "done")
        {
            cout << "Adding players had ended. Transitioning to the next state.\n\n";
            break;
        }
    }
}

// assignReinforcement assigns countries to players

void Play::assignReinforcement()
{

    string assign;
    cout << "\nPlease enter assigncountries. \n";
    cin >> assign;

    if (assign == "assigncountries")
    {
        cout << "You have successfully been assigned countries.\n\n";
    }
    else
    {
        cout << "╞╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╡\n";
        cout << "Entry Invalid.\n  ";
        exit(0);
    }
}

// issueOrders allows user to issue orders

void Play::issueOrders()
{
    string issue;
    cout << "\n Please enter issueorder ";
    cin >> issue;
    do
    {
        if (issue == "issueorder")
        {
            cout << "The order has been issued.\n\n";
        }

        while (issue != "issueorder")
        {
            cout << "╞╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╡\n";
            cout << "Invalid Entry.";
            exit(0);
        }

        cout << "\n Please enter issueorder. \nIf you wish to end issuing orders, please enter done\n ";
        cin >> issue;
        if (issue == "done")
            cout << "Issuing orders has been stopped. Transitioning to the next step.\n\n";

    } while (issue == "issueorder");
}
// executeorders lets user execute orders

void Play::executeorders()
{
    string execute;
    cout << "Please enter execorder ";
    cin >> execute;
    do
    {
        if (execute == "execorder")
        {
            cout << "The order has been executed.\n\n";
        }

        while (execute != "execorder")
        {
            cout << "╞╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╡\n";
            cout << "Invalid Entry. ";
            exit(0);
        }

        cout << "\n Please enter execorder. \n If you are done executing orders, enter done.\n\n ";
        cin >> execute;

        if (execute == "done")
            cout << "No more orders to be executed. \n \n";
    } while (execute == "execorder");
}

// endexecuteorders allows user to end the execution of orders

void Play::endexecuteorders()
{
    string endexecorder;
    cout << "if you wish to end executing orders. \nPlease enter endexecorders";
    cin >> endexecorder;
    if (endexecorder == "endexecorders")
    {
        cout << "endexecorders has successfully ended";
    }
    else
    {
        cout << "╞╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╡\n";
        cout << "Invalid Entry. ";
        exit(0);
    }
}
// win announces that the user has won the game

void Play::win()
{
    cout << " ◤◢◣◥◤ ◢◣◆◢◣◥◤◢◣◥◤◢◣◥◤ ◢◣◆◢◣◥◤◢◣◥\n";
    cout << "Congratulations you have WON !!!\n";
    cout << "◣◥◤◢◣ ◥◤◆◥◤◢◣◥◤◢◣◥◤◢◣ ◥◤◆◥◤◢◣◥◤◢\n"
            "";
}

void GameEngine::startupPhase()
{
    string start, gamestart; // string to start the game
    string option;
    cout << "◤◢◣◥◤ ◢◣◆◢◣◥◤◢◣◥◤◢◣◥◤ ◢◣◆◢◣◥◤◢◣◥\n";
    cout << "WELCOME TO WARZONE. \n";
    cout << "◣◥◤◢◣ ◥◤◆◥◤◢◣◥◤◢◣◥◤◢◣ ◥◤◆◥◤◢◣◥◤◢\n";
    cout << "Enter start to begin your adventure.\n";
    cin >> start;

    // looping through the startup and the playing state diagram
    // when either the user enter start or play once the user chooses to play
    // after winning the game

    while (start == "start" || option == "play")
    {
        Startup starting;
        starting.loadmap();
        starting.validateMap();
        starting.addPlayer();

        cout << "If you wish to start the game. "
                "Enter gamestart. \n";
        cin >> gamestart;

        // reading a text file

        if (start == "start" || option == "play")
        {
            Play playing;
            playing.assignReinforcement();
            playing.issueOrders();
            playing.executeorders();
        }

        cout
            << "If you wish to win. Enter win.\n Otherwise enter endexecorders if you wish to end executing orders. \n";
        cin >> option;

        if (option == "win")
        {
            Play playing;
            playing.win();

            cout
                << "If you wish to continue playing. Enter play.\n Otherwise if you wish to end the game. Enter end. \n";
            cin >> option;
        }

        // loops through the methods assignReinforcement, issueOrders, executeorders, endexecuteorders
        // to allow user to go from executing orders to assigning reinforcement.

        while (option == "endexecorders")
        {
            Play playingexec;
            playingexec.assignReinforcement();
            playingexec.issueOrders();
            playingexec.executeorders();
            playingexec.endexecuteorders();

            cout
                << "If you wish to win. Enter win.\n Otherwise enter endexecorders if you wish to end executing orders. \n";
            cin >> option;

            if (option == "win")
            {
                Play playing;
                playing.win();

                cout
                    << "If you wish to continue playing. Enter play.\n Otherwise if you wish to end the game. Enter end. \n";
                cin >> option;
            }
        }

        if (option == "end")
        {
            exit(0);
        }
    }
}

void testGameStates()
{

    // starts the startup phase then leads to the play phase once user enters gamestart

    GameEngine startup;
    startup.startupPhase();
}

