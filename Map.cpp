#include "Map.h"
#include <fstream>


Territory::Territory(string name, string continent){
    this->name = name;
    this->continent = continent;
}

void MapLoader::readMapFile(string fileName){
    ifstream input("Alberta.map");
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
                    cout << name << endl;
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
                Territory *t1 = new Territory(territory, continent);
                territories.push_back(t1);
            
            }
        }
    }
}
string MapLoader::findTerritoriesContinet(string){


}

