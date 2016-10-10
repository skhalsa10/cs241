/***********************************************
*                                              *
*               By: Siri Khalsa                *
*                  10/07/16                    *
*                 CS-241 001                   *
*      Binary.c | binary-decimal converter     *
*                                              *
***********************************************/

#include <stdio.h>

/*declare external fns*/
int isEqual( char *s1, char *s2);
int strLength( char *string);

/*declare external variables*/
const char *USAGEMESSAGE =
  "usage:\n"
  "./binary OPTION SIZE NUMBER\n"
  "  OPTION:\n"
  "    -b    NUMBER is binary and output will be in decimal.\n"
  "    -d    NUMBER is decimal and output will be in binary.\n"
  "\n"
  "  SIZE:\n"
  "    -8    input is an unsigned 8-bit integer.\n"
  "    -16   input is an unsigned 16-bit integer.\n"
  "    -32   input is an unsigned 32-bit integer.\n"
  "    -64   input is an unsigned 64-bit integer.\n"
  "\n"
  "  NUMBER:\n"
  "    number to be converted.\n"
  "\n";

int main(int argc, char **argv)
{
  /*if this is one then binary switch was used else decimal switch was used*/
  int binary = 0;

  /*argc MUST be equal to 4 based on the spec there is no default behavior*/
  if(argc != 4)
  {
    printf("\n%s\n", USAGEMESSAGE);
    return 0;
  }

  /*deal with flag 1*/
  if((binary = isEqual(argv[1], "-b")) | isEqual(argv[1], "-d"))
  ;
  else
  {
    printf("\n%s\n", USAGEMESSAGE);
    return 0;
  }

return binary;
}

/*this function compares to strings to see if they are the same*/
int isEqual( char *s1, char *s2)
{
  if(strLength(s1) != strLength(s2)) return 0;
  while(*s1 != '\0')
  {
    if(*s1 != *s2) return 0;
    s1++;
    s2++;
  }
  return 1;
}

/* returns the length of the string parameter*/
int strLength( char *string)
{
  int n;
  for(n=0; *string != '\0'; string++) n++;
  return n;
}
