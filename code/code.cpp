#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;

vector<string> getCnf(vector<pair<int,int>>);
vector<string> oneOne(int,int);
vector<string> edgeConstraint(Graph,Graph);
vector<string> edgeConstraint1(Graph,Graph);

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
					srcList1.push_back(src);   //Assuming that nodes start at 0 and not 1
					dstList1.push_back(dst);
					cout<<src<<" "<<dst<<"\n";
					if(numVertices1<src) numVertices1 = src;
					if(numVertices1<dst) numVertices1 = dst;
				}
				else{
					srcList2.push_back(src);
					dstList2.push_back(dst);
					cout<<src<<" "<<dst<<"\n";
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
	cout<<"Phone Starts here "<<srcList1.size()<<"\n";
	for(int i=0;i<size;i++){
		cout<<srcList1[i]-1 <<" "<<dstList1[i]-1<<"\n";
		gPhone.addEdge(srcList1[i]-1,dstList1[i]-1);
	}
	size = srcList2.size();
	cout<<"Email starts here "<<dstList2.size()<<"\n";
	for(int i=0;i<size-1;i++){
		cout<<srcList2[i]-1 <<" "<<dstList2[i]-1<<"\n";
		gEmail.addEdge(srcList2[i]-1,dstList2[i]-1);
	}

	/*vector<int> l = gPhone.neighbours(0);
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
	}*/
	//Assumption Xij = i*m+j; number of vars = n*m; number of constrs = n*(Mc2+1);
	cout<<"Hey1\n";
	vector<string> res1 = oneOne(numVertices2,numVertices1);
	for(int i=0;i<res1.size();i++) cout<<res1[i]<<"\n";
	cout<<"Hey2\n";
	vector<string> res2 = edgeConstraint1(gEmail,gPhone);
	cout<<"Hey3";
    for(int i=0;i<res2.size();i++){
    	res1.push_back(res2[i]);
    }
    cout<<"Hey4";
    int numVariables = numVertices2*numVertices1;
    int numConstraints = res1.size();

    ofstream outFile("../test.satinput");
    outFile<<"p"<<" cnf "<<numVariables<<" "<<numConstraints<<"\n";
    for(int i=0;i<res1.size();i++){
    	outFile<<res1[i]<<" 0\n";
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
		for(int i1=0;i1<m;i1++){
			for(int j1=i1+1;j1<m;j1++){
				res.push_back("-"+temp[i1]+" -"+temp[j1]);
			}
		}
	}
	return res;
}

vector<string> edgeConstraint(Graph gEmail,Graph gPhone){
	vector<string> res;
	int n = gEmail.numVertices; int m = gPhone.numVertices; 
	vector<pair<int,int>> eList = gEmail.edgeList();
	vector<pair<int,int>> pList = gPhone.edgeList();
	cout<<eList.size()<<"----------------------\n";
	for(int i=0;i<eList.size();i++) cout<<eList[i].first<<" "<<eList[i].second<<" \n";
	cout<<pList.size()<<"----------------------\n";
	for(int i=0;i<eList.size();i++){
		int v1 = eList[i].first; int v2 = eList[i].second;
		vector<pair<int,int>> temp;
		for(int j=0;j<pList.size();j++){
			int v1Dash = pList[j].first; int v2Dash = pList[j].second;
			pair<int,int> andClause;
			andClause.first = v1*m+(v1Dash+1);  //We are assuming that the graph has nodes from 0 to numVertices-1.So we have to add a +1
			andClause.second = v2*m+(v2Dash+1);
			temp.push_back(andClause);
			//cout<<v1<<" "<<v1Dash<<"\n";
		}
		vector<string> res1;
		if(temp.size()>0) res1 = getCnf(temp);
		cout<<"Value of i"<<i<<" size of clauses"<<res1.size();
		for(int k=0;k<res1.size();k++){
			//cout<<"k "<<k<<"\n";
			res.push_back(res1[k]);
		}
	}
	return res;
}

//This uses the principle of duality
vector<string> edgeConstraint1(Graph gEmail,Graph gPhone){
	vector<string> res;
	int n = gEmail.numVertices; int m = gPhone.numVertices; 
	vector<pair<int,int>> eList = gEmail.edgeList();
	vector<pair<int,int>> pList = gPhone.edgeList();
	cout<<eList.size()<<"----------------------\n";
	for(int i=0;i<eList.size();i++) cout<<eList[i].first<<" "<<eList[i].second<<" \n";
	cout<<pList.size()<<"----------------------\n";
	for(int i=0;i<eList.size();i++){
		int v1 = eList[i].first; int v2 = eList[i].second;
		for(int j=0;j<pList.size();j++){
			int v1Dash = pList[j].first; int v2Dash = pList[j].second;
			int x1 = v1*m+(v1Dash+1);  //We are assuming that the graph has nodes from 0 to numVertices-1.So we have to add a +1
			int x2 = v2*m+(v2Dash+1);  //v1 is mapped to V1Dash and v2 is mapped to v2Dash
			res.push_back("-"+to_string(x1)+" -"+to_string(x2));
		}
	}
	for(int i=0;i<pList.size();i++){
		int v1 = pList[i].first; int v2 = pList[i].second;
		for(int j=0;j<eList.size();j++){
			int v1Dash = eList[j].first; int v2Dash = eList[j].second;
			int x1 = v1Dash*m+(v1+1);  //We are assuming that the graph has nodes from 0 to numVertices-1.So we have to add a +1
			int x2 = v2Dash*m+(v2+1);  //v1Dash is mapped to v1 and v2Dash is mapped to v2
			res.push_back("-"+to_string(x1)+" -"+to_string(x2));
		}
	}
	return res;
}

vector<string> getCnf(vector<pair<int,int>> clause){
	cout<<"getCnf "<<clause.size()<<"\n";
	vector<string> res;
	if(clause.size()==1){
		pair<int,int> p = clause[0];
		string s1 = to_string(p.first);
		string s2 = to_string(p.second);
		res.push_back(s1); res.push_back(s2);
		cout<<"output\n";
		return res;
	}
	pair<int,int> p = clause[clause.size()-1];
	string s1 = to_string(p.first);
	string s2 = to_string(p.second);
	clause.pop_back();
	vector<string> temp = getCnf(clause);
	for(int i=0;i<temp.size();i++){
		//cout<<temp[i]+" "+s1<<"\n";
		res.push_back(temp[i]+" "+s1);
		res.push_back(temp[i]+" "+s2);
	}
	cout<<"outCnf "<<clause.size()<<"\n";
	return res;
}
