#include <iostream>
#include <vector>
using namespace std;


class Territory{
    private:
        string name;
        string continent;
        
    public:
        vector<Territory *> neighbours;
        Territory(string name, string continent); 
        Territory (const Territory &obj);
        ~Territory();
        string getName();
        void setName(string name);
        string getContinent();
        void setContinent(string continent);
        vector<Territory *> getNeighbours();
};

class Map
{
    private:
        vector<Territory*> territories;
        //vector<Continents*> continents;

    public:
        bool validate();

};

class MapLoader{
    public:
        MapLoader();

        void readMapFile(string fileName);
        vector<Territory*> findNeighbours(string s, vector<Territory*>);


};