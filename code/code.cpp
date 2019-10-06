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
	//Assumption Xij = i*m+j; number of vars = n*m; number of constrs = n*(Mc2+1);
	vector<string> res = oneOne(numVertices2,numVertices1);
}

//
vector<string> oneOne(int n, int m){
	string str,constr;
	vector<string> res;
	for(int i=0;i<n;i++){
		vector<string> temp;
		constr = "";  //This constraint tells that atleast one value must be true
		for(int j=1;j<=m;j++){
			str = to_string(i*m+j);
			temp.push_back(str);
			constr = constr+str+" ";
		}
		res.push_back(constr.substr(0,constr.length()-1));
		//These constraints are for ensuring no more than one constraint is true
		for(int i=0;i<m;i++){
			for(int j=i+1;j<m;j++){
				res.push_back("-"+temp[i]+" -"+temp[j]);
			}
		}
	}
	return res;
}

vector<string> edgeConstraint(Graph gEmail,Graph gPhone,int offset){
	int currVal = offset;
	vector<vector<int>> eList = gEmail.edgeList;
	vector<vector<int>> pList = gPhone.edgeList;
	
}

