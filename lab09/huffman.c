#include <stdio.h>
#include "huffman.h"

/*encodes file*/
void encodeFile(FILE* in, FILE* out)
{
  unsigned int freqCounter[260];
  int i;
  /*initialize array to 0*/
  for(i=0;i<260;i++)
  {
    freqCounter[i] = 0;
  }
  /*count frequency of symbols in file pointed to by in*/
  generateFreq(in, freqCounter);
  printFreq(freqCounter);
}
void generateFreq(FILE* in, unsigned int freqCounter[])
{
  int c;
  while((c=getc(in)) != EOF)
  {
    freqCounter[c]++;
  }
}

void printFreq(unsigned int freqCounter[])
{
  int i;
  unsigned long totalChars = 0;
  printf("Symbol\tFreq\n");
  for(i=0;i<260;i++)
  {
    if(freqCounter[i] != 0)
    {
      totalChars += freqCounter[i];
      if(i<33||i>126)
      {
        printf("=%d\t%d\n",i, freqCounter[i]);
      }
      else
      {
        printf("%c\t%d\n",i, freqCounter[i]);
      }
    }
  }
  printf("Total chars = %lu\n", totalChars);
}