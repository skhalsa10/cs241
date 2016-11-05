/***********************************************
*                                              *
*               By: Siri Khalsa                *
*                  11/04/16                    *
*                 CS-241 001                   *
*		                lab07                      *
*     linkedlist.c | defines linked list       *
*                                              *
***********************************************/

#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

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
  if(current->data > data) return pushStack(head);
  while(corrent->next != NULL && (current->next->data) <data)
  {
    current = current->next;
  }
  current->next = pushStack(current->next);
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
  /*again this function could change based on duplicate
   data if there is duplicate do we delete all nodes containing?
    need more info but making a rough draft for now*/

  /*find node that has data and point headRef to a pointer that point to it*/
  while((*headRef)->next != NULL && (*headRef)->data != data)
  {
    *headRef = (*headRef)->next;
  }
  if((*headRef)->data == data)
  {
    popStack(headRef);
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
  while(head->next !=NULL)
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
  while((*headRef != NULL))
  {
    swapFirstLastNode(headRef);
    (*headRef) = (*headRef)->next;
    reverseList(headRef);
  }
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
  struct ListNode** tailRef = headRef;
  while((*tailRef)->next != NULL)
  {
    *tailRef = (*tailRef)->next;
  }
  (*tailRef)->next = *headRef;
  (*headRef) = (*tailRef);
  *tailRef = NULL;
}
