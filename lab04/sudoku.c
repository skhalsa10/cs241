#include <stdio.h>

/* 2d array ill call theGrid */
int theGrid[9][9]
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
   while((charStream != EOF)
   {
     int i = 0;
     int j = 0;
     for(i = 0; i < 9; i++)
     {
       for (j = 0; j < 9; j++)
       {
         charStream = getchar();
         putchar(charStream);
         theGrid[i][j] = charStream;
       }
       printf("\n" );
     }
   }
}
