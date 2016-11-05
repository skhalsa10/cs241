/***********************************************
*                                              *
*               By: Siri Khalsa                *
*                  11/04/16                    *
*                 CS-241 001                   *
*		    lab07                      *
*     linkedlist.c | defines linked list       *
*                                              *
***********************************************/

#include <linkedlist.h>

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
  
}

/***********************************************************
 * Paramters:
 * struct ListNode* headRef - reference to pointer of head node
 ***********************************************************
 * This functions Reverses order of elements in the list 
 ***********************************************************
 * Returns nothing
 ************************************************************/
void reverseList(struct ListNode** headRef)
{
  
}
