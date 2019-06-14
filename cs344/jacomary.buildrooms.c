#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define ROOM_OPTIONS 10 //number of possible room names to randomize from
#define NUM_ROOMS 7 //number of rooms in the graph
#define MIN_ROOM_CONNECTIONS 3
#define MAX_ROOM_CONNECTIONS 6

//global array of possible room names
//Room names are areas in Stargate Atlantis.
char *ROOM_NAMES[ROOM_OPTIONS] =
{
	"Stargate_Operations",
	"Mess_Hall",
	"Living_Quarters",
	"Jumper_Bay",
	"Infirmary",
	"Hologram_Room",
	"Conference_Room",
	"Chair_Room",
	"Brig",
	"Auxiliary_Control_Center"
};

//three types of rooms
enum ROOM_TYPES
{
	START_ROOM, //starting room
	MID_ROOM, //all other rooms
	END_ROOM //winning room
};

//room struct	
struct Room
{
	char name[256]; //name of room
	struct Room *connections[MAX_ROOM_CONNECTIONS]; //connections to other rooms
	int num_connections; //number of connections to other rooms
	enum ROOM_TYPES type; //type of room
};

//graph of rooms
struct Room room_graph[NUM_ROOMS]; 

//0 or 1 to know what room names have been used when randomizing
int used_rooms[ROOM_OPTIONS]; 

//name of directory
char directory_name[256];

//check if a connection can be added from a specific room
//returns 1 (true) or 0 (false)
int CanAddConnectionFrom(int position)
{
	if(room_graph[position].num_connections == MAX_ROOM_CONNECTIONS){
		return 0; //too many room connections
	}

	return 1; //can connect from this room
}

//check if connection already exists
//returns 1 (true) or 0 (false)
int AlreadyConnectedOrSame(int posA, int posB)
{
	int i;

	//checks if posA and posB are actually the same
	//since there are no repeat room names in the graph this is sufficient to check
	if(posA == posB) return 1;

	//goes through connections of posA and checks for connection to posB
	for(i=0; i<room_graph[posA].num_connections; i++){
		if(strcmp(room_graph[posA].connections[i]->name, room_graph[posB].name) == 0){
			return 1;
		}
	}

	return 0; //good to go
}

//returns a random room position within the 7
//does not validate if connection can be added
int GetRandomRoom()
{
	return rand() % NUM_ROOMS;
}

//connects rooms A and B together
//does not check if this connection is valid
void ConnectRoom(int posA, int posB)
{
   	//index after last connection
	int connectionA = room_graph[posA].num_connections; 
	int connectionB = room_graph[posB].num_connections;
	
	//add connection
	room_graph[posA].connections[connectionA] = &room_graph[posB];	
	room_graph[posB].connections[connectionB] = &room_graph[posA];	
	
	//increment num_connections
	room_graph[posA].num_connections++;
	room_graph[posB].num_connections++;
}

//adds random, valid outbound connection from a room to another room
void AddRandomConnection()
{
	int A;
	int B;

	while(1)
	{
		A = GetRandomRoom();

		if(CanAddConnectionFrom(A) == 1) break;
	}
	
	do
	{
		B = GetRandomRoom();
	}
	while(CanAddConnectionFrom(B) == 0 || AlreadyConnectedOrSame(A, B) == 1);
	
	ConnectRoom(A, B);
}

//returns a random room name position within the 10
int GetRandomRoomOption()
{
	return rand() % ROOM_OPTIONS;
}

//makes a room graph
void MakeRoomGraph()
{
	int i, j;   
    	//set all the room names to not used
    	for(i=0; i<ROOM_OPTIONS; i++){
        	used_rooms[i] = 0;
    	}
	//set room connections to NULL
	for(i=0; i<NUM_ROOMS; i++)
	{
		room_graph[i].num_connections = 0;
		for(j=0; j<MAX_ROOM_CONNECTIONS; j++){
			room_graph[i].connections[j] = NULL;
		}

		while(1)
		{
			int random_room = GetRandomRoomOption();
			//checks if random_room was used already
			if(used_rooms[random_room] == 0){ 
				//set it to used
                		used_rooms[random_room] = 1;
				//make there are no garbage values at the end of strings
                		memset(room_graph[i].name,'\0',sizeof(room_graph[i].name));
				//copy the room name to the room graph
                		strcpy(room_graph[i].name, ROOM_NAMES[random_room]);
				//set all the rooms to MID_ROOM for now
                		room_graph[i].type = MID_ROOM;
                		break;
            		}
		}
	}
	//places starting and winning rooms
	room_graph[0].type = START_ROOM;
	room_graph[NUM_ROOMS - 1].type = END_ROOM;	
}

//checks if each room has at least 3 connections
int IsGraphFull()
{
	int i;
	for(i=0; i<NUM_ROOMS; i++){
		//if any room has less than 3 connections, return false
		if(room_graph[i].num_connections < 3){
			return 0;
		}
	}
	return 1;
}

//makes the room graph and adds the connections
void FillRoomGraph()
{
	MakeRoomGraph();
	//until each room has at least 3 connections, keep adding connections
	while(IsGraphFull() == 0)
	{
		AddRandomConnection();
	}
}

//creates room directory
void MakeRoomDirectory()
{
	char *directory_name1 = "jacomary.rooms.";
	int pid = getpid();
	//owner and group and read, write, and execute but not others
	int permissions = 0770; //rwxrwx--- 
	
	//sets the directory name with the 1st part and the process id
	memset(directory_name, '\0', sizeof(directory_name));
	sprintf(directory_name, "%s%d", directory_name1, pid);
	
	//makes directory
	mkdir(directory_name, permissions);	
}

//creates room files
void MakeRoomFiles()
{
	FILE *room_file;
   	int i, j;
	char directory[256];
	
	//gets the directory
	sprintf(directory, "./jacomary.rooms.%d", getpid());
	
	//makes the directory
	MakeRoomDirectory();
	
	//checking if directory changed correctly
	if(chdir(directory) != 0){
		printf("Error: Directory not changed to %s\n", directory);
		return;
	}

	for(i=0; i<NUM_ROOMS; i++){
	   	//room file
	   	room_file = fopen(room_graph[i].name, "w");

		//print name to the file
		fprintf(room_file, "ROOM NAME: %s\n", room_graph[i].name);

		//print connections to the file
		for(j=0; j<room_graph[i].num_connections; j++){
			fprintf(room_file, "CONNECTION %d: %s\n", j+1, room_graph[i].connections[j]->name);
		}

		//prints type to the file
		if(room_graph[i].type == MID_ROOM){
            		fprintf(room_file,"ROOM TYPE: %s\n","MID_ROOM");
        	}
        	else if(room_graph[i].type == START_ROOM){
            		fprintf(room_file,"ROOM TYPE: %s\n","START_ROOM");
        	}
        	else if(room_graph[i].type == END_ROOM){
            		fprintf(room_file,"ROOM TYPE: %s\n","END_ROOM");
        	}
        	else{
            		fprintf(room_file,"ROOM TYPE: %s\n","NULL");
        	}
        	fclose(room_file);	
	}
}

int main()
{
	srand(time(NULL));
	FillRoomGraph();
	MakeRoomFiles();
	return 0;	
}
