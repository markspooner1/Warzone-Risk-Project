#include <iostream>
#include <vector>
using namespace std;


class Territory{
    private:
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

    public:
        bool validate();

};

class MapLoader{
    public:

        void readMapFile(string fileName);
        string findTerritoriesContinet(string);

};