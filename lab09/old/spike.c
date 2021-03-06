#include "queueAndTree.h"
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>

void printQueue(qNode* head);

void main()
{
  qNode* head = NULL;
  qNode* head2 = NULL;
  qNode* max = NULL;
  qNode* middle = NULL;
  qNode* small = NULL;
  
  head = insertTreeIntoQueue(head, createTreeNode('s', 5280));
  head = insertTreeIntoQueue(head, createTreeNode('p', 2640));
  head = insertTreeIntoQueue(head, createTreeNode('i', 5281));
  head = insertTreeIntoQueue(head, createTreeNode('m', 1320));
  head = insertTreeIntoQueue(head, createTreeNode(32, 1065));
  head = insertTreeIntoQueue(head, createTreeNode(10, 264));
  printQueue(head);

  max = createQueueNode(createTreeNode(0, 7920));
  max->dataNode->left = createTreeNode('p',2640);
  max->dataNode->right = createTreeNode('s', 5280);
  
  middle = createQueueNode(createTreeNode(0, 7920));
  middle->dataNode->left = createTreeNode('t',2640);
  middle->dataNode->right = createTreeNode('u', 5280);
  
  small = createQueueNode(createTreeNode(0, 3));
  small->dataNode->left = createTreeNode('a',1);
  small->dataNode->right = createTreeNode('b', 2);
  head2 = insertQueueIntoQueue(head2, small);
  head2 = insertQueueIntoQueue(head2, max);
  head2 = insertQueueIntoQueue(head2, middle);

  printQueue(head2);
}
