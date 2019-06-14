/*
 * CS 261 Assignment 5
 * Name: Mary Jacobsen
 * Date: 7-27-16
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
*Compares a task with each task already in the heap.   
*@param heap
*@param the new task to compare to the heap 
*@Returns: 0 if not present, 1 if present  
*/

int duplicateCheck(DynamicArray *heap, struct Task *task)
{
 // FIXME: Implement
	int i;
	struct Task *temp;
	for(i=0; i<dySize(heap); i++)
	{
		temp = (struct Task*)dyGet(heap, i);
		if(taskCompare(dyGet(heap, i), task) == 0 && strcmp(temp->name, task->name) == 0)
			return 1;
	}
	return 0;
}

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n\r]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &(temp.priority), &(temp.name)) == 2)
    { 
	struct Task *newTask = taskNew(temp.priority, temp.name);           
  	if (duplicateCheck(heap, newTask) == 0){        
	   dyHeapAdd(heap, newTask, taskCompare);
	}      
    }     

 }


/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    int i;
    for (i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
	if(command == 'l')
	{
		FILE *file;
		char fileName[128];
		printf("Please enter the filename: ");
		scanf("%s", fileName);
		printf("fileName: %s\n", fileName);
		file = fopen(fileName, "r");
		listLoad(list, file);
		printf("\nThe list has been loaded successfully.\n\n");
	}
	else if(command == 's')
	{
	   	if(dySize(list) == 0)
		{
		   printf("Your to-do list is empty!\n\n");
		   return;
		}
		FILE *file;
		char fileName[128];
		printf("Please enter the filename: ");
		scanf("%s", fileName);
		file = fopen(fileName, "w");
		listSave(list, file);
		printf("\nThe list has been saved to the file successfully.\n\n");
	}
	else if(command == 'a')
	{
		struct Task *newTask, temp;
		printf("Please enter the task description: ");
		scanf("%[^\n]", temp.name);
		printf("\nPlease enter the task priority (0-999): ");
		scanf("%d", &(temp.priority));
		newTask = taskNew(temp.priority, temp.name);
	  	if (duplicateCheck(list, newTask) == 0)
		{        
	   	   dyHeapAdd(list, newTask, taskCompare);
		} 
		printf("\nThe task '%s' has been added to your to-do list.\n\n", newTask->name);
	}
	else if(command == 'g')
	{
		if(dySize(list) == 0)
		{
		   printf("Your to-do list is empty!\n\n");
		   return;
		}
		struct Task *t = dyHeapGetMin(list);
		printf("\nYour first task is: '%s'\n\n", t->name);
	}
	else if(command == 'r')
	{
		if(dySize(list) == 0)
		{
		   printf("Your to-do list is empty!\n\n");
		   return;
		}
		struct Task *t = dyHeapGetMin(list);
		printf("\nYour first task '%s' has been removed from the list.\n\n", t->name);
		dyHeapRemoveMin(list, taskCompare);
	}
	else if(command == 'p')
	{
		if(dySize(list) == 0)
		{
		   printf("Your to-do list is empty!\n\n");
		   return;
		}
		listPrint(list);
		printf("\n");
	}
	else if(command == 'e')
	{
		printf("Bye!\n\n");
	}
	else
	   printf("Not a valid command\n");
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );

	do
	{
           command = getchar();
	}
	while(command == '\n');
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}
