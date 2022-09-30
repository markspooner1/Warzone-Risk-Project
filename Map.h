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
        Territory& operator=(const Territory& t);
        friend ostream& operator<<(ostream& out, Territory territory);
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
        Continent(const Continent &obj);
        Continent& operator=(const Continent &c);
        friend ostream& operator<<(ostream& out, Continent continent);
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
        Map();
        Map(vector<Territory*> t, vector<Continent*> c);
        Map(const Map &map);
        Map& operator = (const Map &map);
        friend ostream& operator<<(ostream& out, Map map);
        bool validate();
        vector<Territory*> getTerritories();
        vector<Continent*> getContinents();
        void reset();
};

class MapLoader{
    public:
        Map readMapFile(string fileName);
        MapLoader();
        //Helper function to find neighbours while loading map file
        vector<Territory*> findNeighbours(string s, vector<Territory*>);
};
int nthSubstr(int n, const string& s, const string& p);