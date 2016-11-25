#ifndef HUFFMAN_H
#define HUFFMAN_H

/* Including stdio so we'll know about FILE type */
#include <stdio.h>
#include "queueAndTree.h"

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

struct QueueNode* generateQueue(unsigned long freqCounter[]);
void printQueue(struct QueueNode* head);

#endif
