#include <stdio.h>
#include "huffman.h"
#include "queueAndTree.h"


/*encodes file*/
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
  /*count frequency of symbols in file pointed to by in*/
  generateFreq(in, freqCounter);
  printFreq(freqCounter);
  head = generateQueue(freqCounter);
  printQueue(head);
}


void generateFreq(FILE* in, unsigned long freqCounter[])
{
  int c;
  while((c=getc(in)) != EOF)
  {
    freqCounter[c]++;
  }
}

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


void printQueue(qNode* head)
{
  qNode* current = head;
  printf("___________PRINTING QUEUE_______________\n");
  while(current != NULL)
  {
    if(current->dataNode->symbol<33||current->dataNode->symbol>126)
    {
      printf("=%d\t%d\n",current->dataNode->symbol, current->dataNode->freq);
    }
    printf("%c\t%d\n",current->dataNode->symbol, current->dataNode->freq);
    current = current->next;
  }

}

struct QueueNode* generateQueue(unsigned long freqCounter[])
{
  struct QueueNode* head = NULL;
  unsigned char i;
  for(i=0; i<260; i++)
  {
    if(freqCounter[i] != 0)
    {
      head = insertTreeIntoQueue(head, createTreeNode(i,freqCounter[i]));
    }
  }

  return head;
}