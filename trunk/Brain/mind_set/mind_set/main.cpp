#include "MindControl.h"

int main(void)
{
	MindControl *m;
	char portName[15];
	char portNo[3];
	printf("Enter COM port number (1 - 99) \n");
	gets(portNo);

	strcpy(portName, "\\\\.\\COM");
	strcat(portName, portNo);

	m = new MindControl(portName);

	if(m == NULL){
		printf("ERROR: No memory");
		exit(EXIT_FAILURE);
	}
	if(m->isConnected()){
		printf("Connected\n");				
	}
	else{
		printf("No connection\n");
		delete m;
		exit(EXIT_FAILURE);
	}

	printf("Turn on data logging? (y/n)\n");
	if (getc(stdin) == 'y'){
		m->logOn();
		printf("log on\n");
	}
	else{
		m->logOff();
		printf("log off\n");
	}
	m->analyzeData();
	delete m;
	return( EXIT_SUCCESS );
}