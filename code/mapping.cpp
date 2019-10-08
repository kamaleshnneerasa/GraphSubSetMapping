#include <iostream>
#include <fstream>

using namespace std;

int main() {
  /* code */
  ifstream inFile("./values.txt");
  int n, m;
  if (inFile.is_open()){
    inFile >> n; inFile >> m;
    inFile.close();
    ifstream satoutput("./../test.satoutput");
    ofstream output("./../output.txt");
    string sat;
    getline(satoutput, sat);
    if (sat.compare("SAT") == 0){
      int temp;
      for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
          satoutput >> temp;
          if (temp > 0){
            output << i+1 << " " << j+1 << "\n";
          }
        }
      }
  }else{
    output << 0 << "\n";
  }
    satoutput.close();
    output.close();
  }
  return 0;
}
