#include <stdio.h>

/* 2d array ill call theGrid */
int theGrid[9][9];
/* declare variable for charStream*/
int charStream = 0;

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
	 charStream = getchar();
       }
     }
     charStream = getchar();
     for(i=0; i<9;i++)
       {
	 printf("\n+---------------------------+\n");
	 for(j=0;j<9;j++)
	   {
	     printf("|%d|", theGrid[i][j]);
	   }
       }
   }
}

int convertLineToGrid()
{

}
