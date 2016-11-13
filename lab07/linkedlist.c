/***********************************************
*                                              *
*               By: Siri Khalsa                *
*                  11/04/16                    *
*                 CS-241 001                   *
*		    lab07                      *
*     linkedlist.c | defines linked list       *
*                                              *
***********************************************/

#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

void swapFirstLastNode(struct ListNode** headRef);

/********************************************************
 * Parameters:
 * int data- data to be assigned to newly allocated node
 ********************************************************
 * This function mallocs a new listNode with input data
 ********************************************************
 * returns struct ListNode*:  pointer to new node
 ********************************************************/
struct ListNode* createNode(int data)
{
  struct ListNode* node = malloc(sizeof(struct ListNode));
  node->data = data;
  node->next = NULL;
  return node;
}

/********************************************************
 * Parameters:
 * struct ListNode* head- Pointer to Head of LinkedList
 * int data- use data to determine where 
 *           to insert sorted new node
 ********************************************************
 * Insert data at appropriate place in a sorted list
 ********************************************************
 * Returns struct ListNode*: returns pointer to new HEAD
 ********************************************************/
struct ListNode* insertSorted(struct ListNode* head, int data)
{
  /*what do we do with duplicate data? for now I will ignore but need to come back*/
  struct ListNode* current = head;
  if(current == NULL) return createNode(data);
  if(current->data >= data) return pushStack(current, data);
  while(current->next != NULL && (current->next->data) <data)
  {
    current = current->next;
  }
  current->next = pushStack(current->next, data);
  return head;
}

/********************************************************
 * Parameters:
 * struct ListNode** headRef- pointer to the head pointer
 * int data- Search list for data and remove 
 *           node holding data
 ********************************************************
 * This function does:
 * Remove data from list pointed to by headRef,
 * changing head if necessary.
 * Makes no assumptions as to whether the list is sorted.
 * Memory for removed node should be freed.
 ********************************************************
 * Returns 1 if data was present, 0 if not found.
 ********************************************************/
int removeItem(struct ListNode** headRef, int data)
{
  struct ListNode** currentRef = headRef;
  /*check if first node has data and change head to point to second node*/
  if((*headRef)->data == data)
  {
    popStack(headRef);
    return 1;
  }
  /*now move currentRef to hold the address of the "next" 
    That points to the node with the data*/
  while((*currentRef)->next != NULL && (*currentRef)->data != data)
  {
    currentRef = &((*currentRef)->next);
  }
  if((*currentRef)->data == data)
  {
    popStack(currentRef);
    return 1;
  }
  else
  {
    return 0;
  }
}

/********************************************************
 * Parameters:
 * struct ListNode* head - pointer to head node to be pushed
 * int data - data to be added to new node @ head of list
 ********************************************************
 * Insert data at head of list
 ********************************************************
 * returns: 
 * struct ListNode* - new list head 
 ********************************************************/
struct ListNode* pushStack(struct ListNode* head, int data)
{
  struct ListNode* newHead = createNode(data);
  newHead->next = head;
  return newHead;
}

/**********************************************************
 * Parameters:
 * struct ListNode** headRef - pointer to head reference
 **********************************************************
 * free node at head of list and point head to the next node
 * Memory for removed node should be freed. 
 **********************************************************
 * Returns int - data from freed node will be returned
 ***********************************************************/
int popStack(struct ListNode** headRef)
{
  struct ListNode* temp = *headRef;
  int dataToReturn = temp->data;
  *headRef = temp->next;
  free(temp);
  temp = NULL;
  return dataToReturn;
}

/***********************************************************
 * Parameters:
 * struct ListNode* head - pointer to Head node of list
 ***********************************************************
 * this function returns the current length of linked list
 ***********************************************************
 * Return int - length of the list.
 ***********************************************************/
int listLength(struct ListNode* head)
{
  /*i feel like this has a recursive solution
   but I cant figure it out right now*/
  int length = 1;
  struct ListNode* current = head;
  while(current->next != NULL)
  {
    length++;
    current = current->next;
  }
  return length;  
}

/***********************************************************
 * Paramters:
 * struct ListNode* head- point to head node of list
 ***********************************************************
 * Print list data on single line, separated with 
 * spaces and ending with newline. 
 ***********************************************************/
void printList(struct ListNode* head)
{
  struct ListNode* current = head;
  if(current == NULL)
  {
    printf("\n");
    return;
  }
  while (current->next != NULL)
  {
    printf("%d ", current->data );
    current = current->next;
  }
  printf("%d\n", current->data );
}

/***********************************************************
 * Paramters:
 * struct ListNode* head - pointer to the head node of list
 ***********************************************************
 * Free memory used by the list.
 ***********************************************************
 * Returns nothing
 ***********************************************************/
void freeList(struct ListNode* head)
{
  struct ListNode* toFree;
  while((head != NULL) && head->next !=NULL)
  {
    toFree = head;
    head = head->next;
    free(toFree);
  }
}

/***********************************************************
 * Paramters:
 * struct ListNode** headRef - reference to pointer of head node
 ***********************************************************
 * This functions Reverses order of elements in the list 
 ***********************************************************
 * Returns nothing
 ************************************************************/
void reverseList(struct ListNode** headRef)
{
  struct ListNode** currentRef = headRef;
  if(*currentRef->next == NULL) return;
  swapFirstLastNode(currentRef);
  currentRef = &((*headRef)->next);
  reverseList(currentRef);
  
}

/*************************************************************
 * Parameters:
 * struct ListNode** headRef - reference to head*
 *************************************************************
 * The function swaps the first ListNode with the LastNode
 *************************************************************
 * Return void
 *************************************************************/
void swapFirstLastNode(struct ListNode** headRef)
{
  int temp;
  struct ListNode** tailRef = headRef;
  printf("before swap\n");
  printList(*headRef);
  /*check to see if 1 node is passed in just return b/c nothing to swap*/
  if((*headRef)->next == NULL || (*headRef)==NULL) return;
  /*set tailRef to point to a pointer that points to a node with next == null*/
  while((*tailRef)->next != NULL)
  {
    tailRef = &((*tailRef)->next);
  }
  temp = (*tailRef)->data;
  (*tailRef)->data = (*headRef)->data;
  (*headRef)->data = temp;
  printf("after swap\n");
  printList(*headRef);
}
