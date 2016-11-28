#include "queueAndTree.h"

/*the first section of this file will define functions for the Tree*/
tNode* createTreeNode(unsigned char symbol, unsigned long freq)
{
  tNode* node = malloc(sizeof(tNode));
  node->symbol = symbol;
  node->freq = freq;
  node->left = NULL;
  node->right = NULL;
  return node;
}


/*this second part of this file will define functions for the Queue*/
qNode* createQueueNode(tNode* dataNode)
{
  qNode* node = malloc(sizeof(qNode));
  node->dataNode = dataNode;
  node->next = NULL;
  return node;
}
/*******************************************************************
 * Parameters:
 * qNode* head - pointer to the beginning of the queue
 * tNode* tNodeToInsert - pointer to a tree node to insert in 
 *                        queue in a prioritized order
 *******************************************************************
 * This function inserts a tNode pointer into a queue pointed to 
 * by head in a defined prioritized order
 *******************************************************************
 * Returns:
 * qNode* - pointer to the head of this queue
 *******************************************************************/
qNode* insertTreeIntoQueue(qNode* head, tNode* tNodeToInsert)
{
  qNode* temp; 
  /*if the head is NULL just create a new 
    qNode and returnt he pointer to it*/
  if (head == NULL)
  {
    return createQueueNode(tNodeToInsert);
  }
  /*if the frequency of the tnode to insert 
    is smaller than the head's dataNodes's frequency
    we need to insert at the head and return new head*/
  if(tNodeToInsert->freq < (head->dataNode->freq))
  {
    temp = createQueueNode(tNodeToInsert);
    temp->next = head;
    head = temp;
    return head;
  }
  /*if freq is the same need to compare symbol*/
  if(tNodeToInsert->freq == (head->dataNode->freq))
  {
    /*if symbol is greater insert before and return head*/
    if(tNodeToInsert->symbol > head->dataNode->symbol)
    {
      temp = createQueueNode(tNodeToInsert);
      temp->next = head;
      head = temp;
      return head;
    }
  }
  /*if freq greater than heads dataNode or if freqs
   are the same but symbol is smaller than dataNodes->symbol 
   recursively call this function with the head as next*/
  head->next = insertTreeIntoQueue(head->next, tNodeToInsert);
  /*return original head*/
  return head;
}
qNode* insertQueueIntoQueue(qNode* head, qNode* qNodeToInsert)
{
  qNode* temp = NULL;
  if(head==NULL) return qNodeToInsert;
  if(head->next == NULL) return head;
  if(qNodeToInsert->dataNode->freq < head->dataNode->freq)
  {
    temp = qNodeToInsert;
    temp->next = head;
    head = temp;
    return head;
  }
  if(qNodeToInsert->dataNode->freq == head->dataNode->freq)
  {
    if(getRightLeafSymbol(qNodeToInsert->dataNode) 
      > getRightLeafSymbol(head->dataNode))
    {
      temp = qNodeToInsert;
      temp->next = head;
      head = temp;
      return head;
    }
  }
  head->next = insertQueueIntoQueue(head->next, qNodeToInsert);
  return head;
}

char getRightLeafSymbol(tNode* root)
{
  if(root->right ==NULL) return root->symbol;
  return getRightLeafSymbol(root->right);
}