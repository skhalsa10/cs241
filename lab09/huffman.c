#include "huffman.h"

/*encodes file*/
void encodeFile(FILE* in, FILE* out)
{
  unsigned int freqCounter[500];
  int i;
  /*initialize array to 0*/
  for(i=0;i<500;i++)
  {
    freqCounter[i] = 0;
  }
  /*count frequency of symbols in file pointed to by in*/
  generateFreq(in, freqCounter);
  printFreq(freqCounter)
}
void generateFreq(File* in, unsigned int freqCounter[])
{
  int c;
  while((c=getc(in)) != EOF)
  {
    freqCounter[c]++;
  }
}
void printFreg(unsigned int freqCounter[])
{
  int i;
  printf("Symbol\tFreq\n");
  for(i=0;i<500;i++)
  {
    if(freqCounter[i] != 0)
    {
      if(i<33||i>126)
      {
        printf("=%d\t%d",i, freqCounter[i]);
      }
      else
      {
        printf("%c\t%d",i, freqCounter[i]);
      }
    }
  }
}