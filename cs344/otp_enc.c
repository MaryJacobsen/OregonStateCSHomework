#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fcntl.h>
#include <sys/stat.h>

//struct for holding the file names, descripters, and length (which is the  same)
struct FileInfo 
{
	int KeyDescriptor;
	int MsgDescriptor;
	char* KeyFileName;
	char* MsgFileName;
	int FileLength; //same for key and msg
};

//error function from slides
void error(const char *msg) 
{ 
	perror(msg); 
	exit(0);
} 

//checks that at least 3 args are passed to the function
void ValidArgc(int argc)
{
    if(argc == 3){
        error("Error: invalid number of arguments");
        exit(1);
    }
}

//stores data from args into file info struct
struct FileInfo *InitFileInfo(char** argv)
{
   	//allocate memory for file info
	struct FileInfo *f = malloc(1 * sizeof(struct FileInfo));

	//set file names
	f->MsgFileName = argv[1];
	f->KeyFileName = argv[2];

	//open msg file 
	f->MsgDescriptor = open(argv[1], O_RDONLY);
	if(f->MsgDescriptor < 0){
		error("Error: couldnt open plaintext file");
	}
	// open key file
	f->KeyDescriptor = open(argv[2], O_RDONLY);
	if(f->KeyDescriptor < 0){
		error("Error: couldnt open keytext file");
	}

	return f;
}

//checks for chars that aren't A-Z or a space
char* ValidateFileContent(struct FileInfo* f, char fdType)
{
	int i; 
	int FileDescriptor;
	char* FileContent = malloc(f->FileLength * sizeof(char*));
	int Buffer;

	//check if it is key or msg
	if(fdType == 'K'){
		FileDescriptor = f->KeyDescriptor;
	}
	else if(fdType == 'M'){
		FileDescriptor = f->MsgDescriptor;
	}

	//read file
	if(read(FileDescriptor, FileContent, f->FileLength) < 0){ 
		error("Error: couldnt open file");
	}

	//validate the contents of file is within A-Z or is a space
	for(i=0; i<f->FileLength; i++)
	{
		Buffer = (FileContent[i]);
		if(!(Buffer == ' ' || (Buffer >= 'A' && Buffer <= 'Z')))
		{
			error("Error: invalid character in a file");
		}

	}
	//return an address of file content
	return FileContent;
}

//closes file descriptors
CloseFDs(struct FileInfo *f)
{
	// close desciptors.
	close(f->MsgDescriptor);
	close(f->KeyDescriptor);

	//set -1
	f->MsgDescriptor = -1;
	f->KeyDescriptor = -1;
}

//check to make sure key is not shorter than msg and sets FileLength
int SetFileLength(struct FileInfo *f)
{
	struct stat Key, Msg;

	//check stat
	if(stat(f->KeyFileName, &Key) < 0){
		error("Error: stats of key file");
	}

	//check stat
	if(stat(f->MsgFileName, &Msg) < 0){
		error("Error: stats of msg file");
	}

	//return error if key is shorter than text file
	if(Key.st_size-1 < Msg.st_size -1){
		error("Error: Key File cannot be shorter than Message File");
	}

	else{
		//set FileLength
		f->FileLength = Msg.st_size -1;
	}

	return f->FileLength;
}

int main(int argc, char* argv[])
{
	//variables for connection 
	int socketFD, portNumber;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	//so server can tell which client this is	
	char client = 'E';
    
	//check for correct number of args
	ValidArgc(argc);
	//fill file info struct
	struct FileInfo *info = InitFileInfo(argv);
	SetFileLength(info);

	//Read Key and Msg
	char* Key = ValidateFileContent(info, 'K');
	char* EncryptedMsg = malloc(info->FileLength * sizeof(char*));
	char* Msg = ValidateFileContent(info, 'M');
	char serverAccept;

	//set up the server address struct

	//clear address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress));

	//convert port from string to int
	portNumber = atoi(argv[3]);

	//make network capable socket
	serverAddress.sin_family = AF_INET;

	//set port number
	serverAddress.sin_port = htons(portNumber);

	//connecting to server that is also on localhost (my machine)
	serverHostInfo = gethostbyname("localhost");

	//check serverHostInfo
	if (serverHostInfo == NULL) { 
		fprintf(stderr, "Client Error: no such host\n");
		exit(1);
	}

	//copy in address
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); 
	
	//make socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	//check socket
	if (socketFD < 0){ 
		error("Error: client opening socket");
	}
	
	//connect to server
	//connect socket to server address
	if(connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
	{
	 	error("Error: client connecting");
	}


	//send E so server knows which client this is
	send(socketFD, &client, sizeof(char), 0);
	//receive Y or N
	recv(socketFD,&serverAccept, sizeof(char), 0);
	//check if server is correct
	if(serverAccept != 'Y')
	{
		close(socketFD);
		error("Error: not the encryption server");
	}

	//send file length to server
	send(socketFD, &(info->FileLength), sizeof(info->FileLength), 0);
	//send key
	send(socketFD, Key, info->FileLength * sizeof(char), 0);
	//send message
	send(socketFD, Msg, info->FileLength * sizeof(char), 0);

	//receive encrypted message
	recv(socketFD, EncryptedMsg, info->FileLength * sizeof(char), 0);
	printf("%s\n", EncryptedMsg);

	//freeing data
	CloseFDs(info);
	free(Key);
	free(Msg);
	free(EncryptedMsg);
	free(info);

	return 0;
}
