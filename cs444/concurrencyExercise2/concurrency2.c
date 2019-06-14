/**************************************************************************
* Concurrency 2
* CS 444
* Mary Jacobsen
* To compile: gcc -pthread -o concurrency2 concurrency2.c
**************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

char *PhilosopherNames[5] = {
    "Plato",
    "Aristotle",
    "Socrates",
    "Zeno",
    "Pythagoras",
};

pthread_t philosopher_threads[5];

pthread_mutex_t Forks[5] = 
{
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER
};

void get_forks(int i) {
    if (pthread_mutex_lock(&Forks[i]) != 0) 
    {
        perror("getting fork");
        exit(EXIT_FAILURE);
    } 
    else 
    {
        printf("%s picked up his left fork (fork number %u)\n", PhilosopherNames[i], i);
    }
    if (pthread_mutex_lock(&Forks[(i+1)%5]) != 0) 
    {
        perror("getting fork");
        exit(EXIT_FAILURE);
    } 
    else 
    {
        printf("%s picked up his right fork (fork number %u)\n", PhilosopherNames[i], (i+1)%5);
    }
}

void put_forks(int i) 
{
    printf("%s set down his left fork (fork number %u)\n", PhilosopherNames[i], i);
    if (pthread_mutex_unlock(&Forks[i]) != 0) 
    {
        perror("unlocking first fork");
        exit(EXIT_FAILURE);
    }
    printf("%s set down his right fork (fork number %u)\n", PhilosopherNames[i], (i+1)%5);
    if (pthread_mutex_unlock(&Forks[(i+1)%5]) != 0) 
    {
        perror("unlocking second fork");
        exit(EXIT_FAILURE);
    }
}

void think() 
{
    sleep((rand() % 20) + 1);
}

void eat() 
{
    sleep((rand() % 8) + 2);
}

void *loop(void *input) 
{
    unsigned i = (uintptr_t)input;
    char *name = PhilosopherNames[i];
    while (true) 
    {
        printf("%s is starting to think.\n", name);
        think();
        printf("%s is done thinking.\n", name);
        get_forks(i);
        printf("%s is starting to eat.\n", name);
        eat();
        printf("%s is done eating.\n", name);
        put_forks(i);
    }
    return NULL;
}

int main() 
{
    unsigned i;
    for (i = 0; i < 5; i++) 
    {
        void *index = (unsigned int*)(uintptr_t)i;
        pthread_create(&philosopher_threads[i], NULL, loop, index);
    }
    for (i = 0; i < 5; i++) 
    {
        pthread_join(philosopher_threads[i], NULL);
    }
    return 0;
}

