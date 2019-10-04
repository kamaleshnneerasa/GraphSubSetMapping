#include <iostream>

using namespace std;

class Graph{
public:
	int numVertices;
	vector<vector<int>> adjList;
	//Constructor
	Graph(int numVertices){
		this->numVertices = numVertices;
		for(int i=0;i<numVertices;i++){
			vector<int> temp;
			adjList.pushback(temp);
		}
	}
	//Adds an edge from src to dst
	void addEdge(int src,int dst){
		adjList[src].pushback(dst);
	}
	//Checks if there is an edge from src to dst
	bool isEdge(int src,int dst){
		vector<int> neighbours = adjList[src];
		for(int i=0;i<neighbours.size();i++){
			if(neighbours[i]==dst) return true;
		}
		return false;
	}
	//Returns all the neighbours of the src
	vector<int> neighbours(int src){
		return adjList[src];
	}
}
int main(){

}