#pragma once
#include <iostream>
using std::cout;
using std::string;
using std::ostream;
#include <vector>
using std::vector;
class player;
class Territory{
    private:
        player* owner;
        string* name;
        string* continent;
        int* army_units;
    public:
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
        bool visited;
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
        int DFS(Territory *t, int num);
};
class MapLoader{
    private:
        string filename;
         //Helper function to find neighbours while loading map file
        vector<Territory*> findNeighbours(string s, vector<Territory*>);
    public:
        Map readMapFile(string fileName);
        MapLoader(string filname);
        MapLoader();
       
};
int nthSubstr(int n, const string& s, const string& p);
void testLoadMaps();