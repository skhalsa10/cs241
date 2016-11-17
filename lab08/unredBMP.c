#include <stdio.h>
#include <stdlib.h>

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

/* Copy a bitmap file without red */
int main(int argc, char** argv)
{
  char* infilename = argv[1];
  char* outfilename = argv[2];

  unsigned char header[54];

  FILE* in = fopen(infilename, "rb");
  FILE* out = fopen(outfilename, "wb");

  int fileSize;
  int pixelWidth;
  int pixelHeight;
  int pixelDataSize;
  int rowSize;
  int rowPadding;

  int i, j;

  /* read header into array */
  fread(header, 1, 54, in);

  /* is this really a bitmap? */
  if(header[0] != 'B' || header[1] != 'M')
  {
    printf("Input file is not a bitmap\n");
  }

  /* Is the header size what we expect? */
  if(getIntFromArray(&header[10]) != 54)
  {
    printf("Unexpected header size\n");
  }

  /* How many bits per pixel? Expecting 24*/
  if(!(header[28] == 24 && header[29] == 0))
  {
    printf("Unexpected number of bits/pixel\n");
  }

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

  /* Read RGB data from original, copy without red */
  for(i = 0; i < pixelHeight; ++i)
  {
    for(j = 0; j < pixelWidth; ++j)
    {
      unsigned char bytes[3];
      
      /* color order is BGR */ 
      fread(&bytes, 1, 3, in);

      /* set red byte to zero */
      bytes[2] = 0;

      fwrite(&bytes, 1, 3, out);
    }

    /* handle end of row padding */
    fseek(in, rowPadding, SEEK_CUR);
    for(j = 0; j < rowPadding; ++j)
    {
      putc(0, out);
    }
  }
  
  fclose(in);
  fclose(out);
  return 0;
}
