#ifndef QUEUEANDTREE_H
#define QUEUEANDTREE_H

#include <stdio.h>
/*#include <stdlib.h>*/

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

/* declare tree related functions*/
tNode* createTreeNode(unsigned char symbol, unsigned long freq);


/*declare queue related functions*/
qNode* createQueueNode(tNode* dataNode);
qNode* insertTreeIntoQueue(qNode* head, tNode* tNodeToInsert);
qNode* insertQueueIntoQueue(qNode* head, qNode*qNodeToInsert);


#endif