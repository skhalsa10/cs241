#include "queueAndTree.h"
#include <stdio.h>
#include <stdlib.h>

void printQueue(qNode* head);

void main()
{
  qNode* head = NULL;
  head = insertTreeIntoQueue(head, createTreeNode('s', 5280));
  head = insertTreeIntoQueue(head, createTreeNode(10, 264));
  head = insertTreeIntoQueue(head, createTreeNode(32, 1065));
  head = insertTreeIntoQueue(head, createTreeNode('p', 2640));
  head = insertTreeIntoQueue(head, createTreeNode('m', 1320));
  head = insertTreeIntoQueue(head, createTreeNode('i', 5280));
  printQueue(head);
}

void printQueue(qNode* head)
{
  qNode* current = head;
  printf("___________PRINTING QUEUE_______________\n");
  while(current != NULL)
  {
    if(current->dataNode->symbol<33||current->dataNode->symbol>126)
    {
      printf("=%d\t%lu\n",current->dataNode->symbol, current->dataNode->freq);
    }
    printf("%c\t%lu\n",current->dataNode->symbol, current->dataNode->freq);
    current = current->next;
  }

}