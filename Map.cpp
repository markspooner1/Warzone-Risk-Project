#include "Map.h"
#include <fstream>
#include <sstream>

Territory::Territory(string name, string continent){
    this->name = name;
}
Territory::~Territory(){

}
string Territory::getName(){
            return this->name;
        }
void Territory::setName(string name){
            this->name = name;
        }
string Territory::getContinent(){
            return this->continent;
        }
void Territory::setContinent(string continent){
            this->continent = continent;
        }
 vector<Territory*> Territory:: getNeighbours()
        {
            return this->neighbours;
        }
Map::Map(vector<Territory*> t, vector<string> s){
    this->territories = t;
    this->continents = s;
}
vector<Territory*> Map::getTerritories()
        {
            return this->territories;
        }
void Map::printTerritory(vector<Territory*> t){
    for(int i = 0; i < t.size(); i++){
        cout<< t[i]->getName() << endl;

    }
}
MapLoader::MapLoader(){
}
Map MapLoader::readMapFile(string fileName){
    
    ifstream input(fileName);
    vector<Territory*> territories;
    vector<string> continents;
    string delimiter; 
    int found = -1;
    string line;
    while(getline(input,line)){
        found = line.find("[Continents]");
        if(found != -1){
            delimiter = "=";
            while(getline(input, line)){
                if(line.find("[") != -1 ){
                    break;
                }
                else{
                    continents.push_back(line.substr(0, line.find(delimiter)));
                }
            }
        }
        found = line.find("[Territories]");
        string territory;
        if(found != -1){
            while(getline(input, line)){
                delimiter = ",";
                territory = line.substr(0, line.find(delimiter));
                string continent;
                for(std::size_t i = 0; i < continents.size(); i++) {
                      if(line.find(continents[i]) != -1){
                          continent = continents[i];
                          break;
                      }
                }         
                for(int i = 0; i < continents.size(); i++){
                }
                territories.push_back(new Territory(territory, continent));
            }
        }
    }
    string line2 = "";
    input.clear();
    input.seekg(0, input.beg);
    found = -1;
    int territoryNum = 0;
    while(getline(input,line2)){
        string current = territories[territoryNum]->getName();
        found = line2.find(current);
        if(found != -1){
            territories[territoryNum]->neighbours = findNeighbours(line2, territories);
            territoryNum++;
        }
    }
    return Map(territories, continents);
}
vector<Territory*> MapLoader::findNeighbours(string s, vector<Territory*> te){
    vector<Territory*> neighbours;
    int commas = 0;
    int ptr = 0;
    while(commas < 4){
        if(s[ptr] == ','){
            commas++;
        }
        ptr++;
    }
    string terr = s.substr(ptr, s.find('\n'));
    stringstream ss(terr);
    while(ss.good())
    {
        string substr;
        getline(ss, substr, ',');
        for(int i = 0; i < te.size(); i++){
             if(substr.find(te[i]->getName()) != -1){
                 neighbours.push_back(te[i]);
                 break;
             }
         }
    }
    return neighbours;
}

int main(){
    MapLoader m;
    Map m1 = m.readMapFile("Asia.map");
    m1.printTerritory(m1.getTerritories());

}
