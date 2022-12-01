#include "PlayerStrategy.h"
#include "GameEngine.h"
int main(){
    string input;
    cout << "1 for testPlayerStrategies\n2 for testTournament\n" <<endl;
    cin >> input;
    if(input == "1"){
        testPlayerStrategies();
    }else if(input == "2"){
        testTournament();
    }

}
