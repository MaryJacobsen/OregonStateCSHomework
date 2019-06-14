#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

struct linkedList {
    int data;
    struct linkedList *next;
}*head;

pthread_mutex_t search_lock;
pthread_mutex_t insert_lock;
pthread_mutex_t delete_lock;

int nodeCount(){
    struct linkedList *temp;
    int i=0;
    temp = head;
    while (temp != NULL){
        temp = temp->next;
        i++;
    }
    return i;
}

void searcher() {
    struct linkedList *temp;
    while (1) {
        if (!pthread_mutex_trylock(&search_lock)){
            temp = head;
            if (temp == NULL){
                printf("Searching: \nthe list is empty\n");
                continue;
            } 
	    else{
		printf("Searching:\n");
                while (temp != NULL){
                    printf("[%d] ", temp->data);
                    temp = temp->next;
                }
                printf("\n\n");
            }
            pthread_mutex_unlock(&search_lock);
        }
        sleep(1);
    }
}

void inserter() {
    struct linkedList *temp, **tail;
    int insertItem, i;
    srand(time(NULL));
    while (1){
        if (nodeCount() < 20){
            if (!pthread_mutex_lock(&insert_lock)){
                temp = (struct linkedList *)malloc(sizeof(struct linkedList));
                insertItem = rand() %10;
                printf("Inserting %d\n\n", insertItem);
                temp->data = insertItem;
                temp->next = NULL;
                tail = &head;
                if (head == NULL){
                    head = temp;
                } 
		else {
                    while (*tail != NULL){
                        tail = &((*tail)->next);
                    }
                    *tail = temp;
                }
                pthread_mutex_unlock(&insert_lock);
                sleep(5);
            }
        }
    }
}

void deleter() {
    int deleteItem;
    struct linkedList *temp, *prev;
    srand(time(NULL));
    while (1){
        if (nodeCount() > 1){
            if (!pthread_mutex_trylock(&insert_lock)){
                if(!pthread_mutex_trylock(&search_lock)){
                    temp = head;
                    deleteItem = rand() %10;
                    while (temp != NULL) {
                        if(temp->data == deleteItem){
                            printf("Deleting %d\n\n", deleteItem);
                            if (temp == head){
                                head = temp->next;
                                free(temp);
                                break;
                            } 
			    else {
                                prev->next = temp->next;
                                free(temp);
                                break;
                            }
                        } 
			else {
                            prev = temp;
                            temp = temp->next;
                        }
                    }
                    pthread_mutex_unlock(&search_lock);
                }
                pthread_mutex_unlock(&insert_lock);
            }
            sleep(2);
        }
    }
}

int main(){
    int i = 0;
    struct linkedList *l;
    l = (struct linkedList *)malloc(sizeof(struct linkedList));
    srand(time(NULL));
    l->data = rand() %10;
    head = l;
    head->next = NULL;

    pthread_t search_thread[3];
    pthread_t insert_thread[3];
    pthread_t delete_thread[3];

    for(i = 0; i < 3; i++){
        if(pthread_create(&search_thread[i], NULL, (void *)searcher, (void *)NULL)) {
            fprintf(stderr, "Error creating search thread\n");
            return 1;
        }
        if(pthread_create(&insert_thread[i], NULL, (void *)inserter, (void *)NULL)) {
            fprintf(stderr, "Error creating insert thread\n");
            return 1;
        }
        if(pthread_create(&delete_thread[i], NULL, (void *)deleter, (void *)NULL)) {
            fprintf(stderr, "Error creating delete thread\n");
            return 1;
        }
    }
    for(i = 0; i < 3; i++){
        pthread_join(search_thread[i], NULL);
        pthread_join(insert_thread[i], NULL);
        pthread_join(delete_thread[i], NULL);
    }
    return 0;
}	
