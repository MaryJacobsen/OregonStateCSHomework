#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>

#define ROOM_OPTIONS 10 //number of possible room names to randomize from
#define NUM_ROOMS 7 //number of rooms in the graph
#define MIN_ROOM_CONNECTIONS 3
#define MAX_ROOM_CONNECTIONS 6

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

//holds the name of the newest dir that contains prefix
char newestDirName[256];

//file for current time
char *timeFileName = "currentTime.txt";

pthread_mutex_t TimeFile_Mutex;

void SelectDirectory()
{
   	//modified timestamp of the newest subdir examined
   	int newestDirTime = -1;
	
	//prefix we're looking for
    	char targetDirPrefix[32] = "jacomary.rooms.";
	
	memset(newestDirName, '\0', sizeof(newestDirName));

	//holds the dir we're starting in
	DIR *dirToCheck;

	//holds the current subdir of the dir
	struct dirent *fileInDir;

	//holds information we've gained about sundir
	struct stat dirAttributes;

	//open up the directory this program was run in
	dirToCheck = opendir(".");

	//make sure the current directory was opened
	if(dirToCheck > 0)
	{
	   	//check each entry in dir
		while((fileInDir = readdir(dirToCheck)) != NULL)
		{
		   	//if entry has prefix
			if(strstr(fileInDir->d_name, targetDirPrefix) != NULL)
			{
			   	//get attributes of the entry
			   	stat(fileInDir->d_name, &dirAttributes);

				//if this time is bigger
				if((int)dirAttributes.st_mtime > newestDirTime)
				{
					newestDirTime = (int)dirAttributes.st_mtime;
				     	memset(newestDirName, '\0', sizeof(newestDirName));
					strcpy(newestDirName, fileInDir->d_name);
				}
			}
		}	
	}
}

//sets all the connections in a given room to NULL
void InitializeRoomConnections(int room_num)
{
	int i;
    	for(i=0; i<MAX_ROOM_CONNECTIONS; i++)
	{
            	room_graph[room_num].connections[i] = NULL;
    	}
}

void InitializeRoomGraph()
{
    	int i;
    	for(i=0; i<NUM_ROOMS; i++)
	{
		//sets each name to NULL
        	memset(room_graph[i].name,'\0', sizeof(room_graph[i].name));
		//sets number of connections to 0
        	room_graph[i].num_connections = 0;
		//sets all the connections to NULL 
        	InitializeRoomConnections(i); 
    	}
}

//separates the labels from the values in the room files
void SeparateLabelFromValue(char *label, char *value)
{
    	int i;

	//cut label from value at :
    	strtok(label,":");

	//set value from strtok
    	strcpy(value, strtok(NULL,""));

	//add \0 at end of value and label strings
    	value[strlen(value)-1] = '\0';
    	label[strlen(label)-1] = '\0';

    	for(i=0; i<strlen(value); i++)
	{ 
		//remove space from value string.
        	value[i] = value[i+1];
    	}
}

//find the index of a room name in the room graph
int FindRoomIndexFromName(char *RoomName)
{
    	int i;

    	for(i=0; i<NUM_ROOMS; i++)
	{
		//if the name of the room matches return the index
       		if( strcmp(room_graph[i].name, RoomName) == 0 )
		{ 
            		return i;
        	}
    	}
	
	//return -1 if nothing matched
    	return -1;
}

//make connection from one room to another room (one sided)
void MakeConnection(int roomIndexA, int roomIndexB)
{
    	int numConnectionsA = room_graph[roomIndexA].num_connections;
	
	//add connection from A to B
    	room_graph[roomIndexA].connections[numConnectionsA] = &room_graph[roomIndexB];
    	room_graph[roomIndexA].num_connections++; 
}

//fill the room structs with names from reading in the room files
void FillRoomGraphNames()
{
    	DIR *dir;
    	struct dirent *fileInDir;
	//iterator for room structs
    	int FileCount = 0;
	//initialize the room graph
    	InitializeRoomGraph();

    	/*Filling struct Names*/
    	if((dir = opendir(newestDirName)) != NULL)
	{
        	while((fileInDir = readdir(dir)) != NULL) 
		{
            		if(strlen(fileInDir->d_name) > 2)
			{ 
				//copy file name to struct
                		strcpy(room_graph[FileCount].name, fileInDir->d_name);
                		FileCount++;
            		}
        	}
    	}
}

//fill in the room structs from reading in the room files
void FillStructRooms()
{
    	char line[256];
    	char value[256];
	//pointer to room file
    	FILE *roomFile;
    	int i;

	//fill the room structs with names
    	FillRoomGraphNames();
	
	//change to the room directory
    	chdir(newestDirName); 

    	for(i=0; i<NUM_ROOMS; i++)
	{
		//open room file for reading
        	roomFile = fopen(room_graph[i].name,"r");
		
		//make sure the file is there
        	if(roomFile == NULL)
		{ 
            		printf("%s is NULL\n", room_graph[i].name);
            		return;
        	}

        	memset(line,'\0', sizeof(line));
        	memset(value,'\0', sizeof(value));

        	//read the file line by line
        	while(fgets(line, sizeof(line), roomFile) != NULL)
		{
            		//separate the label from the value on the line
            		SeparateLabelFromValue(line, value);
			
			//fill in connections
            		if(strcmp(line,"CONNECTION ") == 0)
			{
				//get the index of the room to connect to  
                		int roomIndex = FindRoomIndexFromName(value);
                		MakeConnection(i, roomIndex);
            		}
	
			//fill in room type
            		else if(strcmp(line,"ROOM TYP") == 0)
			{
				//find which room type
                		if(strcmp(value,"START_ROOM") == 0)
				{
                    			room_graph[i].type = START_ROOM;
                		}
                		else if(strcmp(value,"END_ROOM") == 0)
				{
                    			room_graph[i].type = END_ROOM;
                		}
                		else
				{	
                    			room_graph[i].type = MID_ROOM;
                		}
            		}
	        }
		//close file
       		fclose(roomFile);
	}
    	//return to parent directory	
    	chdir("..");
}

//prints out the path taken
void PrintStepPath(int *path, int steps)
{
	int i;

    	for(i = 1; i < steps + 1; i++)
	{ 
		//print the name of every step
        	printf("%s\n", room_graph[path[i]].name);
    	}
}

//returns the index of the start room
int FindStartRoomIndex()
{
    	int i;
	//look through until start room is found
    	for(i =0; i<NUM_ROOMS; i++)
	{ 
        	if(room_graph[i].type == START_ROOM){ 
		//return start room index
            	return i;
        	}
    	}
	//return -1 if start room is not found
    	return -1;
}

//make the current time file
void* MakeCurrentTimeFile()
{
	char TimeStr[256];
    	time_t CurrentTime;
    	struct tm * TimeInfo;
    	FILE *TimeFile;
	
	//clear time string
    	memset(TimeStr,'\0',sizeof(TimeStr));
	
	//get the current time
    	time(&CurrentTime);

	//put the current time into the TimeInfo struct 
    	TimeInfo = localtime(&CurrentTime);
	
	//format the time string
    	strftime(TimeStr, 256, "%I:%M%P %A, %B %d, %Y", TimeInfo);
	
	//open time file that can be written to
    	TimeFile = fopen(timeFileName,"w");

	//write the current time to the time file
    	fprintf(TimeFile,"%s\n",TimeStr); 
    	
	//close the time file
	fclose(TimeFile);

    	return NULL;
}

//make time thread
int TimeThread()
{
	//container for the thread that will have the function
    	pthread_t MakeTimeFile_Thread;

	//lock the thread so it can't be used until it is finished running
    	pthread_mutex_lock(&TimeFile_Mutex); 

    	//check that the thread was created correctly
	//start make current time file function running
    	if(pthread_create(&MakeTimeFile_Thread, NULL, MakeCurrentTimeFile, NULL) != 0)
	{
        	printf("thread error");
        	return 0;
    	}

    	//now unlock the mutex
    	pthread_mutex_unlock(&TimeFile_Mutex);
    	
	//wait for make time file thread to terminate
    	pthread_join(MakeTimeFile_Thread, NULL);
    	
	return 1;
}

//print out the current time by reading the current time file
void PrintCurrentTime()
{
    	char line[256];
    	FILE *TimeFile;

	//clear the line string
    	memset(line,'\0',sizeof(line)); 
	
	//open the time file for reading
    	TimeFile = fopen(timeFileName,"r"); 
	
	//make sure the file is there
    	if(TimeFile == NULL)
	{
        	printf("%s is NULL\n", timeFileName);
        	return;
    	}

    	//read in the file line by line
    	while(fgets(line, 256, TimeFile) != NULL)
	{
		//print the current time from the file
        	printf("%s\n", line);
    	}
	
	//close the time file
    	fclose(TimeFile);
}

//run the game
PlayAtlantisAdventure()
{
	int i;
    	int stepCount = 0;
    	int path[1028]; //holds rooms the user has gone into in order
    	int roomIndex;
    	struct Room currentRoom;
   	char input[256]; //user input
	int validInput; //to check if user typed "time" or a valid connection name
	
	//find the index of the start room
    	path[stepCount] = FindStartRoomIndex();

	do{
	   	//set / reset this to false every time
		validInput = 0;
	   	
        	//keep track of step path
        	roomIndex = path[stepCount];
        	currentRoom = room_graph[roomIndex];
		
		//print the room the user is in
        	printf("CURRENT LOCATION: %s\n", currentRoom.name);

        	//print out all the names of connections except the last one
        	printf("POSSIBLE CONNECTIONS:");
        	for(i=0; i<currentRoom.num_connections - 1; i++)
		{
            		printf(" %s,",currentRoom.connections[i]->name);
        	}

        	//print last connection separately to have a period instead of a comma
        	printf(" %s.\n", currentRoom.connections[i]->name);
	
		//clear input string
        	memset(input,'\0', sizeof(input));

        	//prompt user to type where to go next
        	printf("WHERE TO? >");
	
		//take in input up to 255 chars
        	scanf("%255s", input);

        	printf("\n"); //\n for formatting

        	//check if user wants to go to a connecting room
		for(i=0; i<currentRoom.num_connections; i++)
		{
            		if(strcmp(input, currentRoom.connections[i]->name) == 0)
			{ 
				//set validInput to true
				validInput = 1;
			   	
				//increment step count
                		stepCount++;

				//put the user's choice in the path
                		path[stepCount] = FindRoomIndexFromName(input);
                	
				//go to the room they chose
				roomIndex = path[stepCount]; 
                		currentRoom = room_graph[roomIndex];
			
				//check if the user found the end room
 				if(currentRoom.type == END_ROOM)
				{
					//print out congratulatory message
                    			printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
			
					//print step count and the path they took
                    			printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", stepCount);
                    			PrintStepPath(path, stepCount);
                    			return;
                		}
            		}
		}

        	//check if user wants the time
        	if(strcmp(input, "time") == 0)
		{
		   	//set validInput to true
			validInput = 1;

			//check if time thread was created properly
            		if( TimeThread() == 1)
			{
				//print the current time from reading the time file
                		PrintCurrentTime();
            		}
            
        	}
        	
		//if the input was not valid
        	else if(validInput == 0)
		{
            		printf("HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
        	}
    	}
    	while(1);
}

int main(void)
{
   	//get the newest room directory
	SelectDirectory();
	
	//fill the room structs
	FillStructRooms();

	//run the game
	//it will keep running until the player wins or presses control c
	PlayAtlantisAdventure();
	return 0;
}
