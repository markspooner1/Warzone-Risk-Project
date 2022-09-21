#include <iostream>
#include <vector>
using namespace std;


class Territory{
    public:
        string name;
        string continent;
        vector<Territory*> neighbours;
    public:
        
        Territory(string name, string continent); 
        Territory (const Territory &obj);
        ~Territory();

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