/* Mary Jacobsen
 * Project 2 - file transer system
 * server side
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

//Reused from project 1
//This function is from Beej's guide
//https://beej.us/guide/bgnet/html/multi/syscalls.html#getaddrinfo
//It is used to get the address information and put it in addrinfo struct
struct addrinfo* getAddress(char* port){
    int status;
    struct addrinfo hints;
    struct addrinfo *res;               // to hold results
    memset(&hints, 0, sizeof hints);    // make sure the struct is empty
    hints.ai_family = AF_INET;          // version
	  hints.ai_socktype = SOCK_STREAM;    // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;

	  if((status = getaddrinfo(NULL, port, &hints, &res)) != 0){ //check that status is 0
		    fprintf(stderr, "Address / port error\n", gai_strerror(status));
		    exit(1);
	  }
	  return res;
}

//Reused from project 1
//This function is from Beej's guide
//https://beej.us/guide/bgnet/html/multi/syscalls.html#getaddrinfo
//It is used to get the address information and put it in addrinfo struct
struct addrinfo* getAddressIP(char* addressIP, char* port){
    int status;
    struct addrinfo hints;
    struct addrinfo *res;               // to hold results
    memset(&hints, 0, sizeof hints);    // make sure the struct is empty
    hints.ai_family = AF_INET;          // version
	  hints.ai_socktype = SOCK_STREAM;    // TCP stream sockets

	  if((status = getaddrinfo(addressIP, port, &hints, &res)) != 0){ // check that status is 0
		    fprintf(stderr, "IP Address / port error\n", gai_strerror(status));
		    exit(1);
	  }
	  return res;
}

//Reused from project 1
//This function returns the socket descriptor that is needed
//The call to socket() in this function is from Beej's guide
int getSockfd(struct addrinfo* res){
    int sockfd;
    if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){ // check for error
		    fprintf(stderr, "Error getting socket descriptor\n");
		    exit(1);
	  }
	  return sockfd;
}

//Reused from project 1
//This function connects the socket descriptor to the address passed in
//Also learned this from Beej's guide
void connectSocket(int sockfd, struct addrinfo * res){
    int status;
    if ((status = connect(sockfd, res->ai_addr, res->ai_addrlen)) == -1){ //check for error
		    fprintf(stderr, "Error connecting\n");
		    exit(1);
	 }
}

//This function binds the socket (associates the socket with a port to listen on later)
//This is also from Beej's guide
void bindSocket(int sockfd, struct addrinfo * res){
  if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1){
    close(sockfd);
    fprintf(stderr, "Error binding\n");
    exit(1);
  }
}

//This function is used to listen for incoming connections
//listen function call from Beej's guide
void listenForConnections(int sockfd){
  if(listen(sockfd, 5) == -1){
		close(sockfd);
		fprintf(stderr, "Error listening\n");
		exit(1);
  }
}

//This function reads all the files from a directory
//This page on stack overflow showed me how to do this:
//https://stackoverflow.com/questions/11736060/how-to-read-all-files-in-a-folder-using-c
//also referenced these for struct dirent:
//https://www.gnu.org/software/libc/manual/html_node/Directory-Entries.html
//http://pubs.opengroup.org/onlinepubs/7908799/xsh/readdir.html
int dirFiles(char** files){
	DIR* fd;
	struct dirent * dir;
	fd = opendir(".");
	int i = 0;
	if (fd){
    //keep reading file names if there are any left
		while ((dir = readdir(fd)) != NULL){
      //if it is a regular file
			if (dir->d_type == DT_REG){
        //add to files array
				strcpy(files[i], dir->d_name);
				i++;
			}
		}
    //close directory
		closedir(fd);
	}
	return i;
}

//This function is for sending files
//The parts for sending and recieving are from this:
//ftp://gaia.cs.umass.edu/pub/kurose/ftpserver.c
void sendFile(char* addressIP, char * port, char * filename){
	sleep(2);
  //get address, get socket file descriptor, and connect socket
	struct addrinfo * res = getAddressIP(addressIP, port);
	int sockfd = getSockfd(res);
	connectSocket(sockfd, res);

  //file buffer
	char buffer[2000];
  //clear buffer
	memset(buffer, 0, sizeof(buffer));

  //get file descriptor for reading
	int fd = open(filename, O_RDONLY);
	while (1) {
		int bytes = read(fd, buffer, sizeof(buffer) - 1);
		if (bytes == 0)
			break;

		if (bytes < 0) {
			fprintf(stderr, "Error reading %s\n",filename);
			return;
		}

		void* buf = buffer;
		while (bytes > 0) {
			int bytesSent = send(sockfd, buf, sizeof(buffer), 0);
			if (bytesSent < 0) {
				fprintf(stderr, "Error sending %s\n",filename);
				return;
			}
			bytes -= bytesSent;
			buf += bytesSent;
		}
    //clear buffer
		memset(buffer, 0, sizeof(buffer));
	}

  char* done = "finished";
	send(sockfd, done, strlen(done), 0);

  //close socket
	close(sockfd);
	freeaddrinfo(res);
}

//This function sends all the files in a directory
//It just needs to set up connection, a loop to send, and then close the socket
void sendDirectory(char * addressIP, char * port, char ** files, int n){
	sleep(2);
  int i;
  //get address, get socket file descriptor, and connect socket
	struct addrinfo * res = getAddressIP(addressIP, port);
	int sockfd = getSockfd(res);
	connectSocket(sockfd, res);

  //loop to send each file
	for (i = 0; i < n; i++){
		send(sockfd, files[i], 100 ,0);
	}

	char* done = "finished";
	send(sockfd, done, strlen(done), 0);

	close(sockfd);
	freeaddrinfo(res);
}

//This function allocates for an array that is used to hold files
//Referenced the following to make this function
//https://stackoverflow.com/questions/7652293/how-do-i-dynamically-allocate-an-array-of-strings-in-c
char ** getArray(int size){
  int i;
	char ** array = malloc(size*sizeof(char *));
	for(i = 0; i < size; i++){
		array[i] = malloc(100*sizeof(char));
		memset(array[i],0,sizeof(array[i]));
	}
	return array;
}
//This function is used to free the array
void freeArray(char ** array, int size){
	int i;
	for (i = 0; i < size; i++){
		free(array[i]);
	}
	free(array);
}

int fileFound(char ** files, int numFiles, char * filename){
	int i;
  //check each file in directory to see if it matches filename
	for (i = 0; i < numFiles; i++){
    //if it matches, return 1
		if(strcmp(files[i], filename) == 0){
			return 1;
		}
	}
  //didn't find a match so return 0
	return 0;
}

//This function is for receiving commands from the client
//and sending what the commands specify
//This function layout is based off of task 7 of the assignment requirements
//and Beej's guide
void commandsFromClient(int acceptedfd){
	char port[100];
  char command[500];
  char addressIP[100];
  char * madeit = "ok";
	char * didnotmakeit = "notokay";

  //clear port holder
	memset(port, 0, sizeof(port));
	recv(acceptedfd, port, sizeof(port)-1, 0); //get port
  send(acceptedfd, madeit, strlen(madeit), 0); //ack

  //clear command holder
	memset(command, 0, sizeof(command));
	recv(acceptedfd, command, sizeof(command)-1, 0); //get command
	send(acceptedfd, madeit, strlen(madeit),0); //ack

  //clear addressIP
	memset(addressIP, 0, sizeof(addressIP));
	recv(acceptedfd, addressIP, sizeof(addressIP)-1,0); //get ip address of connection
	printf("Connection from %s\n", addressIP); //print ip address of connection

  //-g <FILENAME> (get))
  //transfer the file given
  if(strcmp(command, "-g") == 0){
	   send(acceptedfd, madeit, strlen(madeit), 0); //ack

	   char filename[100]; //container for filename
	   memset(filename, 0, sizeof(filename)); //clear filename container
	   recv(acceptedfd, filename, sizeof(filename) - 1, 0); //get filename
	   printf("File %s requested on port %s\n", filename, port); //print the requested filename

     //allocate files
     char** files = getArray(500);
     //fill files and returns number of files
     int numFiles = dirFiles(files);
     //if the file is in the directory
	   if(fileFound(files, numFiles, filename)){
			   char * fileFound = "File found";
			   send(acceptedfd, fileFound, strlen(fileFound), 0);

         //new filename container
			   char newFilename[100];
         //clear new filename container
			   memset(newFilename, 0, sizeof(newFilename));
			   strcpy(newFilename, "./");
			   char * end = newFilename + strlen(newFilename);
         //referenced https://www.geeksforgeeks.org/sprintf-in-c/
			   end += sprintf(end, "%s", filename);

         //send to client
         printf("Sending %s to client:%s\n", filename, port);
			   sendFile(addressIP, port, newFilename);
		}
    else{
			printf("File not found. Sending error message to client:%s\n",port);
			char * notFound = "File not found";
			send(acceptedfd, notFound, 100, 0);
		}
    //free files
		freeArray(files, 500);
	}
  //-l (list)
  //list the files in a directory
	else if(strcmp(command,"-l") == 0){

    printf("List directory requested on port %s\n", port);
		send(acceptedfd, madeit, strlen(madeit),0);
    //allocate files
    char** files = getArray(500);
    //fill files and return number of files
    int numFiles = dirFiles(files);
		printf("Sending directory contents to client:%s\n", port);
    //send to client
		sendDirectory(addressIP, port, files, numFiles);
    //free files
	  freeArray(files,500);
	 }
   else{
		send(acceptedfd, didnotmakeit, strlen(didnotmakeit), 0);
		printf("Not a valid command. Commands: -l or -g <FILENAME>\n");
	 }

	 printf("Waiting for connections\n");
}
//this function is to wait to accept connections
//it is from Beej's guide
void waitConnectionAccept(int sockfd){
	struct sockaddr_storage their_addr;
  socklen_t addr_size;
	int acceptedfd;

	while(1){
		addr_size = sizeof(their_addr);
		acceptedfd = accept(sockfd, (struct addrinfo *)&their_addr, &addr_size);

		if(acceptedfd == -1){
			continue;
		}

		commandsFromClient(acceptedfd);
		close(acceptedfd);
	}
}

//main just checks command line arguments
//and calls all the necessary functions
int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Please use: ./ftserver [server_port]\n");
		exit(1);
	}

	printf("Server open on port %s\n", argv[1]);
	struct addrinfo* res = getAddress(argv[1]);
	int sockfd = getSockfd(res);
	bindSocket(sockfd, res);
	listenForConnections(sockfd);
	waitConnectionAccept(sockfd);
	freeaddrinfo(res);
}
