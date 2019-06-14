#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 2048
#define MAX_ARGS 512

//struct for holding all parts of a parsed command
struct ParsedInput
{
	//bool for if command is background or not
	int Background;
    	char InputFile[128];
    	char OutputFile[128];
    	char Command[MAX_COMMAND_LENGTH];
    	int NumArgs;
    	char *Arguments[MAX_ARGS];
};

//number of background pids
int NumBackgroundPids;
//keeps track of the background processes
pid_t BackgroundPids[MAX_ARGS];

//saves last foreground status in case user asks for it
int LastForegroundStatus;
//keep track if &s are ignored
//intitially set to false
int ForegroundOnly = 0;

//initializes the background pids to -1 instead of garbage
void initBP()
{
    	int i;
	NumBackgroundPids = 0;

    	for(i = 0; i < MAX_ARGS; i++)
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

//removes a particular background pid
void removeBP(pid_t processId)
{
    	int i;
	//index of pid to remove
    	int removeIndex; 
	
	//find index of pid to remove
    	for(i = 0; i < NumBackgroundPids; i++){
        	if(BackgroundPids[i] == processId){
			//found it
            		removeIndex = i;
            		break;
        	}
    	}
	
	//remove pid at that index
    	for(i = removeIndex; i < NumBackgroundPids; i++){
        	BackgroundPids[i] = BackgroundPids[i+1];
    	}
    	
	//decrement number of background pids
    	NumBackgroundPids--;

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

//lets user move through file directory
int changeDirectory(char* InputBuffer)
{
   	//finds the home path
    	char* HomeDirectoryPath = getenv("HOME");
	
	//initialize a new path
    	char NewPath[1028];
	memset(NewPath,'\0',sizeof(NewPath));

    	InputBuffer[strlen(InputBuffer) -1] = '\0';

	if(strcmp(InputBuffer,"cd") == 0){
	   	//check that the home directory is there
        	if(chdir(HomeDirectoryPath) != 0){
            		printf("%s not found\n", HomeDirectoryPath);
            		return 1;
        	}
        	return 0;
    	}

   	//ignoring spaces 
    	strtok(InputBuffer," ");
    	strcpy(InputBuffer, strtok(NULL,""));

    	if(InputBuffer[0] == '/'){
		//go to new path
        	sprintf(NewPath, "%s%s", HomeDirectoryPath, InputBuffer);
    	}

    	else if(strcmp(InputBuffer,"..") == 0){ 
		//go to parent directory
        	strcpy(NewPath, InputBuffer);
    	}

    	else if(strcmp(InputBuffer,"~") == 0){ 
	   	//go home
        	strcpy(NewPath, HomeDirectoryPath);
    	}

    	else if(InputBuffer[0] == '.' && InputBuffer[1] == '/'){ 
	   	//current directory
       	 	sprintf(NewPath,"%s", InputBuffer);
    	}

    	else{
	   	//go to directory
        	sprintf(NewPath,"%s", InputBuffer);
    	}

	//check that chdir worked
    	if(chdir(NewPath) != 0){
        	printf("%s not found\n", NewPath);
        	return 1;
    	}
    	return 0;
}

//function to check for leading &, <, >, #
//this helps to find args
int IsLeadCharSpecial(char *str)
{
    	int IsSpecial = 0;

	//check for string	
    	if(str == NULL){ 
        	return 1;
    	}

	//check for &
    	if(str[0] == '&'){ 
        	IsSpecial = 1;
    	}

	//check for <
    	else if(str[0] == '<'){ 
        	IsSpecial = 1;
    	}

	//check for >
    	else if(str[0] == '>'){ 
        	IsSpecial = 1;
    	}

	//check for #
    	else if(str[0] == '#'){
        	IsSpecial = 1;
    	}

    	return IsSpecial;
}

//takes the input and puts it into the struct for args
void ParseInput(char* InputBuffer, struct ParsedInput* input)
{
	char *InputFileName;
    	char *OutputFileName;
    	char *Temp;
	char *ret;

	//for using strtok
    	char TempBuffer[MAX_COMMAND_LENGTH];
	
	//number of arguments starts at 0
    	input->NumArgs = 0;

	//remove the newline
    	InputBuffer[strlen(InputBuffer) -1] = '\0';
	
	//check if it should be run in the background
    	if(InputBuffer[strlen(InputBuffer) -1] == '&'){
		//set to true 
        	input->Background = 1;
		//remove & now
        	InputBuffer[strlen(InputBuffer) -1] = '\0';
    	}
    	else
	{
		//set to false
        	input->Background = 0;
    	}

    	//clear temp buffer
    	memset(TempBuffer, '\0', sizeof(TempBuffer));
	//copy input buffer into temp buffer
    	strcpy(TempBuffer, InputBuffer);
	
	//get the command
    	strtok(TempBuffer," ");
	
	//put the command into the parsed input
    	strcpy(input->Command, TempBuffer);

    	//clear temp buffer
    	memset(TempBuffer, '\0', sizeof(TempBuffer)); 
	//copy input buffer into temp buffer
    	strcpy(TempBuffer, InputBuffer);

	//get everything after < to get input file
    	InputFileName = strstr(TempBuffer,"<");
	
	//checking if there was an input file
    	if(InputFileName != NULL){
		//get rid of <
     		memmove(InputFileName, InputFileName+2, strlen(InputFileName));
		
		//get rid of anything after input file name
        	strtok(InputFileName," ");
		
		//add a null terminator
        	InputFileName[strlen(InputFileName)] = '\0';
		
		//put it into the parsed input struct
        	strcpy(input->InputFile, InputFileName);
    	}

    	//clear temp buffer
    	memset(TempBuffer, '\0', sizeof(TempBuffer));
	//copy input buffer to temp buffer
    	strcpy(TempBuffer, InputBuffer);
    	
	//get everything after > to get output file
	OutputFileName = strstr(TempBuffer,">");
    
	//check if there was an output file
	if(OutputFileName != NULL){
		//get rid of >
        	memmove(OutputFileName, OutputFileName+2, strlen(OutputFileName));
		
		//get rid of anything after output file name
        	strtok(OutputFileName," ");        
		
		//add null terminator
		OutputFileName[strlen(OutputFileName)] = '\0';
		
		//put it into the parsed input struct
        	strcpy(input->OutputFile, OutputFileName);
    	}
     
	//clear temp buffer
    	memset(TempBuffer,'\0',sizeof(TempBuffer));
   	//copy input buffer into temp buffer
	strcpy(TempBuffer,InputBuffer);
   
       	//get everything before first space	
	strtok(TempBuffer," ");

	//get everything after first space
    	Temp = strtok(NULL,""); 

	//check if it is an argument
    	if(IsLeadCharSpecial(Temp) == 0){
        	strcpy(TempBuffer, Temp);
		
		//get everything before <, >, #, &
        	strtok(TempBuffer,"<>&#");
        	
		//get first arg
        	strtok(TempBuffer," ");
		
		//put first arg in parsed input
//		if(strstr(TempBuffer, "$$") != NULL)
//		{
//			ret = strstr(TempBuffer, "$$");
//		   	sprintf(ret, "%d\0", getpid());
//		}
        	input->Arguments[0] = TempBuffer;
        	input->NumArgs = 1;
		
		//get next arg
        	Temp = strtok(NULL," ");
        	
		while(Temp != NULL)
		{
		   	//put the rest of the args into parsed input struct
			
//		  	if(strstr(Temp, "$$") != NULL)	
//			{
//				ret = strstr(Temp, "$$");
//				sprintf(ret, "%d\0", getpid());
//			}
            		input->Arguments[input->NumArgs] = Temp;
            		input->NumArgs++;
            		Temp = strtok(NULL," ");
        	}
		
		//get the last arg
        	input->Arguments[input->NumArgs] = strtok(NULL, "");         
    	}

}

//makes array of arguements for execvp
void InitArgs(struct ParsedInput* input, char** Args)
{
    	int i;
	//for changing $$ to pid
	char *ret;

	//first arguement is the command
    	Args[0] = input->Command; 
   
 	for(i=0; i < input->NumArgs; i++)
	{

		if(getenv(input->Arguments[i]) != NULL)
		{
			//add args
            		Args[i+1] = getenv(input->Arguments[i]); 
        	}
		
       		else if(strcmp(input->Arguments[i],"$$") == 0)
		{	
          		sprintf(Args[i+1],"%d", getpid());
        	}
		//check for $$
		else if(ret = strstr(input->Arguments[i], "$$"))
		{  	
			sprintf(ret, "%d", getpid());
			Args[i+1] = (input->Arguments[i]);
		}
		//default		
        	else
		{
            		Args[i+1] = (input->Arguments[i]);
    		}
	}

	//add null terminator
    	Args[i+1] = NULL;

}

void SetupRedirects(struct ParsedInput* input)
{
   	//file descriptors
    	int InputFD = STDIN_FILENO;
    	int OutputFD = STDOUT_FILENO;

	//check if we have input file
    	if(input->InputFile[0] != '\0')
	{ 
	   	//open input file
        	InputFD = open(input->InputFile, O_RDONLY);

		//check for file
        	if(InputFD < 0)
		{ 
            		printf("cannot open %s for input\n", input->InputFile);
            		exit(1);
        	}

		//redirect input to input file
        	dup2(InputFD, 0); 

		//close input file
        	close(InputFD); 
    	}

	//check if we have output file
    	if(input->OutputFile[0] != '\0'){
        	//open or create file to write to
        	OutputFD = open(input->OutputFile, O_WRONLY | O_CREAT | O_TRUNC,0644);
		
		//check if anything went wrong
        	if(OutputFD < 0){ 
            		printf("cannout open or create %s for output\n", input->OutputFile);
            		exit(1);
        	}

		//redirect output to output file
        	dup2(OutputFD, 1);

		//close output file
        	close(OutputFD);
    	}
}

//forks a child for a command
void RunCommand(struct ParsedInput* input)
{
   	//for passing into exec
	char *Args[MAX_ARGS];

	//fork() return value
    	pid_t spawnPid = -5;

	//status
    	int ProcessStatus;

	int i; //for debugging
	
	spawnPid = fork();
    	switch(spawnPid)
    	{
	   	//error
        	case -1:
            		printf("fork() error\n");
            		exit(1);
            		break;

		//child
        	case 0: 
            		SetupRedirects(input);
            		InitArgs(input, Args);	
				
			//debug - print arguments
			//for(i=0;i<(input->NumArgs)+1;i++)
			//{			
			//	write(STDOUT_FILENO, "Arg ", 4);
			//	write(STDOUT_FILENO, Args[i], strlen(Args[i]));
			//	write(STDOUT_FILENO, "\n", 1);
			//}

			//run command
            		execvp(input->Command, Args);
            
            		printf("%s: no such file or directory\n", input->Command);
            		exit(1);
            		break;
		
		//parent
        	default:
			//check if command needs to run in background
            		if(input->Background == 1 && ForegroundOnly == 0)
			{
				//add to stack of background pids
                		pushBP(spawnPid);

				//print last added background pid
                		printf("Background Pid is %d\n", peekBP());
            		}
            		else
			{
			   	//make shell wait until process terminates
                		waitpid(spawnPid, &ProcessStatus, 0);
                		LastForegroundStatus = ProcessStatus;
            		}
            		break;
    	}
}

//^z signal handler
void TrapStopSignal(int signal)
{
	if(ForegroundOnly == 0)
	{
       		char* message = ("\nEntering foreground-only mode (& is now ignored)\n"); 
		
		//tell user
        	write(STDOUT_FILENO, message, 50);
		
		//change to true
        	ForegroundOnly = 1;	
    	}
    	else
	{
        	char* message = "\nExiting foreground-only mode\n";

		//tell user
        	write(STDOUT_FILENO, message, 31);
        	
		//set to false
		ForegroundOnly = 0;
    	}
}

void TrapChildSignal(int signal)
{
    	pid_t ChildPid;
    	int ChildStatus;
   	int i;

	//find the background pid that exited
    	for(i=0; i < NumBackgroundPids; i++)
	{
        	ChildPid = waitpid(BackgroundPids[i], &ChildStatus, WNOHANG);
		
		//check if child exited
        	if((ChildStatus == 0 || ChildStatus == 1) && ChildPid != 0 )
		{ 
            		fprintf(stdout, "\nBackground pid %d is done: exit value %d\n", ChildPid, ChildStatus);
            		removeBP(ChildPid);
        	}
		
		//other signals
        	else if(ChildPid != 0)
		{
            		fprintf(stdout, "\nBackground pid %d is done: terminated by signal %d\n", ChildPid, ChildStatus);
            		removeBP(ChildPid);
        	}
    }
    
}

//signal handler for ^c of a foreground process
void TrapTermSignal(int signal)
{
    printf("\nterminated by signal %d\n", signal); 
}

//frees parsed input struct
void ClearAndFreeInputStruct(struct ParsedInput* input)
{
	//reset background to false
    	input->Background = 0; 
    	//clear everything
    	memset(input->InputFile,'\0',sizeof(input->InputFile));
    	memset(input->OutputFile,'\0',sizeof(input->OutputFile));
    	memset(input->Command,'\0',sizeof(input->Command));
	
	//free parsed input
    	free(input);
}

//kills the background processes
void KillBGProcesses()
{
    	int i;
    	for(i=0; i < NumBackgroundPids; i++)
	{
		//interrupt all the background pids
        	kill(BackgroundPids[i], SIGINT); 
    	}
}

//switches foreground modes if a program returns a stop signal
void CheckForBGMode()
{
	//if signal is stop and foreground only is true, switch to false
    	if(WTERMSIG(LastForegroundStatus) == 11 && ForegroundOnly == 1)
	{
        	printf("\nExiting foreground-only mode\n");
        	ForegroundOnly = 0;
    	}
	
	//if signal is stop and foreground mode is false, switch to true
    	else if(WTERMSIG(LastForegroundStatus) == 11 && ForegroundOnly == 0)
	{
        	printf("\nEntering foreground-only mode (& is now ignored)\n");
        	ForegroundOnly = 1;
    	}
}

//runs shell
void RunShell()
{
    	char InputBuffer[MAX_COMMAND_LENGTH];
    	struct ParsedInput *input;
    	int ForegroundStatus;
	int i; //for debugging

	//initialize background pid array
	initBP();

    	//initialize stop signal to respective handler
    	struct sigaction StopSignal;
    	StopSignal.sa_handler = TrapStopSignal;
    	StopSignal.sa_flags = 0;

	//initialize term signal to respective handler
    	struct sigaction TermSignal;
    	TermSignal.sa_handler = TrapTermSignal;
    	StopSignal.sa_flags = 0;
	
	//initialize child signal to respective handler
    	struct sigaction ChildSignal;
    	ChildSignal.sa_handler = TrapChildSignal;
    	StopSignal.sa_flags = 0;

    	do
    	{
        	//reset signal handlers
        	sigaction(SIGTSTP, &StopSignal, NULL);
        	sigaction(SIGINT, &TermSignal, NULL);
        	sigaction(SIGCHLD, &ChildSignal, NULL);

        	CheckForBGMode();

        	//clear stdin and stdout
       	 	fflush(stdout);
        	fflush(stdin); 

        	printf(": ");

		//clear InputBuffer
        	memset(InputBuffer,'\0', sizeof(InputBuffer));
		
		//get command line
        	fgets(InputBuffer, sizeof(InputBuffer), stdin);
        
		//clear stdin and stdout
        	fflush(stdout);
        	fflush(stdin);
	
		//check for exit
        	if(strncmp(InputBuffer,"exit", 4) == 0)
		{ 
			//kill processes and exit shell
            		KillBGProcesses();
            		exit(0);
        	}
        
		//check for comment
		else if(strncmp(InputBuffer, "#", 1) == 0 || strcmp(InputBuffer, "\n") == 0)
		{
		  	//go to top of loop 
            		continue;
        	}

		//check for cd
        	else if(strncmp(InputBuffer,"cd", 2) == 0)
		{ 
            		changeDirectory(InputBuffer);
        	}

		//check for status
        	else if(strncmp(InputBuffer,"status", 6) == 0)
		{
		   	//check if exited
            		if(WEXITSTATUS(LastForegroundStatus))
			{
                		ForegroundStatus = WEXITSTATUS(LastForegroundStatus);
            		}
            
			else
			{
			   	//terminated by signal
                		ForegroundStatus = WTERMSIG(LastForegroundStatus);
            		}
            		
			//print exit vlaue
			printf("exit value %d\n", ForegroundStatus);
        	}
        
		else
		{
            		if(InputBuffer != NULL && strcmp(InputBuffer,"") != 0)
			{
                		//read in a command.
                		input = malloc(sizeof(struct ParsedInput));

			       	//parse and put command in parsed input struct	
                		ParseInput(InputBuffer, input);

				//debug - print arguments
				//for(i=0;i<input->NumArgs;i++)
				//{			
				//	printf("Argument %d: %s\n", i, input->Arguments[i]);
				//}

				//run the command
                		RunCommand(input);		
				
				//clear out and free the parsed input struct for next command
                		ClearAndFreeInputStruct(input);
            		}
            
			else
			{
                		continue;
            		}
        	}
    	}
	//keep going until user exits
    	while(1);
}

int main(void)
{
    	RunShell();
    	return 0;
}
