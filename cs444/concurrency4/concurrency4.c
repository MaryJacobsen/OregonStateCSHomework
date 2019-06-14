#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t customers_available_lock;
pthread_mutex_t barber_lock;
pthread_mutex_t chairs_lock;
sem_t chairs;
pthread_cond_t customers_available;
pthread_cond_t barber_available;

//possible names
char *names[25] = {
    "Jane",
    "Lukas",
    "Markus",
    "Al",
    "Lilly",
    "Alice",
    "Hector",
    "Allen",
    "Shirley",
    "Peter",
    "Will",
    "Helen",
    "Bob",
    "Bill",
    "Jackson",
    "Jill",
    "Karl",
    "Calvin",
    "Richard",
    "Roy",
    "Ashley",
    "Hal",
    "Anne",
    "Elizabeth",
    "Marie",
};

int haircut_time() {
    return  2 + (rand() % 3);
}

void get_haircut(int t) {
    sleep(t);
}

void cut_hair(int t) {
    sleep(t);
}

void exit_shop() {
    pthread_exit(NULL);
}

void *barber() {
    int num_free_chairs;
    while (true) {
        pthread_mutex_lock(&customers_available_lock);
 	sem_getvalue(&chairs, &num_free_chairs);
        //printf("The barber is taking a nap while waiting for customers.\n");
        pthread_cond_wait(&customers_available, &customers_available_lock);
	//printf("The Barber got woken up\n");
        pthread_mutex_unlock(&customers_available_lock);
        printf("The Barber is ready for the next customer\n");
        pthread_cond_signal(&barber_available);
        cut_hair(2);
        //printf("The Barber is done with the haircut.\n");
    }
}

char *get_name() {
    char *name = names[rand() % 25];
    return name;
}

void *customer(void *n) {
    char *name = n;
    int num_free_chairs;

    printf("%s entered the barber shop.\n", name);
    //if no chairs left, exit barber shop
    pthread_mutex_lock(&chairs_lock);
    sem_getvalue(&chairs, &num_free_chairs);
    if(num_free_chairs == 0) {
        pthread_mutex_unlock(&chairs_lock);
        printf("%s exited the shop because the shop was full.\n", name);
        exit_shop();
    }

    /*if(num_free_chairs == 5){
       printf("%s woke up the Barber.\n", name);
    }*/
    printf("%s is sitting in one of the free chairs.\n", name);
    sem_wait(&chairs);
    pthread_mutex_unlock(&chairs_lock);

    pthread_cond_signal(&customers_available);

    pthread_mutex_lock(&barber_lock);

    printf("%s is waiting.\n", name);

    //wait for the barber
    pthread_cond_wait(&barber_available, &barber_lock);
    pthread_mutex_unlock(&barber_lock);

    printf("%s is getting a haircut.\n", name);
    get_haircut(2);

    printf("%s's haircut is finished.\n", name);
    
    printf("%s exited the barber shop.\n", name);
    //adds one to number of chairs available
    pthread_mutex_lock(&chairs_lock);
    sem_post(&chairs);
    pthread_mutex_unlock(&chairs_lock);

    return NULL;
}

void run() {
    while (true) {
        pthread_t t;
        pthread_create(&t, NULL, customer, get_name());
        pthread_detach(t);
        sleep(rand() %4);
    }
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
       printf("Please run as follows: \nc4 [number of chairs (int)]\n");
       exit(1);
    }
    int num_chairs = atoi(argv[1]);
    //printf("num_chairs: %d\n", num_chairs);
    srand(time(NULL));
    pthread_mutex_init(&chairs_lock, NULL);
    pthread_mutex_init(&customers_available_lock, NULL);
    pthread_mutex_init(&barber_lock, NULL);
    sem_init(&chairs, 0, num_chairs);
    pthread_cond_init(&barber_available, NULL);
    pthread_cond_init(&customers_available, NULL);
    pthread_t barber_thread;
    pthread_create(&barber_thread, NULL, barber, NULL);
    run();
    return pthread_join(barber_thread, NULL);
}
