#include<bits/stdc++.h>
using namespace std;

int offset;
int x,y;
FILE *fptr;

void setSwitchPositon(int k){
	for(int i =0; i<k*k; i++){
	 	x =200+ i/k*100;
	 	y =200+ i%k*100;
	 	fprintf(fptr,"\nswitch[%d].xpos = %d;\nswitch[%d].ypos = %d;\n",i, x, i, y);
	 }
}

void switch2switch(int k){
	for(offset =0; offset <k-1; offset++)
	 	for(int i =0; i<k; i++){
	 		fprintf(fptr,"switch[%d].out++ --> switch[%d].in++;\n",i+offset*k,k*(offset+1)+i);
	 		fprintf(fptr,"switch[%d].in++ <-- switch[%d].out++;\n",i+offset*k,k*(offset+1)+i);
	 		if(i%k==k-1)  continue;
			fprintf(fptr,"switch[%d].out++ --> switch[%d].in++;\n",i+offset*k,k*offset +i+1);	 	
			fprintf(fptr,"switch[%d].in++ <-- switch[%d].out++;\n",i+offset*k,k*offset +i+1);
		 }
		for(int i = (k-1)*k ; i<k*k-1; i++){
		fprintf(fptr,"switch[%d].out++ --> switch[%d].in++;\n",i,i+1);	
		fprintf(fptr,"switch[%d].in++ <-- switch[%d].out++;\n",i,i+1); 
		}
}

void switch2host(int k){
	for(int i =0; i<k*k ; i++){
		fprintf(fptr,"host[%d].out++ --> switch[%d].in++;\n",i,i);
		fprintf(fptr,"host[%d].in++ <-- switch[%d].out++;\n",i,i);
	}
	 
}
int main(){
	int k;
	cin>> k;
	
	fptr = fopen("C:\\Users\\linhq\\Desktop\\output.txt","w");
	
	fprintf(fptr,"simple Host\n{\nparameters:\n@display(\"i=device/pc_s\");\n\ngates:\ninput in[];\noutput out[];\n}\nsimple Switch\n{\nparameters:\n@display(\"i=device/switch\");\nint xpos;\nint ypos;\n@display(\"p=$xpos,$ypos\");\ngates:\ninput in[];\noutput out[];\n}\nnetwork Network\n{\nparameters:\n@display(\"bgb=1356.1,682.825\");\n");

	setSwitchPositon(k);
	
	fprintf(fptr,"\ntypes:\nsubmodules:\nswitch[%d]:Switch;\nhost[%d]:Host;\nconnections:\n",k*k,k*k);
	
	switch2switch(k);
	switch2host(k);
	
	fprintf(fptr,"}");
	fclose(fptr);
}


