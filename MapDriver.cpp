#include "Map.cpp"
#include <iostream>
#include <fstream>
#include <vector>
void testloadmaps(){
     MapLoader* m = new MapLoader();
     // insert file name here with correct path
    Map m1 = m->readMapFile(".mapFiles/Asia.map");
    if(m1.validate()){
        cout << "map is valid" << endl;
    }
}
int main(){
   testloadmaps();
}
