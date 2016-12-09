#ifndef QUEUEANDTREE_H
#define QUEUEANDTREE_H

#include <stdio.h>
#include <stdlib.h>

/*this is the node for the tree*/
struct TreeNode
{
  unsigned char symbol;
  unsigned long freq;
  struct TreeNode* left;
  struct TreeNode* right;
};

/*this is the node for the queue holds a treenode and next*/
struct QueueNode
{
  struct TreeNode* dataNode;
  struct QueueNode* next;
};

/* type def out the annoying struct keyword!*/
typedef struct TreeNode tNode;
typedef struct QueueNode qNode;

/*******************************************************************
 * Parameters:                                                     *
 * unsigned char symbol - value to set as symbol                   *
 * unsigned long freq - value to set as frequency                  *
 *******************************************************************
 * This function dynamically allocates a tNode and                 * 
 * sets symbol and freq to theior respective data members          *                                  *
 *******************************************************************
 * Returns:                                                        *
 * tNode* - pointer to the new tNode                               *
 *******************************************************************/
tNode* createTreeNode(unsigned char symbol, unsigned long freq);
/**************************************************************
* Parameters:                                                 *
* tNode* root - points to root of tree                        *
***************************************************************
* This functions traverses tree and obtains the right mostleaf*                                              *
***************************************************************
* returns symbol in leaf                                      *
***************************************************************/
char getRightLeafSymbol(tNode* root);

/*******************************************************************
 * Parameters:                                                     *
 * tNode* dataNode - tree node to set as dataNode field            *
 *******************************************************************
 * This function dynamically allocates a queueNode and             * 
 * sets dataNode to the parameter                                  *
 *******************************************************************
 * Returns:                                                        *
 * qNode* - pointer to the new qNode                               *
 *******************************************************************/
qNode* createQueueNode(tNode* dataNode);
/*******************************************************************
 * Parameters:                                                     *
 * qNode* head - pointer to the beginning of the queue             *
 * tNode* tNodeToInsert - pointer to a tree node to insert in      *
 *                        queue in a prioritized order             *
 *******************************************************************
 * This function inserts a tNode pointer into a queue pointed to   *
 * by head in a defined prioritized order                          *
 *******************************************************************
 * Returns:                                                        *
 * qNode* - pointer to the head of this queue                      *
 *******************************************************************/
qNode* insertTreeIntoQueue(qNode* head, tNode* tNodeToInsert);
/**************************************************************
* Parameters:                                                 *
* qNode* head - head of queue to insert into                  *
* qNode* qNodeToInsert - queuenode to insert
***************************************************************
* This functions takes a prioritized queue and inserts a queue*
* Node in the correct prioritized location                    *                                              *
***************************************************************
* returns:                                                    *
* qNode* - the new head                                       *
***************************************************************/
qNode* insertQueueIntoQueue(qNode* head, qNode*qNodeToInsert);


#endif