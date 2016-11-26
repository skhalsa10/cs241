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
  int i;
  struct QueueNode* head = NULL;
  /*initialize array to 0*/
  for(i=0;i<260;i++)
  {
    freqCounter[i] = 0;
  }
 /*the following couple of methods make up the main algorithm*/
  generateFreq(in, freqCounter);
  printFreq(freqCounter);
  head = generateQueue(freqCounter);
  printQueue(head);
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

tNode* buildHuffmanTree(qNode* head)
{

}
