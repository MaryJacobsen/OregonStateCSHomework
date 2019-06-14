/* Mary Jacobsen
 * client server chat program
 * client side
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

//This function is from Beej's guide
//https://beej.us/guide/bgnet/html/multi/syscalls.html#getaddrinfo
//It is used to get the address information and put it in addrinfo struct
struct addrinfo* getAddress(char* address, char* port){
    int status;
    struct addrinfo hints;
    struct addrinfo *res;               // to hold results
    memset(&hints, 0, sizeof hints);    // make sure the struct is empty
    hints.ai_family = AF_INET;          // version
	  hints.ai_socktype = SOCK_STREAM;    // TCP stream sockets

	  if((status = getaddrinfo(address, port, &hints, &res)) != 0){ // check that status is 0
		    fprintf(stderr, "Server address / port error\n", gai_strerror(status));
		    exit(1);
	  }
	  return res;
}

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

//This function connects the socket descriptor to the server address passed in
//Also learned this from Beej's guide
void connectSocket(int sockfd, struct addrinfo * res){
    int status;
    if ((status = connect(sockfd, res->ai_addr, res->ai_addrlen)) == -1){ //check for error
		    fprintf(stderr, "Error connecting\n");
		    exit(1);
	 }
}

//Handshake
//https://linux.die.net/man/2/send
//http://man7.org/linux/man-pages/man2/recvmsg.2.html
void handshake(int sockfd, char * clientname, char * servername)
{
    int sendingreturn = send(sockfd, clientname, strlen(clientname), 0);
    int receivingreturn = recv(sockfd, servername, 10, 0);
}

//This function is for chatting after everything is set up
void chat(int sockfd, char * clientname, char * servername){
    int num_bytes = 0; //for checking sending and receiving
	  int connection; //for checking if the server closed the connection

	  char inputBuffer[500]; //buffer for input
    memset(inputBuffer, 0 ,sizeof(inputBuffer)); //clear input buffer

	  char outputBuffer[500]; //buffer for output
	  memset(outputBuffer, 0, sizeof(outputBuffer)); //clear output buffer

    //https://www.systutorials.com/docs/linux/man/3-fgets/
	  fgets(inputBuffer, 500, stdin); //clear stdin

    //just keep chatting
	  while(1){
        //chatclient will display this handle as a prompt on host B,
        //and will prepend it to all messages sent to host A
		    printf("%s> ", clientname);
		    fgets(inputBuffer, 500, stdin);

        //or closes the connection with the command “\quit”
		    if (strcmp(inputBuffer, "\\quit\n") == 0){
		        break;
		    }

        //from Beej's guide yet again
        //send returns the number of bytes sent
		    num_bytes = send(sockfd, inputBuffer, strlen(inputBuffer), 0);

        //check for errors sending
		    if(num_bytes == -1){
		        fprintf(stderr, "Error sending data\n");
				    exit(1);
		    }

        //Beej's guide
        //recv returns the number of bytes read
		    connection = recv(sockfd, outputBuffer, 500, 0);

        //check for errors receiving
		    if (connection == -1){
		        fprintf(stderr, "Error receiving data\n");
		        exit(1);
		    }

        //connection equals 0 if the server closed the connection
		    else if (connection == 0){
		        printf("The connection was closed by the server.\n");
			      break;
		    }

        else{
            //servername followed by message from server
	          printf("%s> %s\n", servername, outputBuffer);
		    }

        //clear buffers
        memset(inputBuffer, 0, sizeof(inputBuffer));
        memset(outputBuffer, 0, sizeof(outputBuffer));
	  }

    //close connection
	  close(sockfd);
	  printf("The connection is closed.\n");
}

//main
int main(int argc, char *argv[]){
    char clientName[10]; //to hold client handle
    char serverName[10]; //to hold server handle
    struct addrinfo * res; //to hold address info
    int sockfd; //for socket descriptor

    //check that we have three args (program, server, and port)
    if(argc != 3){
		    fprintf(stderr, "Please use: ./chatclient [server] [port]\n");
		    exit(1);
    }
    //get client handle
    printf("Enter a name that is 10 characters or less for the client.");
	  scanf("%s", clientName);

    //get address info
    //pass in server address and port
    res = getAddress(argv[1], argv[2]);

    //get the socket descriptor
    sockfd = getSockfd(res);

    //connect socket descriptor to the server address passed in
    connectSocket(sockfd, res);

    //handshake
    handshake(sockfd, clientName, serverName);

    //we are now set up and can chat
    chat(sockfd, clientName, serverName);

    //Beej's guide
    //free the linked list that getaddrinfo() allocated
    freeaddrinfo(res);
}
