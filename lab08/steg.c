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
*                                              *
***********************************************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  char* inFileName = argv[1];
  char* outFileName = argv[2];

  unsigned char header[54];
  /* array of 4 bytes to hide 1 char*/
  unsigned char bytes[4];

  FILE* in = fopen(inFileName, "rb");
  FILE* out = fopen(outFileName, "wb");

  int c;

  /* read header into array */
  fread(header, 1, 54, in);

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