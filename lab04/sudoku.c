#include <stdio.h>
#define FALSE 0
#define TRUE 1

/* 2d array ill call theGrid */
int theGrid[9][9];
/* declare variable for charStream*/
int charStream = 0;
/*declare and initialize error boolean variables*/
int errorLineTooLong = FALSE;
int errorLineTooShort = FALSE;
int errorNotNumeric = FALSE;

int main()
{

  /*the program continues until the EOF characters
  it will copy 81 numbers and blanks int a 2d array.
  if it comes accross a non number character then the
  error flag is turned on. if there are not 81 characters
  '\n' error flag turned on. if there are more then 81
  characters before '\n' error flag is turned on. */
  while((charStream = getchar()) != EOF)
  {
    convertLineToGrid();
    int i = 0;
    int j = 0;
    if(errorNotNumeric)
    {
      printf("errorNotNumeric\n");
    }
    else if (errorLineTooShort)
    {
      printf("errorLineTooShort\n");
    }
    else if (errorLineTooLong)
    {
      printf("errorLineTooLong\n");
    }
    else
    {
      printf("\n+---------------------------+\n");
      for(i=0; i<9;i++)
      {
        for(j=0;j<9;j++)
        {
          printf("|%d|", theGrid[i][j]);
        }
        printf("\n");
      }
    }
  }
}

int convertLineToGrid()
{
  /*reinitialize error flags to false to start  off function*/
  errorLineTooShort = FALSE;
  errorNotNumeric = FALSE;
  errorLineTooLong = FALSE;

  /* loop over line and copt to theGrid*/
  int i = 0;
  int j = 0;
  for(i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      if(charStream == '.')
      {
        theGrid[i][j] = 0;
      }
      else if ((charStream >= '0' ) && (charStream <= '9'))
      {
        theGrid[i][j] = (charStream - '0');
      }
      /*test for line to short error */
      else if (charStream == '\n')
      {
        errorLineTooShort = TRUE;
        break;
      }
      /*if it makes it this far than we have nonnumeric char*/
      else
      {
        errorNotNumeric = TRUE;
        break;
      }
      charStream = getchar();
    }
    /* if we broke out of the first loop due
     to error just break the second one */
    if (errorNotNumeric||errorLineTooShort) break;
  }
  /* if we get 81 characters the next char should be'\n'
  but if our line is too short this will keep the stream in order*/
  if(!errorLineTooShort)
  {
    charStream = getchar();
  }
  /* successfull return!!! */
  if(charStream == '\n') return 1;
  /* I MEAN ALMOST FRIGGIN successfull!! our line seems to
  be more then 81 characters UGHHHH! */
  else
  {
    errorLineTooLong = TRUE;
    /* we need to return this function with a '\n'...
    ....
    ....   while loop: do your thing */
    while ((charStream = getchar()) != '\n' ||charStream != EOF)
    return 0;
  }
}
