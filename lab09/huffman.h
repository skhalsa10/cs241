#ifndef HUFFMAN_H
#define HUFFMAN_H

/* Including stdio so we'll know about FILE type */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "queueAndTree.h"
#define FALSE 0
#define TRUE 1

struct code96Bit
{
  unsigned long part1;
  unsigned long part2;
  unsigned long part3;
  unsigned char length;
};

typedef struct code96Bit c96b;
/* The following 2 functions are used in my huffencode and huffdecode
   programs. You'll need to write them if you want to use my code.  */

/**************************************************************/
/* Huffman encode a file.                                     */
/*     Also writes freq/code table to standard output         */
/* in -- File to encode.                                      */
/*       May be binary, so don't assume printable characters. */
/* out -- File where encoded data will be written.            */
/**************************************************************/
void encodeFile(FILE* in, FILE* out);

/***************************************************/
/* Decode a Huffman encoded file.                  */
/* in -- File to decode.                           */
/* out -- File where decoded data will be written. */
/***************************************************/
void decodeFile(FILE* in, FILE* out);

c96b* convertDecodeCode(char* code);
void createDecodedFile(FILE* in, FILE* out,char* symbolCodes[],unsigned long freqCounter[]);
void generateDecodeFreq(unsigned char totalSymbols,FILE* in,unsigned long freqCounter[]);
int checkCodeAndWrite(c96b* code, FILE* out,char* symbolCodes[],unsigned long freqCounter[])
;
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
void generateFreq(FILE* in, unsigned long freqCounter[]);
/**************************************************************
* Parameters:                                                 *
* unsigned int freqCounter[]- use this to print out freq      *
***************************************************************
* This functions iterates over the array and prints out       *
* the freq associated with the char number                    *
***************************************************************
* returns nothing                                             *
***************************************************************/
void printFreq(unsigned long freqCounter[]);

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
qNode* generateQueue(unsigned long freqCounter[]);
/*********************************************************************
* Parameters:                                                        *
* struct QueueNode* head - pointer to head of Queue to be printed    *
**********************************************************************
* This function will print out a priority queue it will              *
* print the DataNode's symbol and frequency of the symbol            *
**********************************************************************
* Nothing is returned                                                *
**********************************************************************/
void printQueue(struct QueueNode* head);
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
* qNode* - the address of the root of the new tree                   *
**********************************************************************/
qNode* buildHuffmanTree(qNode* head);
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
void generateCodes(char* symbolCodes[], tNode* root, char* code);
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
void printSymbolCodes(unsigned long freqCounter[], char* symbolCodes[]);
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
void copyStringWithC(char* copyFrom, char* copyTo, char addToEnd);
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
void freeAllMemory(tNode* root, char* symbolCodes[], unsigned long freqCounter[]);
/**************************************************************
* Parameters:                                                 *
* FILE* in - file to encode                                   *
* FILE* out - file to write the encoded data to               *
* char* symbolCodes[] - array of Symbols to codes             *
* unsigned long freqCounter[] - array that holds symbol-freq  *
***************************************************************
* This function writes the header and then the encoded data   *
* to out                                                      *
***************************************************************
* returns nothing                                             *
***************************************************************/
void createEncodedFile(FILE* in, FILE* out, char* symbolCodes[],unsigned long freqCounter[]);
/* Free memory used by the tree. */
void freeTree(tNode* root);
/**************************************************************
* Parameters:                                                 *
* unsigned long freqCounter[] - array that has list of symbols*
***************************************************************
* This functions interates over the freqCounter array and     *
* adds up all frequencies.                                    *
***************************************************************
* returns the total amount chars in file                      *
***************************************************************/
unsigned long getTotalChars(unsigned long freqCounter[]);
/**************************************************************
* Parameters:                                                 *
* FILE* out- file to write header to                          *
* unsigned long freqCounter[] - array that has list of symbols*
***************************************************************
* This functions writes ehader to file                        *
***************************************************************
* returns nothing                                             *
***************************************************************/
void buildHeader(FILE* out, unsigned long freqCounter[]);
/**************************************************************
* Parameters:                                                 *
* FILE* in - file to encode                                   *
* FILE* out - file to write the encoded data to               *
* char* symbolCodes[] - array of SYmbols to codes             *
***************************************************************
* This function encodes in with codes from symbolCodes and    *
* and writes it to out                                        *
***************************************************************
* returns nothing                                             *
***************************************************************/
void encodeTheData(FILE* in,FILE* out,char* symbolCodes[]);
/**************************************************************
* Parameters:                                                 *
* unsigned long freqCounter[] - array that has list of symbols*
***************************************************************
* This functions interates over the freqCounter array and     *
* and counts how many spots have values                       *
***************************************************************
* returns the total amount of unique symbols in file          *
***************************************************************/
unsigned char getTotalSymbols(unsigned long freqCounter[]);
/**************************************************************
* Parameters:                                                 *
* char* code - code string to convert to binary representation*
***************************************************************
* This functions returns the binary representation of code    *
***************************************************************
* returns the binary representation of code                   *
***************************************************************/
unsigned long convertCode(char* code);
/**************************************************************
* Parameters:                                                 *
* char* code - code string to get length of                   *
***************************************************************
* This functions returns the length of code string            *
***************************************************************
* returns the length of code string                           *
***************************************************************/
unsigned char getCodeLength(char* code);

#endif
