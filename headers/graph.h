#ifndef graph_h
#define graph_h
#include <vector>
#include <iostream>

using namespace std;

class Graph{
public:
	int numVertices;
	vector<int>* adjList;
	//Constructor
	Graph(int numVertices){
		this->numVertices = numVertices;
		this->adjList = new vector<int>[numVertices];
		for(int i=0;i<numVertices;i++){
			vector<int> temp;
			adjList[i] = temp;
		}
	}
	//Adds an edge from src to dst
	void addEdge(int src,int dst){
		adjList[src].push_back(dst);
	}
	//Checks if there is an edge from src to dst
	bool isEdge(int src,int dst){
		vector<int> neighbours = adjList[src];
		int size = neighbours.size();
		for(int i=0;i<size;i++){
			if(neighbours[i]==dst) return true;
		}
		return false;
	}
	//Returns all the neighbours of the src
	vector<int> neighbours(int src){
		return adjList[src];
	}
	vector<pair<int,int> > edgeList(){
		vector<pair<int,int> > res;
		for(int i=0;i<numVertices;i++){
			for(int j=0;j<adjList[i].size();j++){
				pair<int,int> p;
				p.first = i; p.second = adjList[i][j];
				res.push_back(p);
			}
		}
		return res;
	}
};

#endif
