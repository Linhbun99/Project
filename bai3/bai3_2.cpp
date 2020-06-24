#include<bits/stdc++.h>

using namespace std;

int offset;
int x,y;
FILE *fptr;
vector <int> v[100];
void builtConnections(int k) {
//		for(int offset =0; offset <k-1; offset++)
//	 	for(int i =0; i<k; i++){
//	 		if(i%k!=k-1) [i+offset*k].push_back(k*offset +i+1);
//			 
//	 		v[i+offset*k].push_back(k*(offset+1)+i); 	
//			
//		 }
//		for(int i = (k-1)*k ; i<k*k-1; i++){
//			v[i].push_back(i+1);
//		}
			for (int i=0; i<k; i++) {
				for (int j=0; j<k; j++) {
					if (i>0) {
//						cout<< (i-1)*k+j<<"line 23";
						v[i*k+j].push_back((i-1)*k+j);
					}
					
					if (j>0) {
//						cout<<i*k+j-1<<" line 28 ";
						v[i*k+j].push_back(i*k+j-1);
					}
						if (j<k-1) {
//						cout<<i*k+j+1<<" line 32 ";
						v[i*k+j].push_back(i*k+j+1);
					}
					if (i<k-1) {
//						cout<< (i+1)*k+j<<" line 37 ";
						v[i*k+j].push_back((i+1)*k+j);
					}
					
				
					
					
				}
				cout<<endl;
			}
		}
void saveConnections(int k) {
			int soDinh = k*k;
			ofstream outfile("C:\\Users\\linhq\\Desktop\\network.txt", ios::out | ios::trunc);
			char dongLenh[1024];
//			sprintf(dongLenh,"%d\n",soDinh);
//			outfile<<dongLenh;
			for (int i=0; i<soDinh; i++) {
				sprintf(dongLenh,"switch%d ",i);
				outfile<<dongLenh;
				vector<int>::iterator duyet;
				for (duyet=v[i].begin(); duyet!=v[i].end(); duyet++) {
					int nextHop = (int) *duyet;
					sprintf(dongLenh,"switch%d ",nextHop);
					outfile<<dongLenh;
				}
				sprintf(dongLenh,"host%d",i);
				outfile<<dongLenh;
				sprintf(dongLenh,"\n");
				outfile<<dongLenh;
			}
		}



void setSwitchPositon(int k){
	for(int i =0; i<k*k; i++){
	 	x =200+ i/k*200;
	 	y =200+ i%k*200;
	 	fprintf(fptr,"switch%d: Switch { @display(\"p=%d,%d;i=abstract/switch\"); }\n",i, x, y);
	 }
	 for(int i =0; i<k*k; i++){
	 	x =200+ i/k*200;
	 	y =200+ i%k*200;
	 	fprintf(fptr,"host%d: Host  { @display(\"p=%d,%d;\i=abstract/server;is=s\"); }\n",i,x-50,y-50);
	 }
}

void switch2switch(int k){
	for(offset =0; offset <k-1; offset++)
	 	for(int i =0; i<k; i++){
	 		if(i%k!=k-1) fprintf(fptr,"switch%d.port++ <--> Channel <--> switch%d.port++;\n\n",i+offset*k,k*offset +i+1);
	 		fprintf(fptr,"switch%d.port++ <--> Channel <--> switch%d.port++;\n\n",i+offset*k,k*(offset+1)+i);
//	 		if(i%k==k-1)  continue;	 	
			
		 }
		for(int i = (k-1)*k ; i<k*k-1; i++){
		fprintf(fptr,"switch%d.port++ <--> Channel <--> switch%d.port++;\n",i,i+1);
		}
}

void switch2host(int k){
	for(int i =0; i<k*k ; i++){
		fprintf(fptr,"host%d.port++ <--> Channel <--> switch%d.port++;\n",i,i);
//		fprintf(fptr,"host[%d].in++ <-- switch[%d].out++;\n",i,i);
	}
	 
}
int main(){
	int k;
	cin>> k;
	
	fptr = fopen("C:\\Users\\linhq\\Desktop\\output.txt","w");
	
	fprintf(fptr,"simple Host\n{\nparameters:\n@display(\"i=device/pc_s\");\n\ngates:\ninout port[];\n}\nsimple Switch\n{\nparameters:\n@display(\"i=device/switch\");\n\ngates:\ninout port[];\n}\nnetwork Network\n{\nparameters:\n@display(\"bgb=1356.1,682.825\");\n");

	
	
	fprintf(fptr,"types:\nchannel Channel extends ned.DelayChannel\n{delay = 15ms;}\nsubmodules:\n");
	setSwitchPositon(k);
	
	fprintf(fptr,"\nconnections:\n");
	
	switch2switch(k);
	switch2host(k);
	
	fprintf(fptr,"}");
	fclose(fptr);
	builtConnections(k);
	saveConnections(k);
	
}


