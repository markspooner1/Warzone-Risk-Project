#include <iostream>
#include <vector>
using namespace std;


vector<string> split(string str, string deli)
{
    vector<string> list;
    int start = 0;
    int end = str.find(deli);
    while (end != -1) {
      list.push_back(str.substr(start, end - start)); 
        start = end + deli.size();
        end = str.find(deli, start);
    }
      list.push_back(str.substr(start, end - start)); 
   return list;
}
int main()
{
   string wod = "OrderDeployType, ID, num_of_units, ,name, target";
      vector<string> list;
      list = split(wod, ",");
       for(int i=0;i<list.size();i++){
        cout << list[i] << "\n";
       }

   
    

    return 0;
}
