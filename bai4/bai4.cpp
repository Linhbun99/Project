#include<bits/stdc++.h>
using namespace std;
int n,k;
vector <int> v[100];

void readFile(); // doc du lieu tu file network.txt
vector<int> routingTable(int start, vector<int> neighboor); 
void routing(int start); 
void writeToFile(int start, vector<int> RouteTable); 

int main(){
	 readFile();
	 for(int i= 0; i<k; i++){
		routing(i);
	}
	 
}

void readFile(){
	fstream infile;
	infile.open("C:\\Users\\linhq\\Desktop\\network.txt", ios::in);
	infile >> k;
	for (int i=0; i<k; i++) {
		int lv;
		infile>>lv;
		int nextHop;
		for (int j=0; j<lv; j++) {
			infile>>nextHop;
			v[i].push_back(nextHop);
		}
//		vector<int>::iterator p;
//		cout<< "\nNext hop cua switch "<<i<<": ";
//		for(p=v[i].begin(); p!= v[i].end(); p++){
//			int k = *p;
//			cout<<k<<"\t";
//		}
	}
}

// ghi du lieu sau khi thuc hien routing
void writeToFile(int start, vector<int>RouteTable ) {
			char file[256];
			fstream outfile;
			sprintf(file,"C:\\Users\\linhq\\Desktop\\Project\\neighboorsOfSwitch%d.txt",start);
			outfile.open(file, ios::out | ios::trunc);
			sprintf(file,"%d ",v[start].size());
			outfile<<file;
			vector<int>::iterator itr;
			for (itr=v[start].begin(); itr!=v[start].end(); itr++) {
				int nextHop = (int) *itr;
				sprintf(file,"%d ",nextHop);
				outfile<<file;
			}
			outfile.close();
			
			sprintf(file,"C:\\Users\\linhq\\Desktop\\Project\\routingSwitch%d.txt",start);			
			outfile.open(file, ios::out | ios::trunc);
			for (int i=0; i<RouteTable.size(); i++) {
				sprintf(file,"%d ",RouteTable[i]);
				outfile<<file;
			}
			outfile.close();
		}
	
// tim nut tiep theo can di den 

vector<int> routingTable(int start, vector<int> neighboor) {
	vector<int> RouteTable;
	RouteTable.resize(neighboor.size());
	fill(RouteTable.begin(), RouteTable.end(), -1);
	stack<int> myStack;
	for (int i=0; i<RouteTable.size(); i++) {
		if (RouteTable[i]==-1) {
			int j=i;					
		    while (neighboor[j]!=start) {
		    	myStack.push(j);
//		    	cout<<j<<"-" <<neighboor[j]<<"\n";
			    j = neighboor[j];
			    cout<<j<<" ";
		    }
		    myStack.push(j);
		    int x;
		    while (!myStack.empty()) {
		    	x = myStack.top();
		    	myStack.pop();
		    	RouteTable[x] = j;
//		    	cout<< RouteTable[x]<<"  ";
		    }

		}
	}
	return RouteTable;
}

// vector nextHop luu gia tri : muon di den nut i se di phai den nut nextHop[i] 
void routing(int start){
//	cout<<"===================\n";
	vector<int> neighboor;
			neighboor.resize(k);
			fill(neighboor.begin(), neighboor.end(), -1);
			queue<int> q;
			neighboor[start] = start;
			q.push(start);
			int nextHop;
			int add;
			vector<int>::iterator p;
			while (!q.empty()) {
				nextHop = q.front();
				q.pop();
				
				for (p=v[nextHop].begin(); p!=v[nextHop].end(); p++) {
					add = (int) *p;
//					cout<<"nextHop:" << nextHop <<"add:" << add<<endl; 
					if (neighboor[add]==-1) {
//						cout<<"nextHop:" << nextHop <<"add:" << add<<endl; 
						neighboor[add] = nextHop;
						q.push(add);
					}
				}
			}
//			vector<int>::iterator o;
//			for (o=neighboor.begin(); o!=neighboor.end(); o++) {
//			for (int o=0; o<neighboor.size(); o++) {
//				cout<<neighboor[o]<<" ";
//			}
	vector<int> RouteTable = routingTable(start,neighboor);
	writeToFile(start, RouteTable);
 
}


		



