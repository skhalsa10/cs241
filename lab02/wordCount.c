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
  int c, charStream, numOfChars, numOfLines, numOfWords, isNewLine, inWord;
  numOfChars = numOfLines = numOfWords = 0;
  isNewLine = inWord = TRUE;

  while((c = getchar()) != EOF)
  {
    numOfChars++;
    if(isNewLine == TRUE)
    {
      numOfLines++;
      isNewLine = FALSE;
      putchar(numOfLines);
      putchar('.');
    }
    if(c == ' ' || c == '\n' || c == '\t')
    {
      inWord = FALSE;
      if (c == '\n')
      {
        isNewLine = TRUE;
      }
    }
    else if(inWord == FALSE)
    {
      inWord = TRUE;
      numOfWords++;
    }
    putchar(c);
  }

  printf("%d of lines, %d of words, %d of characters\n", numOfLines, numOfWords, numOfChars );


}
