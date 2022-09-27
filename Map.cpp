#include "Map.h"
#include <fstream>
#include <sstream>

Territory::Territory(string name, string continent){
    this->name = new string(name);
    this->continent = new string(continent);
    this->visited = false;
}
Territory::~Territory(){

}
string Territory::getName(){
            return *name;
        }
void Territory::setName(string name){
            this->name = &name;
        }
string Territory::getContinent(){
            return *continent;
        }
void Territory::setContinent(string continent){
            this->continent = &continent;
        }
 vector<Territory*> Territory:: getNeighbours()
        {
            return this->neighbours;
        }
Continent::Continent(string name){
    this->name = new string(name);
}
string Continent::getName(){
    return *name;
}
Map::Map(vector<Territory*> t, vector<Continent*> c){
    this->territories = t;
    this->continents = c;
}
Map::~Map(){

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

vector<Continent*> Map::getContinents(){
    return continents;
}
MapLoader::MapLoader(){
}
Map MapLoader::readMapFile(string fileName){
    
    ifstream input(fileName);
    vector<Territory*> territories;
    vector<Continent*> continents;
    string delimiter; 
    int found = -1;
    string line;
    while(getline(input,line)){
        found = line.find("[Continents]");
        if(found != -1){
            delimiter = "=";
            while(getline(input, line)){
                if(line.find("[") != -1){
                    break;
                }
                else if(line.find("=") == -1){
                    continue;
                }
                else{
                    continents.push_back(new Continent(line.substr(0, line.find(delimiter))));
                }
            }
        }
        found = line.find("[Territories]");
        string territory;
       
        if(found != -1){
            while(getline(input, line)){
                int index;
                delimiter = ",";
                territory = line.substr(0, line.find(delimiter));
                string continent;
                for(int i = 0 ;i < continents.size(); i++) {
                      if(line.find(continents[i]->getName()) != -1){
                          continent = continents[i]->getName();
                          index = i;
                          break;
                      }
                }
                Territory* t = new Territory(territory, continent);
                territories.push_back(t);
                continents[index]->continent_members.push_back(t);
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
        if(ptr > s.length()) return neighbours;
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

bool Map::validate(){
    int num = 0;
    for(size_t i = 0; i < this->getTerritories().size(); i++){
        if(territories[i]->visited == false){
            territories[i]->visited = true;
            num++;
            //if a territory has no neighbours, not connected
            cout<< territories[i]->getName() << endl;
            cout << territories[i]->getNeighbours().size() << endl;
            if(territories[i]->getNeighbours().size() == 0){
                return false;
            }
            else{
                for(size_t j = 0; j < this->getTerritories()[i]->getNeighbours().size(); j++){
                    if(this->getTerritories()[i]->getNeighbours()[j]->visited == false){
                        this->getTerritories()[i]->getNeighbours()[j]->visited = true;
                        num++;
                    }
                }
            }
        }
    }
    return num == this->getTerritories().size();
   
    
}
int main(){
    MapLoader m;
    Map m1 = m.readMapFile("Maps/Asia.map");
}
