#include <iostream>
#include <fstream>
#include <bits/stdc++>
#include <string>

#include "graph.h"

using namespace std;
int main(){
	String line; 
	int numVertices1 = 0,numVertices2=0; bool firstGraph = true;
	vector<int> srcList1,srcList2,dstList1,dstList2;  //(srcList1,dstList1)----> gPhone;(srcList2,srcList2)---> gEmail
	ifstream inFile("input.txt");
	if(inFile.is_open()){
		int src,dst,temp;
		while(getline(inFile,line)){
			temp = s.find(" ");              //s.find(c) Finds the index of first occurance of c
			src = stoi(line.substring(0,temp));    //s.substring(startInd,len) Finds substring of s starting at startInd and Length = len
			dst = stoi(line.substring(temp+1,line.length()-(temp+1)));
			//Checking for the end of first graph in the if-condition
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
	for(int i=0;i<srcList1.size();i++){
		gPhone.addEdge(srcList1[i],dstList1[i]);
	}
	for(int i=0;i<srcList2.size();i++){
		gEmail.addEdge(srcList2[i],dstList2[i]);
	}
	//Assumption Xij = (i*m+j); Range of vars = (1-n*m); Number of Constraints = n*(Mc2+1)
	vector<String> res1 = oneOne(numVertices2,numVertices1);
}

//n-> Domain Size  m -> Codomain Size
vector<string> oneOne(int n, int m){
	string str,constr;
	vector<string> res;
	for(int i=0;i<n;i++){
		vector<string> temp;
		constr = "";
		for(int j=1;j<=m;j++){
			str = to_string(i*m+j);
			temp.push_back(str);
			constr = constr+str+" ";
		}
		res.push_back(constr.substr(0,constr.length()-1));
		for(int i=0;i<m;i++){
			for(int j=i+1;j<m;j++){
				res.push_back("-"+temp[i]+" -"+temp[j]);
			}
		}
	}
	return res;
}

/*
Graph g1 = Graph(10);
	g1.addEdge(1,2);
	g1.addEdge(2,5);
	g1.addEdge(1,7);
	vector<int> l = g1.neighbours(1);
	int size = l.size();
	for (int i=0; i<size; i++){
		cout << l[i] << endl;
	}
*/