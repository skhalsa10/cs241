/*********************************************
*
* Siri Khalsa
* 09/03/2016
* CS 241 001
*
* This program will echo what is fed into it.
* While it echos it it counds words and lines
* and characters
*
**********************************************/

#include <stdio.h>

/* defining values for boolean tests */
#define TRUE 1
#define FALSE 0

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

/**********************************************
*
* This is the main function it initializez the
* global variables runs a while loop that loops
* until the EOF character is received It counts
* words lines and characters while looping upon
* receiving EOF it then prints out totals and
* lines with most chars and words.
***********************************************/
int main()
{
  /* initialize everything to default values */
  numOfWords =  1;
  charStream = lineLargestChar = lineLargestWord = totalWords = totalLines = 0;
  largestCharNum = largestWordNum  = totalChars = numOfChars = 0;
  isNewLine = inWord= TRUE;

  while((charStream = getchar()) != EOF)
  {

    /*totalChars++;*/
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
      inWord = TRUE;
      numOfWords++;
      /*totalWords++;*/
    }
    if(charStream != '\n')
    {
      numOfChars++;
    }
    putchar(charStream);
  }
  printVerboseEnding();
  return 0;
}

/* This function print #. increments line
*number and sets isNewLine flag to false */
void performNewLineTasks()
{
  totalLines++;
  printf("%d.", totalLines);

  isNewLine = FALSE;
}

/*************************************************
* performLineEndTasks()
* Parameters: none
* return value is void
*
* This function performs tasks that happen
* when the end of the line is reached.
* Print the current line info
* set isNewLine flag to TRUE
* call calculation functions
* add the current line counters to total counters
* and reset line counters
**************************************************/
void performLineEndTasks()
{
  printf("[%d;%d]", numOfWords, numOfChars);
  calcLargestChars(numOfChars);
  calcLargestWords(numOfWords);
  totalWords = totalWords + numOfWords;
  totalChars = totalChars + numOfChars;
  numOfWords = numOfChars = 0;
  isNewLine = TRUE;
}

/*************************************************
* calcLargestChars()
* Parameters:
* inputChars: a positive int that is the number
* of current chars in line
* return value is void
*
* This Function takes in the current line chars
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
* calcLargestWords()
* Parameters:
* inputWords: a positive int that is the number
* of current words in line
* return value is void
*
*This Function takes in the current line words
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
* printVerboseEnding()
* Parameters: none
* return value is void

* This function prints all the verbose
* information collected through out the program
* run.
* Total lines, total chars, total words
* the line with the most amount of chars
* and finally the line with the most words
*************************************************/
void printVerboseEnding()
{
  printf("%d lines, %d words, %d characters\n", totalLines, totalWords, totalChars);
  printf("With %d, line %d has the most characters\n", largestCharNum, lineLargestChar);
  printf("With %d, line %d has the most words\n", largestWordNum, lineLargestWord);
}
