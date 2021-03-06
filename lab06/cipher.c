/***********************************************
*                                              *
*               By: Siri Khalsa                *
*                  10/29/16                    *
*                 CS-241 001                   *
*  cipher.c | encrypt or decrypt data w/xor    *
*                                              *
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include "lcg.h"

/*declaretypedef and external variables and fns*/
typedef unsigned long u64;
typedef struct LinearCongruentialGenerator LCG;

LCG lcg;
int byte;
int encrypt;
int parseLine();
int encryptData();
int decryptData();

int main()
{
  int lineCount = 0;
  byte = getchar();
  /* set encrypt to -1 as default
  if 0 it means decrypt if 1 it means encrypt*/
  encrypt = -1;
  while(byte != EOF)
  {
    while(byte != '\n')
    {
      lineCount++;
      if(parseLine())
      {
        /*lcg = makeLCG(m,c);*/
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
        /*input has error move to \n to get ready for next input*/
        while(byte != '\n') byte = getchar();
        printf("%5d) Error\n", lineCount);
      }
    }
    byte = getchar();
  }
  return 0;
}

/***************************************************
*
* This function will iterate over stdin stream
* treat everything as a char and xor with a psuodo
* random number  generated from a Linear
* Congruential Generator to encrypt the data
* return 1 for success or 0 for error
*
****************************************************/
int encryptData()
{
  u64 x = getNextRandomValue(&lcg);
  char encryptedByte = 0;
  /*encrypt the  entire line per spec definition*/
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

/***************************************************
*
* This function will iterate over stdin stream
* treat everything as a char and xor with a psuodo
* random number  generated from a Linear
* Congruential Generator to decrypt the data
* if this produces not printable ASCII it will error
* return 1 for success or 0 for error
*
****************************************************/
int decryptData()
{
  u64 x = getNextRandomValue(&lcg);
  char decryptedByte = 0;
  /*decrypt the entire line*/
  while (byte != EOF && byte != '\n')
  {
    /*treat escape characters according to spec*/
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
      /*if not escaped then just decrypt*/
      decryptedByte = byte^(x%128);
    }
    /* make sure decrypted result is a printable ascii character- treat accordingly*/
    if(decryptedByte < 32 || decryptedByte >126)
    {
      while(byte != '\n' && byte != EOF) byte = getchar();
      printf("Error");
      return 0;
    }
    putchar(decryptedByte);
    byte = getchar();
    x = getNextRandomValue(&lcg);
  }
  return 1;
}

/***************************************************
*
* This function will iterate over stdin stream
* Per the spec of this program we are expecting the
* following:
* |Action|   lcg m  |    ,   |  lcg c  |    ,   |
* |1 char| 1-20 char| 1 char |1-20 char| 1 char |
* If any of these inputs are wrong this will return 0
* other wise makeLCG(m,c) will be called and 1 will
* be returned
*
****************************************************/
int parseLine()
{

  /*declare needed variables*/
  int i;
  u64 m;
  u64 c;
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
  m = strtoul(buffer, &numberEnd, 10);
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
  c = strtoul(buffer, &numberEnd, 10);
  length = ((numberEnd - buffer) / sizeof(char));
  /* per spec this has to be between 1 and 20*/
  if(length > 20 || length < 1) return 0;

  /*if it make it this far than we can make the lcg*/
  lcg = makeLCG(m,c);
  /*if lcg is bogus return 0*/
  if(lcg.a==0 && lcg.x ==0 && lcg.c ==0 && lcg.m ==0) return 0;

  byte = getchar();

  return 1;
}
