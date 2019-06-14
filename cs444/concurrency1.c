/**************************************************************************
* Concurrency 1
* CS 444
* Mary Jacobsen
* To compile: gcc -pthread -o c1 concurrency1.c
**************************************************************************/

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> //for sleep
//#include "mt19937ar.h"
//#include "rand.h"
//#include "rand_mersenne.h"

pthread_mutex_t lock;

struct item
{
	int num;
	int wait;
};

struct item items[32];

//extern uint32_t cpu_supports_rdrand();
//extern uint32_t native_get_random_number();
/*
static unsigned int (*real_get_random_number)(void);

unsigned int get_random_number() { return real_get_random_number(); }

// Get a random production period in the integer range [3,7).
unsigned int random_number_production()
{
	return (get_random_number() % 4) + 3;
}

// Get a random waiting period in the integer range [2,9).
unsigned int get_random_waiting_period()
{
	return (get_random_number() % 7) + 2;
}

void random_number_init()
{
	eax = 0x01;

	__asm__ __volatile__(
	                     "cpuid;"
	                     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	                     : "a"(eax)
	                     );

	if(cpu_supports_rdrand()) {
		real_get_random_number = native_get_random_number;
	} else {
		initialize_mersenne_twister(time(0));
		real_get_random_number = mersenne_twister_get_random_number;
	}
}

int randomNum(int option)
{
	eax = 0x01;

	__asm__ __volatile__(
	                     "cpuid;"
	                     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	                     : "a"(eax)
	                     );
	
	if(ecx & 0x40000000){
		//use rdrand
	}
	else{
		//use mt19937
		if(option == 1) //number for printing
		{   
			
		}

	   	else if(option == 2) //consumer wait time
		{   
			
		}

		else(option == 3) //producer wait time
		{   
		
		}

	}
}*/

void consumer()
{
   	int waitTime, i = 0;
	while(1)
	{
	   	
		if(i>=32)
		{
			i = 0; //reset
		}

		if(pthread_mutex_trylock(&lock) == 0)
		{
		   	if(items[i].num != -1 && items[i].wait != -1)
			{
			   	//print the number to print and the wait time
				printf("\nConsuming the number %d and waiting %d seconds at index %d\n", items[i].num, items[i].wait, i); 
				//set wait time
				waitTime = items[i].wait;
				//empty item at index i
				items[i].num = -1;
				items[i].wait = -1;
			}
			pthread_mutex_unlock(&lock);
			sleep(waitTime);
		}
		i++;	
	}
}

int main(int argc, char **argv)
{

	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;

	char vendor[13];

	int numConsumers = atoi(argv[1]);
	//printf("\nCommand line arg: %d\n", numConsumers);
	int i, j=0;
	int waitTimeP; //wait time for producer 

	//initialize items to empty
	for(i=0; i<32; i++)
	{
		items[i].num = -1;
		items[i].wait = -1;
	}
	srand(time(NULL));	
	//initalize consumer threads
	pthread_t *consumerThreads[numConsumers];

	for(i=0; i<numConsumers; i++)
	{
		if(pthread_create(&consumerThreads[i], NULL, (void *)consumer, (void *)NULL))
		{
			fprintf(stderr, "Error creating thread\n");
			return 1;
		}   
	}

	while(1)
	{
		if(j >= 32)
		{
			j = 0;
		}

		waitTimeP = 0;

		if(pthread_mutex_trylock(&lock) == 0)
		{
			if(items[j].num == -1 && items[j].wait == -1)
			{
				items[j].num=rand()%10;
				items[j].wait=(rand()%7)+2;
				printf("\nThe producer is inserting the number %d and the wait time %d at index %d\n", items[j].num, items[j].wait, j);
				waitTimeP=(rand()%4)+3;
				printf("\nThe producer is sleeping for %d seconds.\n", waitTimeP);	
			}
			pthread_mutex_unlock(&lock);
			sleep(waitTimeP);
		}
		j++;
	}




	return 0;
}
