#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;
int main(){
	string line;
	int numVertices1 = 0,numVertices2=0; bool firstGraph = true;
	vector<int> srcList1,srcList2,dstList1,dstList2;  //(srcList1,dstList1)----> gPhone;(srcList2,srcList2)---> gEmail
	ifstream inFile("input.txt");
	if(inFile.is_open()){
		int src,dst,temp;
		while(!inFile.eof()){
			// temp = s.find(" ");              //s.find(c) Finds the index of first occurance of c
			// src = stoi(line.substring(0,temp));    //s.substring(startInd,len) Finds substring of s starting at startInd and Length = len
			// dst = stoi(line.substring(temp+1,line.length()-(temp+1)));
			// //Checking for the end of first graph in the if-condition
			inFile >> src;
			inFile >> dst;
			if(src>0 && dst>0){
				if(firstGraph == true){
					srcList1.push_back(src);
					dstList1.push_back(dst);
					if(numVertices1<src) numVertices1 = src;
					if(numVertices1<dst) numVertices1 = dst;
				}
				else{
					srcList2.push_back(src);
					dstList2.push_back(dst);
					if(numVertices2<src) numVertices2 = src;
					if(numVertices2<dst) numVertices2 = dst;
				}
			}
			else firstGraph = false;
		}
	}
	else cout<<"Unable to open the file";
	Graph gPhone(numVertices1);
	Graph gEmail(numVertices2);
	int size = srcList1.size();
	for(int i=0;i<size;i++){
		gPhone.addEdge(srcList1[i]-1,dstList1[i]-1);
	}
	size = srcList2.size();
	for(int i=0;i<size;i++){
		gEmail.addEdge(srcList2[i]-1,dstList2[i]-1);
	}

	vector<int> l = gPhone.neighbours(0);
	size = l.size();
	for (int i=0; i<size; i++){
		cout << l[i]+1<< endl;
	}

	l = gPhone.neighbours(4);
	size = l.size();
	for (int i=0; i<size; i++){
		cout << l[i]+1<<endl;
	}

	l = gEmail.neighbours(4);
	size = l.size();
	for (int i=0; i<size; i++){
		cout << l[i]+1<<endl;
	}

	l = gEmail.neighbours(0);
	size = l.size();
	for (int i=0; i<size; i++){
		cout << l[i]+1<<endl;
	}
}
