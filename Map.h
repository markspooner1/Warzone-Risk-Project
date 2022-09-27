#include <iostream>
#include <vector>
using namespace std;


class Territory{
    private:
        string* name;
        string* continent;
        
        
    public:
        bool visited;
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
class Continent{
    public:
        Continent(string name); 
        string getName();
        vector<Territory*> continent_members;
    private:
        string* name;
       
};
     
class Map
{
    private:
        vector<Territory*> territories;
        vector<Continent*> continents;

    public:
        Map(vector<Territory*> t, vector<Continent*> c);
        ~Map();
        bool validate();
        //test function
        void printTerritory(vector<Territory*> t);
        void printContinents(vector<Continent*> continents);
        vector<Territory*> getTerritories();
        vector<Continent*> getContinents();
};

class MapLoader{
    public:
        MapLoader();

        Map readMapFile(string fileName);
        //Helper function to find neighbours while loading map file
        vector<Territory*> findNeighbours(string s, vector<Territory*>);
};