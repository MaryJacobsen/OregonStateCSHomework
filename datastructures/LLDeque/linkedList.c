#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list)
{
	// FIXME: you must write this
	list->frontSentinel = malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);
	list->backSentinel = malloc(sizeof(struct Link));
	assert(list->backSentinel);
	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	struct Link* newLink = malloc(sizeof(struct Link)); //allocate memory for newLink
	assert(newLink != 0);
	//adjust pointers
	link->prev->next = newLink;
	newLink->prev = link->prev;
	newLink->next = link;
	newLink->prev->next = newLink;
	link->prev = newLink;
	newLink->value = value; //update value for newLink
	list->size++; //update size of linked list
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this
	assert(! linkedListIsEmpty(list));
	link->prev->next = link->next; //adjust pointers
	link->next->prev = link->prev;
	list->size--; //update size of linked list
	free(link); //free memory associated with lnk
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	return list->frontSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this
	if(list->size == 0){
		return 1;
	}
	return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this
	printf("\n");
	struct Link* tempLink = list->frontSentinel->next; //create temp link to cycle through list equal to first link
	while(tempLink != list->backSentinel) //while we haven't reached the end of the list
	{
		printf("%d\n", tempLink->value);
		tempLink = tempLink->next;
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	linkedListAddFront(list, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	struct Link* tempLink = list->frontSentinel->next; //create temp link to cycle through list equal to first link

	while(tempLink != list->backSentinel) //while we haven't reached the end of the list
	{
		if(EQ(value,tempLink->value)) //if value is equal to the value in tempLink
			return 1; //linked list contains the value
		tempLink = tempLink->next; //if value not found, set tempLink to the next link in the chain
	}

	return 0; //if value is not found before the backSentinel is reached, return 0
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	struct Link* tempLink = list->frontSentinel->next; //create temp link to cycle through list equal to first link

	while(tempLink->next != list->backSentinel) //while we haven't reached the end of the list
	{
		if(EQ(value,tempLink->value)) //if value is equal to the value in tempLink
		{
			removeLink(list, tempLink); //remove that link
			return; //terminate function after link is removed
		}
		tempLink = tempLink->next; //if value not found, set tempLink to the next link in the chain
	}
}
