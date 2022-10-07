#include "Map.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
#include <fstream>
#include <vector>
void testLoadMaps(){
     MapLoader* m = new MapLoader();
     // insert file name here with correct path
    string maps[5] = {".mapFiles/Middle Earth.ma2p", ".mapFiles/Africa.map", ".mapFiles/Alabama.map", ".mapFiles/Asia.map"};
    for(int i = 0; i < 4; i++){
      Map m1;
      m1 = m->readMapFile(maps[i]);
      if(m1.getTerritories().size() == 0) continue;

      if(m1.validate()){
         cout << "map is valid" << endl;
         cout << endl;
      }else{
         cout << "map is invalid" << endl;
      }
    }
 }

