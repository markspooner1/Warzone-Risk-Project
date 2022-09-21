#include "Map.h"
#include <fstream>
#include <algorithm>
#include <sstream>

Territory::Territory(string name, string continent){
    this->name = name;
    this->continent = continent;
}
Territory::~Territory(){}

MapLoader::MapLoader(){

}
void MapLoader::readMapFile(string fileName){
    ifstream input(fileName);
    string line;
    vector<Territory*> territories;
    vector<string> continents;
    string delimiter; 
    int found = -1;
    while(getline(input,line)){
        found = line.find("[Continents]");
        if(found != -1){
            delimiter = "=";
            while(getline(input, line)){
                if(line.find("[") != -1 ){
                    break;
                }
                else{
                    string name = line.substr(0, line.find(delimiter));
                    continents.push_back(name);
                }
            }
        }
        found = line.find("[Territories]");
        if(found != -1){
            while(getline(input, line)){
                delimiter = ",";
                string territory = line.substr(0, line.find(delimiter));
                string continent;
                for(std::size_t i = 0; i < continents.size(); i++) {
                      if(line.find(continents[i]) != -1){
                          continent = continents[i];
                          break;
                      }
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
        string current = territories[territoryNum]->name;

        found = line2.find(current);
        if(found != -1){
            territories[territoryNum]->neighbours = findNeighbours(line2, territories);
            territoryNum++;

        }
    }
    for(int i = 0; i < territories.size(); i++){
        cout << "neighbours for territory " << territories[i]->name << endl;
        for(int j = 0; j < territories[i]->neighbours.size(); j++){
            cout << territories[i]->neighbours[j]->name << endl;
        }
        cout << "---------------" <<endl;
    } 
}
vector<Territory*> MapLoader::findNeighbours(string s, vector<Territory*> te){
    vector<Territory*> neighbours;
    int commas = 0;
    int ptr = 0;
    while(commas != 4){
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
 
             if(substr.find(te[i]->name) != -1){
                 neighbours.push_back(te[i]);
                 break;
             }
         }
        
    }
    return neighbours;
}

int main(){
    MapLoader m;
    m.readMapFile("Alberta.map");

}
