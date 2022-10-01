#include "Map.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map> //reffering to the data structure 
Territory::Territory(string name, string continent){
    this->name = new string(name);
    this->continent = new string(continent);
    this->visited = false;
}
Territory::Territory(const Territory &obj){
    this->name = new string(*(obj.name));
    this->continent = new string(*(obj.continent));
    this->visited = false;
    this->neighbours = obj.neighbours;
}
Territory::~Territory(){
}
Territory& Territory::operator=(const Territory &t){
    this->name = new string(*(t.name));
    this->continent = new string(*(t.continent));
    this->neighbours = t.neighbours;
    this->visited = t.visited;
    return *this;
}
ostream& operator << (ostream &out, Territory territory) {
    out << "Territory Name: " << territory.getName() << " Continent: " << territory.getContinent();
    return out;
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
Continent::Continent(const Continent &continent){
    this->name = new string(*continent.name);
    this->continent_members = continent.continent_members;
}
Continent& Continent::operator=(const Continent &continent){
    this->name = new string(*continent.name);
    this->continent_members = continent.continent_members;
    return *this;
}
ostream& operator <<(ostream &out, Continent continent){
    out << "Continent Name: " << continent.getName();
    return out;
}
string Continent::getName(){
    return *name;
}
Map::Map(vector<Territory*> t, vector<Continent*> c){
    this->territories = t;
    this->continents = c;
}
Map::Map(const Map &map){
    this->territories = map.territories;
    this->continents = map.continents;
}
Map& Map::operator=(const Map &map){
    this->territories = map.territories;
    this->continents = map.continents;
    return *this;
}
ostream& operator<<(ostream &out, Map map){
    for(int i = 0; i < map.getContinents().size(); i++){
        out << "Continent name: " << map.getContinents()[i]->getName();
    }
    for(int i = 0; i < map.getTerritories().size(); i++){
        out << "Territory name: " << map.getTerritories()[i]->getName();
    }
    return out;
}
vector<Territory*> Map::getTerritories(){
            return this->territories;
        }
vector<Continent*> Map::getContinents(){
    return continents;
}
MapLoader::MapLoader(){
}
Map MapLoader::readMapFile(string fileName){
    cout << "--LOADING MAP:  " << fileName << "--"<<endl;
    ifstream input(fileName);
    vector<Territory*> territories;
    vector<Continent*> continents;
    string delimiter; 
    int found = -1;
    string line;
    while(getline(input,line)){           
        if(line.length() == 1) continue;
        found = line.find("[Continents]");
        if(found != -1){
            delimiter = "=";
            while(getline(input, line)){
                if(line.find("[Territories]") != -1){
                    break;
                }
                else if(line.length() == 1){
                    continue;
                }
                else{
                    cout << "Loading Continent: " << line.substr(0, line.find(delimiter)) <<endl;
                    continents.push_back(new Continent(line.substr(0, line.find(delimiter))));
                }
            }
        }
        if(line.length() == 1) continue;

        found = line.find("[Territories]");
        string territory;
        if(found != -1){
            while(getline(input, line)){
                if(line.length() == 1) continue;
                int index;
                delimiter = ",";
                territory = line.substr(0, line.find(delimiter));
                string continent;
                int num1 = nthSubstr(3, line, ",");
                int num2 = nthSubstr(4, line, ",");
                string newLine = line.substr(num1 + 1, (num2-num1-1));
                for(int i = 0 ;i < continents.size(); i++) {
                      if(newLine.find(continents[i]->getName()) != -1){
                          continent = continents[i]->getName();
                          index = i;
                          cout << "Loading Territory: " << territory << endl;
                          Territory* t = new Territory(territory, continent);
                          territories.push_back(t);
                          continents[index]->continent_members.push_back(t);
                          break;
                      }
                }
            }
        }
    }
    string line2 = "";
    input.clear();
    input.seekg(0, input.beg);
    found = -1;
    cout << "Finding Territory Neighbours...." << endl;
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
Map::Map(){

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
        //check if map is connected
        if(territories[i]->visited == false){
            territories[i]->visited = true;
            num++;
            if(territories[i]->getNeighbours().size() == 0){
                cout << "map is not connected" << endl;
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
    //check if Continents are connected subgraphs
    //for each continent
    for(size_t i = 0; i < this->getContinents().size(); i++){
        string continent_name = this->getContinents()[i]->getName();
        //check the members of the continent
        for(int j = 0; j < this->getContinents()[i]->continent_members.size(); j++){
            Territory* current_territory = this->getContinents()[i]->continent_members[j];
            if(current_territory->getNeighbours().size() == 0) {
                cout << "Map is not a conntected sub-graph" << endl; 
                return false; 
                }else{
                bool hasNeighbour = false;
                for(int k = 0; k < current_territory->neighbours.size(); k++){
                    if(current_territory->getNeighbours()[k]->getContinent() == continent_name){
                        hasNeighbour = true;
                        break;
                    }
                }
                if(hasNeighbour == false){
                    cout << "Map is not a conntected sub-graph" << endl; 
                    return false;
                }
            }
        }
    }
    //check each country(territory) belongs to only one continent
    map<string,string> m;
    for(int i = 0; i < this->getContinents().size(); i++){
        string continent_name = this->getContinents()[i]->getName();
        for(int j = 0; j < this->getContinents()[i]->continent_members.size(); j++){
            m.insert(pair<string, string>(this->getContinents()[i]->continent_members[j]->getName(), continent_name));
        }
    }
    for (int i = 0; i < this->getTerritories().size(); i++){
            if (m.count(this->getTerritories()[i]->getName()) > 1) {
                cout << "Continent" << this->getTerritories()[i]->getName() << "does not have unique territories" << endl; 
                return false;
            }
    }
    if(num == this->getTerritories().size()) {
        return true;
    }else{
        cout<< "Map is not connected1" <<endl;
        return false;
    }
}
int nthSubstr(int n, const string& s, const string& p) {
            string::size_type i = s.find(p);     

            int j;
            for (j = 1; j < n && i != string::npos; ++j){
                i = s.find(p, i+1); 
            }
            if (j == n)
                return(i);
            else
                return(s.length());
}

