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
					srcList1.push_back(src-1);   //Assuming that nodes start at 0 and not 1
					dstList1.push_back(dst-1);
					if(numVertices1<src) numVertices1 = src;
					if(numVertices1<dst) numVertices1 = dst;
				}
				else{
					srcList2.push_back(src-1);
					dstList2.push_back(dst-1);
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
	vector<string> res1 = oneOne(numVertices2,numVertices1);
	vector<string> res2 = edgeConstraint(gEmail,gPhone);
    for(int i=0;i<res2;i++){
    	res1.push_back(res2[i]);
    }

    int numVariables = gEmail.size()*gPhone.size();
    int numConstraints = res1.size();

    ofstream outFile("test.satinput");
    outFile<<"p"<<" cnf "<<numVariables<<" "<<numConstraints<<"\n";
    for(int i=0;i<res1.size();i++){
    	outFile<<res[i]<<" 0\n";
    }

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

vector<string> edgeConstraint(Graph gEmail,Graph gPhone){
	vector<string> res;
	int n = gEmail.size();int m = gPhone.size(); 
	vector<vector<int>> eList = gEmail.edgeList;
	vector<vector<int>> pList = gPhone.edgeList;
	for(int i=0;i<eList.size();i++){
		int v1 = eList[i].first; int v2 = eList[i].second;
		vector<pair<int,int>> temp;
		for(int j=0;j<pList.size();j++){
			int v1Dash = pList[j].first; int v2Dash = pList[j].second;
			pair<int,int> andClause;
			andClause.first = v1*m+(v1Dash+1);  //We are assuming that the graph has nodes from 0 to numVertices-1.So we have to add a +1
			andClause.second = v2*m+(v2Dash+1);
			temp.push_back(andClause);
		}
		vector<string> res1;
		if(temp.size()>0) res1 = getCnf(temp);
		for(int i=0;i<res1.size();i++){
			res.push_back(res1[i]);
		}
	}
	return res;
}

vector<string> getCnf(vector<pair<int,int>> clause){
	vector<string> res;
	if(clause.size()==1){
		pair<int,int> p = clause[0];
		string s1 = to_string(p.first);
		string s2 = to_string(p.second);
		res.push_back(s1); res.push_back(s2);
		return res;
	}
	pair<int,int> p = clause[clause.size()-1];
	string s1 = to_string(p.first);
	string s2 = to_string(p.second);
	clause.pop_back();
	vector<string> temp = getCnf(clause);
	for(int i=0;i<temp.size();i++){
		res.push_back(temp[i]+" "+s1);
		res.push_back(temp[i]+" "+s2);
	}
	return res;
}
