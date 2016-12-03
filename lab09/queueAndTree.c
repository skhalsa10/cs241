#include "queueAndTree.h"

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
tNode* createTreeNode(unsigned char symbol, unsigned long freq)
{
  tNode* node = malloc(sizeof(tNode));
  node->symbol = symbol;
  node->freq = freq;
  node->left = NULL;
  node->right = NULL;
  return node;
}

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
qNode* createQueueNode(tNode* dataNode)
{
  qNode* node = malloc(sizeof(qNode));
  node->dataNode = dataNode;
  node->next = NULL;
  return node;
}
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
qNode* insertQueueIntoQueue(qNode* head, qNode* qNodeToInsert)
{
  qNode* temp = NULL;
  if(head==NULL) return qNodeToInsert;
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

/**************************************************************
* Parameters:                                                 *
* tNode* root - points to root of tree                        *
***************************************************************
* This functions traverses tree and obtains the right mostleaf*                                              *
***************************************************************
* returns symbol in leaf                                      *
***************************************************************/
char getRightLeafSymbol(tNode* root)
{
  if(root->right ==NULL) return root->symbol;
  return getRightLeafSymbol(root->right);
}