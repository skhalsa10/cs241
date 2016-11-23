/***********************************************
*                                              *
*               By: Siri Khalsa                *
*                  11/04/16                    *
*                 CS-241 001                   *
*		            lab08                      *
*                 | steg.c |                   *
*     takes a picture and hides a message      *
*      from standard in into the picture       *
*                                              *
*   Borrowed a lot of code froom brooks file   *
* No need to reinvent the same methods but need*
*           to credit her code her.            *
*                                              *
***********************************************/
#include <stdio.h>
#include <stdlib.h>

int getIntFromArray(unsigned char bytes[]);
void copyIntToAddress(int n, unsigned char bytes[]);

int main(int argc, char** argv)
{
  char* inFileName = argv[1];
  char* outFileName = argv[2];

  unsigned char header[54];
  /* array of 4 bytes to hide 1 char*/
  unsigned char bytes[4];

  FILE* in = fopen(inFileName, "rb");
  FILE* out = fopen(outFileName, "wb");

  int fileSize;
  int pixelWidth;
  int pixelHeight;
  int pixelDataSize;
  int rowSize;
  int rowPadding;
  int c;

  /* read header into array */
  fread(header, 1, 54, in);

  /*I can assume all header info is correct*/

  fileSize = getIntFromArray(&header[2]);
  pixelWidth = getIntFromArray(&header[18]);
  pixelHeight = getIntFromArray(&header[22]);
  pixelDataSize = getIntFromArray(&header[34]);

  /* compute row padding */
  rowSize = pixelWidth*3;
  rowPadding = (4 - (rowSize % 4)) % 4;
  rowSize += rowPadding;

  printf("pixelWidth  = %d pixels\n", pixelWidth);
  printf("pixelHeight = %d pixels\n", pixelHeight);
  printf("rowPadding  = %d bytes\n", rowPadding);
  printf("rowSize     = %d bytes\n", rowSize);
  printf("pixelDataSize = %d bytes\n", pixelDataSize);
  printf("fileSize = %d bytes\n", fileSize);

  /* write header to output file */
  fwrite(header, 1, sizeof(header), out);

  /* this assumes that the message received from
  stdin is not longer than the picture can hadle*/
  while((c=getchar())!=EOF)
  {
    fread(bytes, 1, 4, in);
    bytes[3]= (bytes[4]&(~3))|(c&3);
    c >>= 2;
    bytes[2]= (bytes[4]&(~3))|(c&3);
    c >>= 2;
    bytes[1]= (bytes[4]&(~3))|(c&3);
    c >>= 2;
    bytes[0]= (bytes[4]&(~3))|(c&3);
    fwrite(bytes, 1, 4,out);
  }

  /*add a null byte*/
  fread(bytes, 1, 4, in);
  bytes[0]= bytes[0]&(~3);
  bytes[1]= bytes[0]&(~3);
  bytes[2]= bytes[0]&(~3);
  bytes[3]= bytes[0]&(~3);
  fwrite(bytes, 1, 4,out);

  /*now copy the rest of the file*/
  while((c=getc(in))!= EOF)
  {
      putc(c,out);
  }

  fclose(in);
  fclose(out);
  return 1;
}

/****************************************************************************/
/* This function copies 4 bytes from an int to an unsigned char array where */
/*   the least significant byte of the int is placed in the first element   */
/*   of the array.                                                          */
/****************************************************************************/
void copyIntToAddress(int n, unsigned char bytes[])
{
  bytes[0] = n & 0xFF;
  bytes[1] = (n >>  8) & 0xFF;
  bytes[2] = (n >> 16) & 0xFF;
  bytes[3] = (n >> 24) & 0xFF;
}

/**********************************************************************/
/* Take 4 bytes from an unsigned char array and assemble them into an */
/* int where the first element of the array is the least significant  */
/* byte of the int.                                                   */
/**********************************************************************/
int getIntFromArray(unsigned char bytes[])
{
  int n =
    bytes[0] |
    bytes[1] << 8 |
    bytes[2] << 16 |
    bytes[3] << 24;
  return n;
}