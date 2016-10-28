#include <stdio.h>
#include <stdlib.h>
#include "lcg.h"

/*declaretypedef and external variables and fns*/
typedef unsigned long u64;
typedef struct LinearCongruentialGenerator LCG;

LCG lcg;
u64 m;
u64 c;
int byte;
int encrypt;
int parseLine(u64* m, u64* c);
int encryptData();
int decryptData();

int main()
{
  int lineCount = 0;
  m = 0;
  c = 0;
  byte = getchar();
  /* set encrypt to negative 1 as default
  if 0 it means decrypt if 1 it means encrypt*/
  encrypt = -1;
  while(byte != EOF)
  {
    while(byte != '\n')
    {
      lineCount++;
      if(parseLine(&m,&c))
      {
        lcg = makeLCG(m,c);
        if(encrypt==1)
        {
          printf("%5d) ", lineCount );
          encryptData();
          printf("\n");
        }
        else if(encrypt ==0)
        {
          printf("%5d) ", lineCount );
          decryptData();
          printf("\n");
        }
        else
        {
          printf("ERROR!");
        }
      }
      else
      {
        while(byte != '\n') byte = getchar();
        printf("%5d) Error\n", lineCount);
      }
    }
    byte = getchar();
  }
  return 0;
}

int encryptData()
{
  u64 x = getNextRandomValue(&lcg);
  char encryptedByte = 0;
  while(byte != '\n' && byte != EOF)
  {
    encryptedByte = byte^(x%128);
    if(encryptedByte <32)
    {
      putchar('*');
      putchar(encryptedByte + '@');
    }
    else if(encryptedByte == 127)
    {
      putchar('*');
      putchar('&');
    }
    else if(encryptedByte == '*')
    {
      putchar('*');
      putchar('*');
    }
    else
    {
        putchar(encryptedByte);
    }
    byte = getchar();
    x = getNextRandomValue(&lcg);
  }
  return 1;
}

int decryptData()
{
  u64 x = getNextRandomValue(&lcg);
  char decryptedByte = 0;
  while (byte != EOF && byte != '\n')
  {
    if(byte == '*')
    {
      byte = getchar();
      if(byte == '*')
      {
        decryptedByte = byte^(x%128);
      }
      else if(byte == '&')
      {
        decryptedByte = 127^(x%128);
      }
      else
      {
        decryptedByte = (byte-'@')^(x%128);
      }
    }
    else
    {
      decryptedByte = byte^(x%128);
    }
    putchar(decryptedByte);
    byte = getchar();
    x = getNextRandomValue(&lcg);
  }
  return 1;
}

int parseLine(u64* m, u64* c)
{
  /*declare needed variables*/
  int i;
  char buffer[25];
  char* numberEnd;
  int length = -1;

  /*if the first char is not e or d return 0 for error*/
  if(byte == 'e')
  {
    encrypt = 1;
  }
  else if(byte == 'd')
  {
    encrypt = 0;
  }
  else
  {
    return 0;
  }

  /*move to the first number and then read in number store in buffer*/
  byte = getchar();
  i = 0;
  while(byte != ',' && byte != '\n' && byte != EOF)
  {
    buffer[i] = byte;
    byte = getchar();
    i++;
  }

  /*we should be expecting a ',' if not one ERROR*/
  if(byte == '\n' || byte == EOF) return 0;
  buffer[i] = '\0';
  *m = strtoul(buffer, &numberEnd, 10);
  length = ((numberEnd - buffer) / sizeof(char));
  /* per spec this has to be between 1 and 20*/
  if(length > 20 || length < 1) return 0;

  /*set buffer to nulls to begin obtaining c*/
  for(i=0;i<25;i++)
  {
    buffer[i]='\0';
  }
  byte = getchar();
  i = 0;
  while(byte != ',' && byte != '\n' && byte != EOF)
  {
    buffer[i] = byte;
    byte = getchar();
    i++;
  }
  if(byte == '\n' || byte == EOF) return 0;
  *c = strtoul(buffer, &numberEnd, 10);
  length = ((numberEnd - buffer) / sizeof(char));
  /* per spec this has to be between 1 and 20*/
  if(length > 20 || length < 1) return 0;
  byte = getchar();

  return 1;
}
