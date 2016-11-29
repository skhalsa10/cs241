#include <stdio.h>
#include "huffman.h"
#include "queueAndTree.h"


/**************************************************************/
/* Huffman encode a file.                                     */
/*     Also writes freq/code table to standard output         */
/* in -- File to encode.                                      */
/*       May be binary, so don't assume printable characters. */
/* out -- File where encoded data will be written.            */
/**************************************************************/
void encodeFile(FILE* in, FILE* out)
{
  unsigned long freqCounter[260];
  char* symbolCodes[260];
  char* code = malloc(sizeof(char)*260);
  int i;
  struct QueueNode* head = NULL;
  tNode* root = NULL;
  /*initialize array to 0*/
  for(i=0;i<260;i++)
  {
    freqCounter[i] = 0;
  }
  /*the following couple of methods make up the main algorithm*/
  generateFreq(in, freqCounter);
  /*rewind in to the beginning*/
  rewind(in);
  printFreq(freqCounter);
  head = generateQueue(freqCounter);
  printQueue(head);
  head = buildHuffmanTree(head);
  printQueue(head);
  root = head->dataNode;
  generateCodes(symbolCodes, root, code);
  printSymbolCodes(freqCounter, symbolCodes);
}

/**************************************************************
* Parameters:                                                 *
* FILE* in - file stream to analyze                           *
* unsigned int freqCounter[]- array that will hold freq count *
***************************************************************
* This functions interates over every char in a FILE stream   *
* and counts and stores how many times each symbol is used    *
***************************************************************
* returns nothingbut permanently changes array parameter      *
***************************************************************/
void generateFreq(FILE* in, unsigned long freqCounter[])
{
  int c;
  while((c=getc(in)) != EOF)
  {
    freqCounter[c]++;
  }
}

/*may get rid of this*/
void printFreq(unsigned long freqCounter[])
{
  int i;
  unsigned long totalChars = 0;
  printf("Symbol\tFreq\n");
  for(i=0;i<260;i++)
  {
    if(freqCounter[i] != 0)
    {
      totalChars += freqCounter[i];
      if(i<33||i>126)
      {
        printf("=%d\t%lu\n",i, freqCounter[i]);
      }
      else
      {
        printf("%c\t%lu\n",i, freqCounter[i]);
      }
    }
  }
  printf("Total chars = %lu\n", totalChars);
}

void printSymbolCodes(unsigned long freqCounter[], char* symbolCodes[])
{
  int i;
  printf("Symbol\tFreq\tCode\n");
  for (i=0;i<260;i++)
  {
    if(freqCounter[i] != 0)
    {
      if(i<33||i>126)
      {
        printf("=%d\t%lu\t%s\n",i, freqCounter[i], symbolCodes[i]);
      }
      else
      {
        printf("%c\t%lu\t%s\n",i, freqCounter[i], symbolCodes[i]);
      }
    }
  }
}

/*********************************************************************
* Parameters:                                                        *
* struct QueueNode* head - pointer to head of Queue to be printed    *
**********************************************************************
* This function will print out a priority queue it will              *
* print the DataNode's symbol and frequency of the symbol            *
**********************************************************************
* Nothing is returned                                                *
**********************************************************************/
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
    else
    {
      printf("%c\t%lu\n",current->dataNode->symbol, current->dataNode->freq);
    }
    current = current->next;
  }
}

/*********************************************************************
* Parameters:                                                        *
* unsigned long freqCounter[] - array index is the char with         *
*                               a frequency associated with the char *
**********************************************************************
* This function generates a priority queue out of array. The array   *
* will have room for all possible char values. this function expects *
* the frequencies to already have been counted. it will find a char  *
* with frequence > 0 create a Tree node and add to queue             *
**********************************************************************
* Return:                                                            *
* qNode* - the head to teh front of the queue                        *
**********************************************************************/
qNode* generateQueue(unsigned long freqCounter[])
{
  struct QueueNode* head = NULL;
  unsigned char i;
  for(i=0; i<255; i++)
  {
    if(freqCounter[i] != 0)
    {
      head = insertTreeIntoQueue(head, createTreeNode(i,freqCounter[i]));
    }
  }
  if(freqCounter[255] != 0)
  {
    head = insertTreeIntoQueue(head, createTreeNode(255,freqCounter[255]));
  }
  return head;
}
/*********************************************************************
* Parameter:                                                         *
* qNode* head - pointer to the head of the Priority Queue to build   *
*               Huffman tree from                                    *
**********************************************************************
* This Function takes a prioritized queue and creates a huffman tree *
* by doing the following:                                            *
* While queue has more than one item:                                *
* – Remove two trees from queue.                                     *
* – Create new tree with those two as children. (First removed       *
* should be left child.) Tree frequency count is sum of              *
* children’s counts.                                                 *
* – Add new tree to priority queue.                                  *
**********************************************************************
* Returns:                                                           *
* qNode* - the address of the head of the queue with one item        *
* this head->dataNode is the root of the huffman tree that was built *
**********************************************************************/
qNode* buildHuffmanTree(qNode* head)
{
  qNode* left;
  qNode* right;
  unsigned long newFreq;
  tNode* newTree;

  /*if head is null return head if head->next is null return head->dataNode
  this completed the returns needed for recursive use of this function*/
  if(head == NULL || head->next == NULL) 
  {
    return head;
  }
    
  left = head;
  right = head->next;
  head = right->next;
  newFreq = (left->dataNode->freq)+(right->dataNode->freq);

  newTree = createTreeNode('\0',newFreq);
  newTree->left = left->dataNode;
  newTree->right = right->dataNode;

  /*free the left qNode and modify the right to hold the newTree*/
  left->dataNode = NULL;
  left->next = NULL;
  free(left);
  right->dataNode = newTree;
  right->next = NULL;
  /*insert modified right qnode into queue with correct priority*/
  head = insertQueueIntoQueue(head,right);
  /*repeat until one qnode is left*/
  head = buildHuffmanTree(head);
  
  return head;
}

void generateCodes(char* symbolCodes[], tNode* root, char* code)
{
  if(root == NULL) return;
  if(root->left == NULL && root->right == NULL)
  {
    symbolCodes[(int)root->symbol] = code;
  }
  if(root->left != NULL)
  {
    generateCodes(symbolCodes, root->left, addZero(code));
  }
  if(root->right != NULL)
  {
    generateCodes(symbolCodes, root->left, addOne(code));
  }
}

char* addZero(char* code)
{
  char* temp = malloc(sizeof(char)*260);
  int i;

  for(i=0;i<260;i++)
  {
    temp[i] = '\0';
  }
  i = 0;
  while((*code) != '\0')
  {
    temp[i] = *code;
    i++;
    code++;
  }
  temp[i] = '0';
  free(code);
  return temp;
}

char* addOne(char* code)
{
  char* temp = malloc(sizeof(char)*260);
  int i;

  for(i=0;i<260;i++)
  {
    temp[i] = '\0';
  }
  i = 0;
  while((*code) != '\0')
  {
    temp[i] = *code;
    i++;
    code++;
  }
  temp[i] = '1';
  free(code);
  return temp;
}