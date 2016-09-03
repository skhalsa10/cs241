#include <stdio.h>
#define TRUE 1 //will be used for my own boolean value
#define FALSE 0 // used as boolean

/*********************************************
*                                            *
* This program will echo what is fed into it.*
* While it echos it it counds words and lines*
*                                            *
**********************************************/

main()
{
  int c, charStream, numOfChars, numOfLines, numOfWordsTotal, isNewLine, inWord;
  int numOfWords;
  numOfChars = numOfLines = 0;
  numOfWordsTotal = numofWords = 1;
  isNewLine = inWord = TRUE;

  while((c = getchar()) != EOF)
  {
    numOfCharsTotal++;
    numOfChars++;
    if(isNewLine == TRUE)
    {
      numOfLines++;
      isNewLine = FALSE;
      printf("%d.", numOfLines);
    }
    if(c == ' ' || c == '\n' || c == '\t')
    {
      inWord = FALSE;
      if (c == '\n')
      {
        numOfChars = 1;
        numOfWords = 1;
        isNewLine = TRUE;
      }
    }
    else if(inWord == FALSE)
    {
      inWord = TRUE;
      numOfWords++;
      numOfWordsTotal++;
    }
    if(isNewLine == TRUE) printf("[%d, %d]", numOfWords, numOfChars);
    putchar(c);
  }

  printf("%d of lines, %d of words, %d of characters\n", numOfLines, numOfWordsTotal, numOfChars );


}
