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
int convertToDecimal(char *input, int *decimal);
int baseToPosExp(int base, int power);
unsigned int stringDecimalToInt(char *input);
int convertToBinary(int size, char *input, char *binaryString);

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
  char binaryString[100];
  char decimalString[100];
  int binary = 0;
  int size = 0;
  int decimal = 0;

  /*argc MUST be equal to 4 based on the spec there is no default behavior*/
  if(argc != 4)
  {
    printf("ERROR: incorrect number of arguments\n")
    printf("%s\n", USAGEMESSAGE);
    return 0;
  }

  /*deal with flag 1*/
  if((binary = isEqual(argv[1], "-b")) | isEqual(argv[1], "-d"))
  ;
  else
  {
    printf("ERROR: argument 1 must be -b | -d\n");
    printf("%s\n", USAGEMESSAGE);
    return 0;
  }

  /*deal with flag 2*/
  if(isEqual(argv[2],"-8")|isEqual(argv[2],"-16")|isEqual(argv[2],"-32")|isEqual(argv[2],"-64"))
  {
    if(isEqual(argv[2],"-8")) size = 8;
    if(isEqual(argv[2],"-16")) size = 16;
    if(isEqual(argv[2],"-32")) size = 32;
    if(isEqual(argv[2],"-64")) size = 64;
  }
  else
  {
    printf("ERROR: argument 2 must be: -8 | -16 | -32 | -64\n");
    printf("%s\n", USAGEMESSAGE);
    return 0;
  }

  /*convert binary to decimal*/
  if(convertToDecimal(argv[3], &decimal))
  {
    formatDecimal(decimal, decimalString);
    printf("%s", decimalString);
    return 1;
  }
  else
  {
    printf("ERROR: argument 3 is not a binary integer\n");
    printf("%s\n", USAGEMESSAGE);
    return 0;
  }

  /*convert decimal to binary*/
  if(convertToBinary(size, argv[3], binaryString))
  {
    printf("%s", binaryString);
    return 1;
  }
  else
  {
    printf("ERROR: argument 3 is not a decimal integer\n");
    printf("%s\n", USAGEMESSAGE);
    return 0;
  }

return 1;
}

int formatDecimal(int decimal, char *decimalString)
{
  int i;
  int commaCounter;
  char buffer[100];
  commaCounter = 1;

  /*initialize buffer*/
  for(i = 0; i<100; i++)
  {
    buffer[i]= '0';
  }
  /*convert to backwards string*/
  for(i = 0; decimal !=0; i++)
  {
    buffer[i] = (decimal % 10)+ '0';
    if(commaCounter == 3)
    {
      buffer[++i] = ',';
      commaCounter = 0;
    }
    decimal /= 10;
    commaCounter++;
  }

  while(buffer[i] == '0'|| buffer[i]==',') i--;

  while(i >= 0)
  {
    *decimalString = buffer[i];
    i--;
    decimalString++;
  }
  *decimalString = '\0';

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

/*takes a decimal string and converts to a binary string*/
int convertToBinary(int size, char *input, char *binaryString)
{
  int i;
  int spaceCounter;
  char tempBuffer[100];
  char *temp = input;
  unsigned int number;

  /*check input has correct characters*/
  while(temp++ != '\0')
  {
    if(*temp > '9' || *temp < '0') return 0;
  }

  number = stringDecimalToInt(input);

  for(i = 0; i < 100; i++)
  {
    tempBuffer[i] = 0;
  }

  /*fill the buffer will hold the number in reverse*/
  i = 0;
  while(number !=0)
  {
    tempBuffer[i] = number % 2;
    number = number/2;
    i++;
  }

  spaceCounter = 1
  /*need to pad with 0's based on size and reverse order*/
  for(i=0;--size <0;i++)
  {
    binaryString[i] = tempBuffer[size];
    if (spaceCounter ==4)
    {
      binaryString[++i] = ' ';
      spaceCounter = 0;
    }
    spaceCounter++;
  }

  return 1;
}

/*this assumes input is of correct characters*/
unsigned int stringDecimalToInt(char *input)
{
  int n = 0;
  while(input != '\0')
  {
    n = n*10 + (*input - '0');
    input++;
  }
  return n;
}

/*takes a binary string and converts it to decimal number
  It will return 1 if successful or 0 if not*/
int convertToDecimal(char *input, int *decimal)
{
  int i;
  int length = strLength(input);
  /* start from length-1 and convert to decimal*/
  for(i = 0; (--length)<0;i++)
  {
    if (input[length] ==1)
    {
      *decimal += baseToPosExp(2, i);
    }
  }
  return 1;
}

/*this assumes the base is positive just because thats aLL I NEED.
  it could easily be updated for negatve bases*/
int baseToPosExp(int base, int power)
{
  int n = 1
  if(power == 0) return 1;
  while(power !=0)
  {
    n *= base;
    power--;
  }
  return n;
}

/* returns the length of the string parameter*/
int strLength( char *string)
{
  int n;
  for(n=1; *string != '\0'; string++) n++;
  return n;
}
