#include <stdio.h>

/* defining values for boolean tests */
#define TRUE 1
#define FALSE 0

/*********************************************
*
* Siri Khalsa
* 09/03/2016
* CS 241 001
*
* This program will echo what is fed into it.
* While it echos it it counds words and lines
*
**********************************************/

/*global variables used by all  functions and main*/

/* defines charStream used for processing getchar & putchar */
int charStream;

/*these variables hold values that keep track
of the line with the most words & chars*/
int lineLargestChar, largestCharNum, lineLargestWord, largestWordNum;

/*variables that hold the total lines, chars, and words*/
int totalLines, totalWords, totalChars;

/*variables that hold data for each line. gets reset per line */
int numOfWords, numOfChars;

/* variables used as boolean flags initialized to TRUE */
int isNewLine, inWord;

/* function declerations */
void calcLargestChars(int inputChars);
void calcLargestWords(int inputWords);
void performLineEndTasks();
void performNewLineTasks();
void printVerboseEnding();

int main()
{
  /* initialize everything to default values */
  totalWords = numOfWords = totalLines = 1;
  charStream = lineLargestChar = lineLargestWord = 0;
  largestCharNum = largestWordNum  = totalChars = numOfChars = 0;
  isNewLine = inWord= TRUE;

  while((charStream = getchar()) != EOF)
  {
    numOfChars++;
    totalChars++;
    if(isNewLine == TRUE)
    {
      performNewLineTasks();
    }
    if(charStream == ' ' || charStream == '\n' || charStream == '\t')
    {
      inWord = FALSE;
      if(charStream == '\n')
      {
        performLineEndTasks();
      }
    }
    else if (inWord == FALSE)
    {
      inWord == TRUE;
      numOfWords++;
      totalWords++;
    }
    putchar(charStream);
  }
  printVerboseEnding();
}

/* This function print #. increments line
*number and sets isNewLine flag to false */
void performNewLineTasks()
{
  printf("%d.", totalLines);
  totalLines++;
  isNewLine = FALSE;
}

/*************************************************
* This function performs tasks that happen
* when the end of the line is reached.
* Print the current line info
* set isNewLine flag to TRUE
* call calculation functions
* reset line counters
**************************************************/
void performLineEndTasks()
{
  printf("[%d,%d]", numOfWords, numOfChars);
  calcLargestChars(numOfChars);
  calcLargestWords(numOfWords);
  numOfWords = numOfChars = 1;
  isNewLine = TRUE;
}

/*************************************************
*This Function takes in the current line chars
* compares it to the variables that hold the
* largest info
* if larger replaces value else do nothing
**************************************************/
void calcLargestChars(int inputChars)
{
  if(inputChars > largestCharNum)
  {
    largestCharNum = inputChars;
    lineLargestChar = totalLines;
  }
}

/*************************************************
*This Function takes in the current line chars
* compares it to the variables that hold the
* largest info
* if larger replaces value else do nothing
**************************************************/
void calcLargestWords(int inputWords)
{
  if(inputWords > largestWordNum)
  {
    largestWordNum = inputWords;
    lineLargestWord = totalLines;
  }
}

/************************************************
* This function prints all the verbose
* information collected through out the program
* run.
* Total lines, total chars, total words
* the line with the most amount of chars
* and finally the line with the most words
5 lines, 50 words, 252 characters
With 56, line 2 has the most characters
With 11, line 1 has the most words
*************************************************/
void printVerboseEnding()
{
  printf("%d lines, %d words, %d characters\n", totalLines, totalWords, totalChars);
  printf("With %d, Line %d has the most characters\n", largestCharNum, lineLargestChar);
  printf("With %d, Line %d has the most words\n", largestWordNum, lineLargestWord);
}
