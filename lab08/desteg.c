/***********************************************
*                                              *
*               By: Siri Khalsa                *
*                  11/04/16                    *
*                 CS-241 001                   *
*		            lab08                      *
*                | desteg.c |                  *
*  takes an image and decodes secret message   *
*                                              *
***********************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char* inFileName = argv[1];
    int i;
    char code;
    unsigned char bytes[4];

    FILE* in = fopen(inFileName, "rb");

    /*pass the header*/
    for(i=0; i<54; i++)
    {
        getc(in);
    }

    while(code != NULL)
    {
        bytes[0]= 0;
        bytes[1]= 0;
        bytes[2]= 0;
        bytes[3]= 0;

        fread(&bytes, 1, 4, in);
        code = 0 | (bytes[0]&3);
        code = (code<<2)| (bytes[1]&3);
        code = (code<<2)| (bytes[2]&3);
        code = (code<<2)| (bytes[3]&3);

        if(code != NULL) putchar(code);
    }

    fclose(in);
    return 1;
}
