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
  head = generateQueue(freqCounter);
  head = buildHuffmanTree(head);
  root = head->dataNode;
  generateCodes(symbolCodes, root, code);
  printSymbolCodes(freqCounter, symbolCodes);
  createEncodedFile(in, out, symbolCodes, freqCounter);
  
  /*perform all shut down tasks*/
  head->dataNode = NULL;
  head->next = NULL;
  free(head);
  freeAllMemory(root, symbolCodes, freqCounter);

}

/**************************************************************
* Parameters:                                                 *
* tNode* root - pointer to root of tree                       *
* char* symbolCodes[] - array that holds codes                *
* unsigned long freqCounter[] - used to pinpoint  where       *
*                               malloced codes are stored     *
***************************************************************
* This functions first frees all malloced strings in          *
* symbolCodes then freeTree is calle on root to free all Nodes*
***************************************************************
* returns  Nothing                                            *
***************************************************************/
void freeAllMemory(tNode* root, char* symbolCodes[], unsigned long freqCounter[])
{
  int i;
  for(i = 0; i<260;i++)
  {
    if(freqCounter[i] != 0)
    {
      free(symbolCodes[i]);
    }
  }
  freeTree(root);
}

/* Free memory used by the tree. */
void freeTree(tNode* root)
{
    if(root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void createEncodedFile(FILE* in, FILE* out,char* symbolCodes[],unsigned long freqCounter[])
{
  
  rewind(in);
  rewind(out);
  buildHeader(out, freqCounter);
  encodeTheData(in,out, symbolCodes[]);

}

void encodeTheData(FILE* in,FILE* out,char* symbolCodes[])
{
  int c;
  unsigned char byteToWrite;
  unsigned char codeLength;
  unsigned long code;
  unsigned char bitsAvailable = 8;
  cIsUsedUp = FALSE;
  while((c = getc(in)) != EOF)
  {
    codeLength = getCodeLength(symbolCodes[c]);
    code = convertCode(symbolCodes[c]);
    cIsUsedUp = FALSE;
    while(!cIsUsedUp)
    {
      if(codeLength>bitsAvailable)
      {
        codeLength -= bitsAvailable;
        byteToWrite = byteToWrite | (char)(code>>length);
        fwrite(&byteToWrite,1,1,out);
        code = code & ~((~0)<<length);
        byteToWrite = 0;
        bitsAvailable = 8;
      }
      if(codeLength == bitsAvailable)
      {
        byteToWrite = byteToWrite | code;
        fwrite(&byteToWrite,1,1,out);
        byteToWrite = 0;
        bitsAvailable = 8;
        cIsUsedUp = TRUE;
      }
      if(codeLength < bitsAvailable)
      {
        byteToWrite = byteToWrite | code<<(bitsAvailable-codeLength);
        bitsAvailable +=codeLength;
        cIsUsedUp = TRUE;
      }
    }
  }

}

unsigned long convertCode(char* code)
{
  unsigned long convertedCode = 0;
  while(*code != '\0')
  {
    if(*code == '1')
    {
      convertedCode = convertCode<<1 & 1;
    }
    else
    {
      convertedCode = convertedCode<<1;
    }
    code++;
  }
  return convertedCode;
}
unsigned char getCodeLength(char* code)
{
  unsigned char codeLength = 0;
  while(*code != '\0')
  {
    codeLength++;
    code++;
  }
  return  codeLength;
}
void buildHeader(FILE* out, unsigned long freqCounter[])
{
  int i;
  unsigned long totalChars = 0;
  unsigned char totalSymbols = 0;
  totalSymbols = getTotalSymbols(freqCounter);
  fwrite(&totalSymbols, 1, 1,out);
  for(i=0;i<260;i++)
  {
    if(freqCounter[i] != 0)
    {
      if(i<256)
      {
        fwrite(&i,1,1,out);
      }
      else 
      {
        printf("ERROR");
      }
      fwrite(&freqCounter[i],8,1,out);
    }
  }
  totalChars = getTotalChars(freqCounter);
  fwrite(&totalChars, 8, 1,out);
}

unsigned long getTotalChars(unsigned long freqCounter[])
{
  int i;
  unsigned long totalChars=0;
  for(i = 0; i<260;i++)
  {
    if(freqCounter[i] != 0)
    {
      totalChars += freqCounter[i];
    }
  }
  return totalChars;
}
unsigned char getTotalSymbols(unsigned long freqCounter[])
{
  int i;
  unsigned char totalSymbols = 0;

  for(i = 0; i < 260; i++)
  {
    if(freqCounter[i] != 0)
    {
      totalSymbols++;
    }
  }
  return totalSymbols;
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

/**************************************************************
* Parameters:                                                 *
* unsigned long freqCounter[] -  the array that holds         *
*                                all frequency counts         *
* char* symbolCodes[] - the array that holds the codes        *
***************************************************************
* This functions prints out the character the frequency       *
* and the code                                                *
***************************************************************
* returns nothingnbut permanently changes array parameter     *
***************************************************************/
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

/*********************************************************************
* Parameter:                                                         *
* char* symbolCodes[] - array to hold the codes                      *
* tNode* root - pointer to root of huffman tree                      *
* char* code - string to hold the code until a leaf is discovered    *
**********************************************************************
* This Function traverses the tree and generates codes. it is a      *
* recursive function that traverses the tree each time it is called  *
* the string input will get a 1 or a 0 depending on the direction    *
* of the traversal                                                   *
**********************************************************************
* Returns:                                                           *
* Nothing                                                            *
**********************************************************************/
void generateCodes(char* symbolCodes[], tNode* root, char* code)
{
  char* leftCode = malloc(sizeof(char)*260);
  char* rightCode = malloc(sizeof(char)*260);
  if(root == NULL)
  {
    free(leftCode);
    free(rightCode);
    return;
  } 
  if(root->left == NULL && root->right == NULL)
  {
    symbolCodes[(int)root->symbol] = code;
    free(leftCode);
    free(rightCode);
    return;
  }
  if(root->left != NULL)
  {
    
    copyStringWithC(code, leftCode, '0');
    generateCodes(symbolCodes, root->left, leftCode);
  }
  if(root->right != NULL)
  {
    copyStringWithC(code, rightCode, '1');
    generateCodes(symbolCodes, root->right, rightCode);
  }
  free(code);
}

/*********************************************************************
* Parameter:                                                         *
* char* copyFrom - string that will be copied                        *
* char* copyTo - pointer tht string will be copied to                *
* char addToEnd - this char gets tacked on to the end                *
**********************************************************************
* This Function copies the content of copyFrom into copyTo and       *
* then adds addToEnd to the end                                      *
* NOTE: this function assumes the strings are never longer then 260  *
* characters                                                         *
**********************************************************************
* Returns:                                                           *
* Nothing                                                            *
**********************************************************************/
void copyStringWithC(char* copyFrom, char* copyTo, char addToEnd)
{
  int i;
  for(i=0;i<260;i++)
  {
    copyTo[i] = '\0';
  }
  i = 0;
  while((*copyFrom) != '\0')
  {
    copyTo[i] = *copyFrom;
    i++;
    copyFrom++;
  }
  copyTo[i] = addToEnd;
}