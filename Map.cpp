#include "Map.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::ostream;

#include <fstream>
using std::ifstream;
#include <sstream>
using std::stringstream;
#include <string>
#include <map>
using std::map;
using std::pair;
//https://www.softwaretestinghelp.com/cpp-dfs-program-to-traverse-graph/ https://www.youtube.com/watch?v=7fujbpJ0LB4&t=381s used to help implement connectivity check

//Territory, 2 parameter constructor
Territory::Territory(string name, string continent){
    this->name = new string(name);
    this->continent = new string(continent);
    this->visited = false;
}
//Territory copy constructor
Territory::Territory(const Territory &obj){
    this->name = new string(*(obj.name));
    this->continent = new string(*(obj.continent));
    this->visited = false;
    this->neighbours = obj.neighbours;
}
// TODO 
Territory::~Territory(){
}
//Territory assignment operatior
Territory& Territory::operator=(const Territory &t){
    this->name = new string(*(t.name));
    this->continent = new string(*(t.continent));
    this->neighbours = t.neighbours;
    this->visited = t.visited;
    return *this;
}
//Territory stream insertion operator
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
//Continent one parameter constructor
Continent::Continent(string name){
    this->name = new string(name);
}
//Continent copy constructor
Continent::Continent(const Continent &continent){
    this->name = new string(*continent.name);
    this->continent_members = continent.continent_members;
}
//Continent assignment operator
Continent& Continent::operator=(const Continent &continent){
    this->name = new string(*continent.name);
    this->continent_members = continent.continent_members;
    return *this;
}
//Continent stream insertion operatpr
ostream& operator <<(ostream &out, Continent continent){
    out << "Continent Name: " << continent.getName();
    return out;
}
string Continent::getName(){
    return *name;
}
// Map 2 parameter constructor
Map::Map(vector<Territory*> t, vector<Continent*> c){
    this->territories = t;
    this->continents = c;
}
// Map copy constructor
Map::Map(const Map &map){
    this->territories = map.territories;
    this->continents = map.continents;
}
// Map assignment operator
Map& Map::operator=(const Map &map){
    this->territories = map.territories;
    this->continents = map.continents;
    return *this;
}
// Map stream insertion operator
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
MapLoader::MapLoader(string filename){
    this->filename = filename;
}
//Method to read .map files and create Map
Map MapLoader::readMapFile(string fileName){
    cout << "--LOADING MAP:  " << fileName << "--"<<endl;
    cout << "-----------------" <<endl;
    ifstream input(fileName);
    vector<Territory*> territories;
    vector<Continent*> continents;
    if(fileName.substr(nthSubstr(2, fileName, "."), 4) != ".map"){
        cout << "Invalid filetype" << endl;
        cout << "Couldnt create map" << endl;
        return Map(territories, continents);
    }
    string delimiter; 
    int found = -1;
    string line;
    cout << "Loading Continents..." << endl;
    cout << "Loading Territories.." << endl;
    while(getline(input,line)){   
        //If empty line, continue,
        //read until start of continents found       
        if(line.length() == 1) continue;
        if(line.find("[Continents]") != -1){
            delimiter = "=";
            while(getline(input, line)){
                if(line.find("[Territories]") != -1){
                    break;
                }
                else if(line.length() == 1){
                    continue;
                }
                else{
                    //using the = sign as a dilimeter to insert continents into the vector
                    continents.push_back(new Continent(line.substr(0, line.find(delimiter))));
                }
            }
        }
        if(line.length() == 1) continue;
        //read until start of territories found
        string territory;
        if(line.find("[Territories]") != -1){
            while(getline(input, line)){
                if(line.length() == 1) continue;
                int index;
                delimiter = ",";
                territory = line.substr(0, line.find(delimiter));
                //creating a substring of the current line to find the respective continent for each territory
                //continent of each territory is always between 3rd and 4th commas 
                string continent;
                int num1 = nthSubstr(3, line, ",");
                int num2 = nthSubstr(4, line, ",");
                string newLine = line.substr(num1 + 1, (num2-num1-1));
                //find the continent that we just found through the above method and create a new territory
                for(int i = 0 ;i < continents.size(); i++) {
                      if(newLine.find(continents[i]->getName()) != -1){
                          continent = continents[i]->getName();
                          index = i;
                          Territory* t = new Territory(territory, continent);
                          territories.push_back(t);
                          continents[index]->continent_members.push_back(t);
                          break;
                      }
                }
            }
        }
    }
    //Reopen the file to find territory neighbours
    string line2 = "";
    input.clear();
    input.seekg(0, input.beg);
    found = -1;
    cout << "Finding Territory Neighbours...." << endl;
    int territoryNum = 0;
    while(getline(input,line2)){
        //current territory that we want to find neighbours for
        string current = territories[territoryNum]->getName();
        found = line2.find(current);
        //find the line that contains the territory
        if(found != -1){
            //process the line to find the territories neighbours
            territories[territoryNum]->neighbours = findNeighbours(line2, territories);
            territoryNum++;
        }
    }
    
    return Map(territories, continents);
}
Map::Map(){
}
MapLoader::MapLoader(){
}
vector<Territory*> MapLoader::findNeighbours(string s, vector<Territory*> te){
    vector<Territory*> neighbours;
    int commas = 0;
    int ptr = 0;
    string terr = s.substr(nthSubstr(4, s, ","), s.find('\n'));
    stringstream ss(terr);
    // split the line by commas to find every neighbouring territory
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
int Map::DFS(Territory *t, int num){
    vector<Territory*> t2 = t->getNeighbours();
    for(size_t j = 0; j < t2.size(); j++){
        if(t2[j]->visited == false){
            t2[j]->visited = true;
            num = DFS(t2[j], num);
        }
    }
    return num + 1;
}
bool Map::validate(){
    // Check if map is connected 
    int num = 0;
    bool connected = false;
    //check connectivity by performing DFS on each territory, ignoring those already visited 
    //num is an int to check if all territories were visited
    for(size_t i = 0; i < this->getTerritories().size(); i++){
        if(territories[i]->visited == false){
            territories[i]->visited = true;
            if(territories[i]->getNeighbours().size() == 0) {
                return false;
            }
            num = DFS(territories[i], num);
        }
        if(num == this->getTerritories().size()){
            connected = true;
            break;
        }
    }
    if(!connected) {
        return false;
    }
    //Check if map is connected sub-graph
    for(size_t i = 0; i < this->getContinents().size(); i++){
        string continent_name = this->getContinents()[i]->getName();
        //for each member of the continent
        for(size_t j = 0; j < this->getContinents()[i]->continent_members.size(); j++){
            Territory* current_territory = this->getContinents()[i]->continent_members[j];
            // if a territory in a continent has no neighbours then the map is not a connected subgraph
            if(current_territory->getNeighbours().size() == 0) {
                cout << "Map is not a conntected sub-graph" << endl; 
                return false; 
                }
            //if a territory does have a neighbour, make sure it is apart of its continent, otherwise the continent is not a connected subgraph
            else{
                bool hasNeighbour = false;
                for(size_t k = 0; k < current_territory->neighbours.size(); k++){
                    if(current_territory->getNeighbours()[k]->getContinent() == continent_name){
                        hasNeighbour = true;
                        break;
                    }
                }
                if(hasNeighbour == false){
                    cout << "Map is not a conntected sub-graph " << current_territory->getName() << " has no neighbour within its continent"<< endl; 
                    return false;
                }
            }
        }
    }
    //check each country(territory) belongs to only one continent
    // for each continent, insert its members into a map with the format <TerritoryName, ContinentName>
    map<string,string> m;
    for(size_t i = 0; i < this->getContinents().size(); i++){
        string continent_name = this->getContinents()[i]->getName();
        for(size_t j = 0; j < this->getContinents()[i]->continent_members.size(); j++){
            m.insert(pair<string, string>(this->getContinents()[i]->continent_members[j]->getName(), continent_name));
        }
    }
    //If a territory appears more than once in the map, a territory does not belong to only one continent
    for (size_t i = 0; i < this->getTerritories().size(); i++){
            if (m.count(this->getTerritories()[i]->getName()) > 1) {
                cout << this->getTerritories()[i]->getName()<< " does not belong to one contient" << endl; 
                return false;
            }
    }
    return true;
}
//free function that finds nth occurence of a string
//reference: https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s11.html
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

