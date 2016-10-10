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
  int i = 0;
  for(i=0;i<argc;i++)
  {
    printf("%s\n", argv[i]);
  }

  printf("\n%s\n", USAGEMESSAGE);

}
