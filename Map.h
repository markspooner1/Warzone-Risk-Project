#include <iostream>
#include <vector>
using namespace std;


class Territory{
    private:
        string* name;
        string* continent;
        bool visited = false;
        
    public:
        vector<Territory *> neighbours;
        Territory(string name, string continent); 
        Territory (const Territory &obj);
        ~Territory();
        string getName();
        void setName(string name);
        string getContinent();
        void setContinent(string continent);
        vector<Territory*> getNeighbours();
};
     
class Map
{
    private:
        vector<Territory*> territories;
        vector<string*> continents;

    public:
        Map(vector<Territory*> t, vector<string*> s);
        ~Map();
        bool validate();
        //test function
        void printTerritory(vector<Territory*> t);
        void printContinents(vector<string*> continents);
        vector<Territory*> getTerritories();
        vector<string*> getContinents();
};

class MapLoader{
    public:
        MapLoader();

        Map readMapFile(string fileName);
        //Helper function to find neighbours while loading map file
        vector<Territory*> findNeighbours(string s, vector<Territory*>);
};