#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

#include "graph.h"

using namespace std;

vector<string> getCnf(vector<pair<int,int> >);
vector<string> oneOne(int,int);
vector<string> myConstraint(Graph, Graph, bool**, bool**);
vector<string> edgeConstraint(Graph,Graph);
vector<string> edgeConstraint1(Graph,Graph);

int main(int argc, char** argv){
	time_t start = time(0);
	 // string line;
	int numVertices1 = 0,numVertices2=0; bool firstGraph = true;
	vector<int> srcList1,srcList2,dstList1,dstList2;  //(srcList1,dstList1)----> gPhone;(srcList2,srcList2)---> gEmail
	string input_file;
	input_file = argv[1];
	ifstream inFile(input_file+".graphs");
	if(inFile.is_open()){
		int src,dst,temp, prev_src, prev_dst;
		prev_src = -1; prev_dst = -1;
		while(!inFile.eof()){
			// temp = s.find(" ");              //s.find(c) Finds the index of first occurance of c
			// src = stoi(line.substring(0,temp));    //s.substring(startInd,len) Finds substring of s starting at startInd and Length = len
			// dst = stoi(line.substring(temp+1,line.length()-(temp+1)));
			// //Checking for the end of first graph in the if-condition
			inFile >> src;
			inFile >> dst;
			if (prev_src == src && prev_dst == dst){

			}else{
				if(src>0 && dst>0){
					if(firstGraph == true){
						srcList1.push_back(src);   //Assuming that nodes start at 0 and not 1
						dstList1.push_back(dst);
						// cout<<src<<" "<<dst<<"\n";
						if(numVertices1<src) numVertices1 = src;
						if(numVertices1<dst) numVertices1 = dst;
					}
					else{
						srcList2.push_back(src);
						dstList2.push_back(dst);
						// cout<<src<<" "<<dst<<"\n";
						if(numVertices2<src) numVertices2 = src;
						if(numVertices2<dst) numVertices2 = dst;
					}
				}
				else firstGraph = false;
		}
		prev_src = src;
		prev_dst = dst;
	}
	inFile.close();
	}
	else cout<<"Unable to open the file";
	bool** arr1;
	arr1 = new bool*[numVertices1];
	for (int i=0; i<numVertices1; i++){
		arr1[i] = new bool[numVertices1];
		for (int j=0; j<numVertices1; j++){
			arr1[i][j] = false;
		}
	}

	bool** arr2;
	arr2 = new bool*[numVertices2];
	for (int i=0; i<numVertices2; i++){
		arr2[i] = new bool[numVertices2];
		for (int j=0; j<numVertices2; j++){
			arr2[i][j] = false;
		}
	}

	Graph gPhone(numVertices1);
	Graph gEmail(numVertices2);
	int size = srcList1.size();
	// cout<<"Phone Starts here "<<srcList1.size()<<"\n";
	for(int i=0;i<size;i++){
		// cout<<srcList1[i]-1 <<" "<<dstList1[i]-1<<"\n";
		// gPhone.addEdge(srcList1[i]-1,dstList1[i]-1);
		arr1[srcList1[i]-1][dstList1[i]-1] = true;
	}
	size = srcList2.size();
	// cout<<"Email starts here "<<dstList2.size()<<"\n";
	for(int i=0;i<size;i++){
		// cout<<srcList2[i]-1 <<" "<<dstList2[i]-1<<"\n";
		// gEmail.addEdge(srcList2[i]-1,dstList2[i]-1);
		arr2[srcList2[i]-1][dstList2[i]-1] = true;
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
	// cout<<"Hey1\n";
	vector<string> res1 = oneOne(numVertices2,numVertices1);
	// for(int i=0;i<res1.size();i++) cout<<res1[i]<<"\n";
	// cout<<"Hey2\n";
	vector<string> res2 = myConstraint(gEmail,gPhone, arr1, arr2);
  int numVariables = (numVertices2*numVertices1)+(numVertices1*numVertices1)+(numVertices2*numVertices2);
  int numConstraints = res1.size() + res2.size();

	ofstream outFile1("./values.txt");
	outFile1 << numVertices2 << " " << numVertices1 << "\n";
	outFile1.close();

    ofstream outFile(input_file+".satinput");
    outFile<<"p"<<" cnf "<<numVariables<<" "<<numConstraints<<"\n";
    for(int i=0;i<res1.size();i++){
    	outFile<<res1[i]<<" 0\n";
    }
		for (int i=0; i<res2.size(); i++){
			outFile<<res2[i]<<" 0\n";
		}

		outFile.close();

		time_t finish = time(0);
		cout << finish - start << " seconds" << endl;
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
	for(int i=1;i<=m;i++){
		vector<string> temp;
		for(int j=0;j<n;j++){
			str = to_string(j*m+i);
			temp.push_back(str);
		}
		for(int i1=0;i1<n;i1++){
			for(int j1=i1+1;j1<n;j1++){
				res.push_back("-"+temp[i1]+" -"+temp[j1]);
			}
		}
	}
	return res;
}

vector<string> myConstraint(Graph gEmail, Graph gPhone, bool** arr1, bool** arr2){
	vector<string> res;
	int n = gEmail.numVertices; int m = gPhone.numVertices;
	for (int i = 0; i < n; i++){
		// vector<int> temp = gEmail.neighbours(i);
		// int temp1 = 0; int size = temp.size();
		// cout << size << "\n";
		// int nxtNeighbour = -1;
		// if (temp1 < size){
		// 	nxtNeighbour = temp[temp1];
		// }
		for (int j=0; j<n; j++){
			if (!arr2[i][j]){
				res.push_back(to_string(-((n*m)+(i*n)+j+1)));
			}else{
				res.push_back(to_string((n*m)+(i*n)+j+1));
				// temp1++;
				// if (temp1 < size){
				// 	nxtNeighbour = temp[temp1];
				// }
			}
		}
	}
	for (int i = 0; i < m; i++){
		// vector<int> temp = gPhone.neighbours(i);
		// int temp1 = 0; int size = temp.size();
		// int nxtNeighbour = -1;
		// if (temp1 < size){
		// 	nxtNeighbour = temp[temp1];
		// }
		for (int j=0; j<m; j++){
			if (!arr1[i][j]){
				res.push_back(to_string(-((n*n)+(n*m)+(i*m)+j+1)));
			}else{
				res.push_back(to_string((n*n)+(n*m)+(i*m)+j+1));
				// temp1++;
				// if (temp1 < size){
				// 	nxtNeighbour = temp[temp1];
				// }
			}
		}
	}
	// cout << "done\n";

	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			for (int iDash=0; iDash<m; iDash++){
				for (int jDash=0; jDash<m; jDash++){
					if (arr2[i][j]){
						res.push_back(to_string(-((i*m)+iDash+1)) + " " + to_string(-((j*m)+jDash+1)) + " " + to_string((n*n)+(n*m)+(iDash*m)+jDash+1));
						// res.push_back(to_string(-((n*n)+(n*m)+(iDash*m)+jDash+1)) + " " + to_string(-((i*m)+iDash+1)) + " " + to_string(-((j*m)+jDash+1)) + " " + to_string((n*m)+(i*n)+j+1));
					}
					if (arr1[iDash][jDash]){
						// res.push_back(to_string(-((n*m)+(i*n)+j+1)) + " " + to_string(-((i*m)+iDash+1)) + " " + to_string(-((j*m)+jDash+1)) + " " + to_string((n*n)+(n*m)+(iDash*m)+jDash+1));
						res.push_back(to_string(-((i*m)+iDash+1)) + " " + to_string(-((j*m)+jDash+1)) + " " + to_string((n*m)+(i*n)+j+1));
					}
				}
			}
		}
	}
	return res;
}

vector<string> edgeConstraint(Graph gEmail,Graph gPhone){
	vector<string> res;
	int n = gEmail.numVertices; int m = gPhone.numVertices;
	vector<pair<int,int> > eList = gEmail.edgeList();
	vector<pair<int,int> > pList = gPhone.edgeList();
	cout<<eList.size()<<"----------------------\n";
	for(int i=0;i<eList.size();i++) cout<<eList[i].first<<" "<<eList[i].second<<" \n";
	cout<<pList.size()<<"----------------------\n";
	for(int i=0;i<eList.size();i++){
		int v1 = eList[i].first; int v2 = eList[i].second;
		vector<pair<int,int> > temp;
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
	vector<pair<int,int> > eList = gEmail.edgeList();
	vector<pair<int,int> > pList = gPhone.edgeList();
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

vector<string> getCnf(vector<pair<int,int> > clause){
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
