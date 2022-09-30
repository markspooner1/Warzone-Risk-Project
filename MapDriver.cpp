#include "Map.cpp"
void testLoadMaps(){
}
int main(){
    MapLoader m;
    Map m1 = m.readMapFile(".mapFiles/Asia.map");
    if(m1.validate()){
        cout << "map is valid" << endl;
    }
}
