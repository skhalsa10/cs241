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
int convertToDecimal(int size, char *input, unsigned long int *decimal);
unsigned long int baseToExp(int base, int power);
unsigned int stringDecimalToInt(char *input);
int convertToBinary(int size, char *input, char *binaryString);
int formatDecimal(int size, unsigned long int decimal, char *decimalString);

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
  unsigned long int decimal = 0;

  /*argc MUST be equal to 4 based on the spec there is no default behavior*/
  if(argc != 4)
  {
    printf("ERROR: incorrect number of arguments\n");
    printf("%s", USAGEMESSAGE);
    return 0;
  }

  /*deal with flag 1*/
  if((binary = isEqual(argv[1], "-b")) | isEqual(argv[1], "-d"))
  ;
  else
  {
    printf("ERROR: argument 1 must be -b | -d\n");
    printf("%s", USAGEMESSAGE);
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
    printf("%s", USAGEMESSAGE);
    return 0;
  }

  if(binary)
  {
    /*convert binary to decimal*/
    if(convertToDecimal(size, argv[3], &decimal))
    {
      formatDecimal(size, decimal, decimalString);
      printf("%s\n", decimalString);
      return 1;
    }
    else
    {
      printf("ERROR: argument 3 is not a binary integer\n");
      printf("%s", USAGEMESSAGE);
      return 0;
    }
  }
  else
  {
    /*convert decimal to binary*/
    if(convertToBinary(size, argv[3], binaryString))
    {
      printf("%s\n", binaryString);
      return 1;
    }
    else
    {
      printf("ERROR: argument 3 is not a decimal integer\n");
      printf("%s", USAGEMESSAGE);
      return 0;
    }
  }

  return 1;
}

/**********************************************
* paramters:
* int size: defines output format
* unsigned long int decimal: number to format
* char *decimalString : pointer to char array
* that holds the formatted string
***********************************************
* formatDecimal converts a decimal to a
* formatted string.
***********************************************
* returns: 1 if success and 0 if error
***********************************************/
int formatDecimal(int size, unsigned long int decimal, char *decimalString)
{
  int i;
  int commaCounter;
  char buffer[100];
  commaCounter = 1;

  /*initialize buffer*/
  for(i = 0; i<100; i++)
  {
    buffer[i]= ' ';
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

  /*deletes comma that is not used*/
  while(buffer[i] == ' ') i--;
  if(buffer[i] == ',') buffer[i] = ' ';
  /*sets padding*/
  switch (size) {
    case 8:
    i = 2;
    break;
    case 16:
    i = 5;
    break;
    case 32:
    i = 12;
    break;
    case 64:
    i =25;
    break;
  }
  /*pull string out of buffer in correct order*/
  while(i >= 0)
  {
    *decimalString = buffer[i];
    i--;
    decimalString++;
  }
  *decimalString = '\0';
  return 1;
}

/**********************************************
* paramters:
* char *s1: s
* char *s2: number to format
***********************************************
* formatDecimal converts a decimal to a
* formatted string.
***********************************************
* returns: 1 if success and 0 if error
***********************************************/
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

/**********************************************
* paramters:
* char *s1: s
* char *s2: number to format
***********************************************
* formatDecimal converts a decimal to a
* formatted string.
***********************************************
* returns: 1 if success and 0 if error
***********************************************/
int convertToBinary(int size, char *input, char *binaryString)
{
  int i;
  int spaceCounter;
  char tempBuffer[100];
  int length = strLength(input);
  unsigned int number;

  /*check input has correct characters*/
  for(i=0;i<length;i++)
  {
    if(*(input+i) > '9' || *(input+i) < '0') return 0;
  }
  number = stringDecimalToInt(input);
  for(i = 0; i < 100; i++)
  {
    tempBuffer[i] = '0';
  }
  /*fill the buffer will hold the number in reverse*/
  i = 0;
  while(number !=0)
  {
    tempBuffer[i] = (number % 2)+'0';
    number = number/2;
    i++;
  }

  spaceCounter = 1;
  /*need to pad with 0's based on size and reverse order*/
  for(i=0;--size >=0;i++)
  {
    binaryString[i] = tempBuffer[size];
    if (spaceCounter == 4)
    {
      binaryString[++i] = ' ';
      spaceCounter = 0;
    }
    spaceCounter++;
  }
  binaryString[--i] = '\0';
  return 1;
}

/**********************************************
* paramters:
* input[]: String that is converted to number
***********************************************
* this fn converts a string into its int counterpart
* does not do any error checking
***********************************************
* returns: the converted int
***********************************************/
unsigned int stringDecimalToInt(char *input)
{
  int n = 0;
  while(*input != '\0')
  {
    n = n*10 + (*input - '0');
    input++;
  }
  return n;
}

/**********************************************
* paramters:
* size: how many bits used
* *input: STring of of a binary representation
* unsigned long int *decimal: this will hold
* base 10 representation of input string
***********************************************
* convertToDecimal: converts input binary
* string into int base 10 representation
***********************************************
* returns: 1 if success and 0 if error
***********************************************/
int convertToDecimal(int size, char *input, unsigned long int *decimal)
{
  int i;
  int length = strLength(input);
  int iModerator = length/size;
  if (length == size) iModerator =0;
  /* start from length-1 and convert to decimal*/
  for(i = 0; (--length)>=(iModerator);i++)
  {
    if (input[length] =='1')
    {
      *decimal += baseToExp(2, i);
    }
  }
  return 1;
}

/**********************************************
* paramters:
* int base: base to be raised
* int power: the exponant the base will be raised to
***********************************************
* baseToExp: this fn will rase the base to the power
* it assumes the base is positive because that
* is all that is needed for this program I
* am sure there is a better standard library
* available for this, but decided to make
* my own for more practice
***********************************************
* returns: the number after all calculationsa are made.
***********************************************/
unsigned long int baseToExp(int base, int power)
{
  unsigned long int n = 1;
  if(power == 0) return 1;
  while(power !=0)
  {
    n *= base;
    power--;
  }
  return n;
}

/**********************************************
* paramters:
* char *string: the string that will be analyzed
***********************************************
* strLength: this fn returns the length of inputted string
***********************************************
* returns: length of string
***********************************************/
int strLength( char *string)
{
  int n;
  for(n=0; *string != '\0'; string++) n++;
  return n;
}
