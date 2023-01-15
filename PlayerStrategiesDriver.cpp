#include "PlayerStrategy.h"
#include "Map.h"
#include "Cards.h"
#include "Player.h"
#include "CommandProcessing.h"
void testPlayerStrategies(){
    GameEngine *g = new GameEngine();
    Deck *adeck = new Deck();
    adeck->initial_deck();
    g->deck = adeck;

    vector<Territory*> MapTerritories;
    vector<Continent*> MapContinents;
    Continent *dummyC1 = new Continent("1", 5);
    MapContinents.push_back(dummyC1);

    Territory *dummyT1 = new Territory("A", "1");
    Territory *dummyT2 = new Territory("B" , "1");
    Territory *dummyT3 = new Territory("C" , "1");

    dummyT1->neighbours.push_back(dummyT2);
    dummyT3->neighbours.push_back(dummyT1);

    MapTerritories.push_back(dummyT1);
    MapTerritories.push_back(dummyT2);
    MapTerritories.push_back(dummyT3);


    Map *m = new Map(MapTerritories, MapContinents);
    g->map = m;

    cout << "Enter 1 for example 1, 2 for example 2: " << endl;
    string choice;
    cin >> choice;
    if(choice == "1"){
        cout << "**Case where a neutral players strategy dynamically changes during play and that human player requires input(enter start)**" << endl;
        string s;
        cin >> s;

        Player *p1 = new Player("Normal Player#1", g);
        p1->ps = new HumanPlayerStrategy(p1);
        Player *p3 = new Player("Neutral Player#1", g);
        p3->ps = new NeutralPlayerStrategy(p3);
        p1->addTerritory(dummyT1);
        p3->addTerritory(dummyT2);
        p3->addTerritory(dummyT3);

        g->players.push_back(p1);
        g->players.push_back(p3);

        g->mainGameLoop();
        delete g;
        delete p1;
        delete p3;
        delete adeck;
    }else{
        cout << "**Example of a game being played by different computer players (enter start)**" << endl;
        string s;
        cin >> s;

        GameEngine *g2 = new GameEngine();
        CommandProcessing *c = new CommandProcessing();
        Deck *adeck2 = new Deck();
        g2->deck = adeck2;
        g2->deck->initial_deck();

        Command loadmap = Command("loadmap<Iceland.map>");
        loadmap.saveEffect("maploaded");
        c->gameCommands.push_back(loadmap);
        g2->setStateName(new string("maploaded"));
        g2->readCommandList(c);
        c->gameCommands.clear();


        Command validatemap = Command("validatemap");
        validatemap.saveEffect("validatemap");
        c->gameCommands.push_back(validatemap);
        g2->setStateName(new string("mapvalidated"));
        g2->readCommandList(c);
        c->gameCommands.clear();


        
        Command addplayer = Command("addplayer<AggressivePlayer1>");
        addplayer.saveEffect("playersadded");
        c->gameCommands.push_back(addplayer);
        g2->setStateName(new string("playersadded"));
        g2->readCommandList(c);
        c->gameCommands.clear();

        Command addplayer2 = Command("addplayer<BenevolentPlayer1>");
        addplayer2.saveEffect("playersadded");
        c->gameCommands.push_back(addplayer2);
        g2->setStateName(new string("playersadded"));
        g2->readCommandList(c);
        c->gameCommands.clear();

        Command addplayer3 = Command("addplayer<CheaterPlayer1>");
        addplayer3.saveEffect("playersadded");
        c->gameCommands.push_back(addplayer3);
        g2->setStateName(new string("playersadded"));
        g2->readCommandList(c);
        c->gameCommands.clear();

        Command start = Command("gamestart");
        start.saveEffect("assignreinforcement");
        g2->setStateName(new string("assignreinforcement"));
        c->gameCommands.push_back(start);
        g2->readCommandList(c);
        c->gameCommands.clear();
        

    }
        


}