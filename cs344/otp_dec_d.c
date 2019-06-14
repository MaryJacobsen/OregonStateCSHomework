#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#define CONNECTIONMAX 5

//number of background pids
int NumBackgroundPids;
//keeps track of the background processes
pid_t BackgroundPids[CONNECTIONMAX];
//for making sure the client trying to connect is the correct client
char AcceptedClientType = 'D';


//initializes the background pids to -1 instead of garbage
void initBP()
{
    	int i;
	NumBackgroundPids = 0;

    	for(i = 0; i < CONNECTIONMAX; i++)
	{
        	BackgroundPids[i] = -1;
    	}
}

//adds a background pid
void pushBP(pid_t processId)
{
	BackgroundPids[NumBackgroundPids] = processId;
	NumBackgroundPids++;
}

//removes the last background pid that was added 
pid_t popBP()
{
	return BackgroundPids[--NumBackgroundPids];
}

//returns the last background pid that was added
pid_t peekBP()
{
    	return BackgroundPids[NumBackgroundPids-1];
}

//kills the background processes
void TerminateServer(int sig)
{
    	int i;
    	for(i=0; i < NumBackgroundPids; i++)
	{
		//interrupt all the background pids
        	kill(BackgroundPids[i], SIGINT); 
    	}
}

//error function
void error(const char *msg) 
{ 
	perror(msg); 
	exit(1); 
} 

//takes a key and a message and encrypts the message using the key
char* DecryptMsg(char* key, char* message)
{
	int i; 
	int keytemp; 
	int msgtemp;
	int length = strlen(message);
	//buffer
	char decryptedMsg[70000];
	
	//clear buffer
	memset(decryptedMsg,'\0',sizeof(decryptedMsg));
	
	//loop through each char in message	
	for(i=0; i<length; i++){
		if(message[i] == '?')
		{
			//replace spaces with ?
			decryptedMsg[i] = ' ';
		}
		else
		{
			keytemp = (int)key[i];
			msgtemp = (int)message[i];
			
			//take char int values and key value from message value
			decryptedMsg[i] = (char)(msgtemp - (keytemp % 3));
		}
	}

	//return decrypted message
	return strdup(decryptedMsg);
}

int main(int argc, char *argv[])
{
	//initialize the background pid stack
	initBP();

	//handler that kills the background pids
	signal(SIGINT, TerminateServer);

	//key goes here
	char KeyBufferFile[70000];
	//message goes here
	char MsgBufferFile[70000];
	//encrypted message goes here
	char* decryptedMsg;
	char clienttype, charResponse;
	//for setup and connection
	int listenSocketFD, establishedConnectionFD, portNumber, charsRead, FileLength;
	socklen_t sizeOfClientInfo;
	char buffer[256];
	struct sockaddr_in serverAddress, clientAddress;
	
	//check for correct number of arguments
	if (argc < 2) 
	{ 
		fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); 
	}

	//set up the address struct for the server

	//clear address struct
	memset((char *)&serverAddress, '\0', sizeof(serverAddress));

	//set port number and convert it from a string to an int
	portNumber = atoi(argv[1]); 

	//make a network capable socket
	serverAddress.sin_family = AF_INET;

	//put port number in address struct
	serverAddress.sin_port = htons(portNumber);

	//set that any address can connect to server
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	// Set up the socket

	//make listening socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	//check that it worked
	if (listenSocketFD < 0)
	{ 
		error("Error: opening socket");
	}

	//bind listening socket to port
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
	{
		error("Error: binding");
	}
	
	//tell socket to start listening
	listen(listenSocketFD, 5);
	//Not sure how many sockets should go in listen call. 
	//It specified 5 for how many concurrent socket connections 
	//but it didn't specify how many can be in the queue to be connected.
	//5 was in the lecture slides though for the queue size in listen.

	//set the size of adress of connecting client
	sizeOfClientInfo = sizeof(clientAddress);

	//keep running and taking connections
	while(1)
	{
		//wait to take a connection (block until one connects)
		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo);
		if (establishedConnectionFD < 0) 
		{
			error("Error: accept()");
		}
		
		//fork a child for that connection
		pid_t pid = fork();

		switch(pid)
		{
			case -1:
				error("Error: child fork");
			//child
			case 0:
				//make sure client is encrpytion type
				recv(establishedConnectionFD, &clienttype, sizeof(char), 0);
				
				//if client type is not encryption, don't connect
				if(clienttype != AcceptedClientType){
					//tell client no
					charResponse = 'N';
					send(establishedConnectionFD, &charResponse, sizeof(char), 0);
					//send error message
					error("Error: invalid client connection");
				}
				else{
					//tell client yes
					charResponse = 'Y';
					send(establishedConnectionFD, &charResponse, sizeof(char), 0);
				}

				//read file length
				recv(establishedConnectionFD, &FileLength, sizeof(FileLength), 0);
				
				//clear message and file buffers
				memset(KeyBufferFile,'\0',sizeof(KeyBufferFile));
				memset(MsgBufferFile,'\0',sizeof(MsgBufferFile));

				//read key
				recv(establishedConnectionFD, KeyBufferFile, FileLength * sizeof(char), 0);

				//read message
				recv(establishedConnectionFD, MsgBufferFile, FileLength * sizeof(char), 0);
				
				//decrypt message
				decryptedMsg = DecryptMsg(KeyBufferFile, MsgBufferFile);

				//send decrypted message back to client and shut down connection
				send(establishedConnectionFD, decryptedMsg, FileLength * sizeof(char), 0);
				shutdown(establishedConnectionFD, 2);

				exit(0);

			//parent
			default:
				//add to 5 possible processes
				pushBP(pid);
		}

	}

	return 0; 
}


