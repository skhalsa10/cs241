#include <stdio.h>
#include <limits.h>

/************************************************
* Siri Khalsa
* 09/09/2016
* CS241 001
* LAB03
*
* This program implements the getbits
* program in K&N. It adds error checking for
* the following:
*
* 1. integer over flow
* 2. There is enough bit spots to shift
* 3. or the given inputs fit into a 32 bit int
*
* this program reads a camma deliminated file
* and feeds it into getbits() K&N
*
*************************************************/
/*declare boolean ENUM*/
enum boolean {FALSE, TRUE};

/*declare fuctions*/
unsigned int getBits(unsigned int x, int p, int n);
void calculateLine();
void getBitsAndPrint();

/*declare variables*/
unsigned int number = 0;
int position = 0;
int nBits = 0;
int notEndOfFile = TRUE;
int valueOutOfRange = FALSE;
int nBitsGreaterThanPosition = FALSE;
int positionOutOfRange = FALSE;
int nBitsOutOfRange = FALSE;
int otherError = FALSE;

int main()
{
  while(notEndOfFile)
  {
    calculateLine();
    getBitsAndPrint();
  }
  return 1;
}

/************************************************
* this functions takes one line at time and
* converts all sections to unsigned int variables
* number, position, nBits in that order
*************************************************/
void calculateLine()
{
  /*declare variables used in this functio first to avoid warnings*/
  int c;
  int overflowtest;
  /* reset variables to 0 and FALSE*/
  number = 0;
  position = 0;
  nBits = 0;
  valueOutOfRange = FALSE;
  nBitsGreaterThanPosition = FALSE;
  positionOutOfRange = FALSE;
  nBitsOutOfRange = FALSE;
  otherError = FALSE;

  /* getchar() until \n if EOF set flag to FALSE
  this assumes there will be 2 commas garunteed
  which there will be based on the input file.
  not built for generality but it is built for
  camma deliminated getbits inputs this also
  assumes that the char will be a numerical
  char. if not the loop breaks immediately
  and sets an errror flag and sends string to
  error stream */
  /*int c; for some reason i get an error if I dont declare this before
  all expressions?! some old standard ? */

  while( (c = getchar()) != ',' || c != EOF)
  {
    printf("this is the char in 1st loop %c\n", c);
    overflowtest = number;
    /*if( (c <= '0') || (c >= '9') )
    {
      otherError = TRUE;
      perror("unexpected character value");
      break;
    }*/
    number = 10 * number + (c - '0');
    /*check for overflow */
    if (number < overflowtest)
    {
      valueOutOfRange = TRUE;
      break;
    }
  }
  /* convert position to numerical value*/
  while( (c = getchar()) != ',' || c != EOF)
  {
    printf("this is the char in 2nd loop %c\n", c);
    /*if( (c <= '0') || (c >= '9') )
    {
      otherError = TRUE;
      perror("unexpected character value");
      break;
    }*/
    position = 10 * position + (c - '0');
  }
  if (position > 31) positionOutOfRange = TRUE;

  /*convert nbits to numerical value */
  while( (c = getchar()) != '\n' || c != EOF)
  {
    printf("this is the char in 3rd loop %c\n", c);
    /* if( (c <= '0') || (c >= '9') )
    {
      printf("this should not be types");
      otherError = TRUE;
      perror("this must be printing no matter what FUCK");
      break;
      }*/
    nBits = 10 * nBits + (c - '0');
  }
  if ((position + 1 - nBits)< 0) nBitsGreaterThanPosition = TRUE;
  if (nBits > 31) nBitsOutOfRange = TRUE;
  if(c == EOF) notEndOfFile = FALSE;
}

/************************************************
* This function tests to see if error flags
* have been turned on. if so prints necessary
* message and bypasses running getbits.
* if all flags are false it runs getbits
************************************************/
void getBitsAndPrint()
{
  if(valueOutOfRange)
  {
    printf("Error: value out of range\n");
  }
  else if(nBitsGreaterThanPosition)
  {
    printf("Error: too many bits requested from position\n");
  }
  else if(positionOutOfRange)
  {
    printf("Error: position out of range\n");
  }
  else if(nBitsOutOfRange)
  {
    printf("Error: number of bits out of range\n" );
  }
  else
  {
      printf("getbits(x=%u, p=%d, n=%d) = %u\n", number, position, nBits, getBits(number,position,nBits));
  }
}

/************************************************
* copied from K&N book: I have added int to make more verbose
*************************************************
* getbits: get n bits from position p
*************************************************/
unsigned int getBits(unsigned int x, int p, int n)
{
  return (x >> (p+1-n)) & ~(~0 << n);
}
