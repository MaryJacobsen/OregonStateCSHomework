#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define A 65
#define Z 90


//generates a char* of random chars
char* GenerateKey(int length)
{
    	int i;
    	char* Key = malloc(sizeof(char) * length);

    	//loop for length
    	for(i=0; i<length; i++)
	{
		//add the possibility of spaces
        	if((rand() % (10) + 1) == 3 || (rand() % (10) + 1) == 6)
		{
            		Key[i] = ' ';
        	}
		//get random number 65 to 90 (A to Z)
        	else
		{
            		Key[i] = (rand() % (Z + 1 - A) + A);
        	}
    	}
    	Key[i] = '\0';

    	return Key;
}

//checks that the correct number of args are passed in
void validArgc(int argc)
{
    	//input should be ./keygen [length of message]
    	if(argc == 1)
	{
        	fprintf(stderr, "Please enter a key length.\n");
        	exit(1);
    	}
}

int main(int argc, char* argv[])
{
    	int Length;
    	char* Key;
	//make sure we have a length
    	validArgc(argc);

    	srand(time(NULL));
    	Length = atoi(argv[1]) + 1;

    	//make key
    	Key = GenerateKey(Length);
    	//print key
    	printf("%s", Key);

    	//free from heap.
    	free(Key);
    	return 0;
}
