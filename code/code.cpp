#include <iostream>
#include "graph.h"

using namespace std;
int main(){
	Graph g1 = Graph(10);
	g1.addEdge(1,2);
	g1.addEdge(2,5);
	g1.addEdge(1,7);
	vector<int> l = g1.neighbours(1);
	int size = l.size();
	for (int i=0; i<size; i++){
		cout << l[i] << endl;
	}
}
