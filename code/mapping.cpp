#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
  /* code */
  ifstream inFile("values.txt");
  int n, m;
  string output_file;
  output_file = argv[1];
  if (inFile.is_open()){
    inFile >> n; inFile >> m;
    inFile.close();
    ifstream satoutput(output_file+".satOutput");
    ofstream output(output_file+".mapping");
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
