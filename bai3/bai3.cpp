#include<bits/stdc++.h>

using namespace std;

int offset;
int x,y;
FILE *fptr;
vector <int> v[100];
void builtConnections(int k) {
		
			for (int i=0; i<k; i++) {
				for (int j=0; j<k; j++) {
					if (j<k-1) {
						v[i*k+j].push_back(i*k+j+1);
					}
					if (j>0) {
						v[i*k+j].push_back(i*k+j-1);
					}
					if (i<k-1) {
						v[i*k+j].push_back((i+1)*k+j);
					}
					if (i>0) {
						v[i*k+j].push_back((i-1)*k+j);
					}
				}
			}
		}
void saveConnections(int k) {
			int soDinh = k*k;
			ofstream outfile("C:\\Users\\linhq\\Desktop\\network.txt", ios::out | ios::trunc);
			char dongLenh[1024];
			sprintf(dongLenh,"%d\n",soDinh);
			outfile<<dongLenh;
			for (int i=0; i<soDinh; i++) {
				sprintf(dongLenh,"%d ",v[i].size());
				outfile<<dongLenh;
				vector<int>::iterator duyet;
				for (duyet=v[i].begin(); duyet!=v[i].end(); duyet++) {
					int nextHop = (int) *duyet;
					sprintf(dongLenh,"%d ",nextHop);
					outfile<<dongLenh;
				}
				sprintf(dongLenh,"\n");
				outfile<<dongLenh;
			}
		}



void setSwitchPositon(int k){
	for(int i =0; i<k*k; i++){
	 	x =200+ i/k*100;
	 	y =200+ i%k*100;
	 	fprintf(fptr,"switch%d: Switch { @display(\"p=%d,%d;i=abstract/switch\"); }\n",i, x, y);
	 }
	 for(int i =0; i<k*k; i++){
	 	fprintf(fptr,"host%d: Host  { @display(\"i=abstract/server;is=s\"); }\n",i);
	 }
}

void switch2switch(int k){
	for(offset =0; offset <k-1; offset++)
	 	for(int i =0; i<k; i++){
//	 		fprintf(fptr,"switch[%d].out++ --> switch[%d].in++;\n",i+offset*k,k*(offset+1)+i);
	 		fprintf(fptr,"switch%d.port++ <--> Channel <--> switch%d.port++;\n\n",i+offset*k,k*(offset+1)+i);
	 		if(i%k==k-1)  continue;
//			fprintf(fptr,"switch[%d].out++ --> switch[%d].in++;\n",i+offset*k,k*offset +i+1);	 	
			fprintf(fptr,"switch%d.port++ <--> Channel <--> switch%d.port++;\n\n",i+offset*k,k*offset +i+1);
		 }
		for(int i = (k-1)*k ; i<k*k-1; i++){
//		fprintf(fptr,"switch[%d].out++ --> switch[%d].in++;\n",i,i+1);	
//		fprintf(fptr,"switch[%d].in++ <-- switch[%d].out++;\n",i,i+1); 
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
	
	fprintf(fptr,"simple Host\n{\nparameters:\n@display(\"i=device/pc_s\");\n\ngates:\ninout port[];\n}\nsimple Switch\n{\nparameters:\n@display(\"i=device/switch\");\nint xpos;\nint ypos;\n@display(\"p=$xpos,$ypos\");\ngates:\ninout port[];\n}\nnetwork Network\n{\nparameters:\n@display(\"bgb=1356.1,682.825\");\n");

	
	
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


