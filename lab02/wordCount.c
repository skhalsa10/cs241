#include <stdio.h>
#define TRUE 1
#define FALSE 0

main()
{
  int c, line;
  long nc, nl;
  nc = nl = 0;
  line = FALSE;
  printf("%ld",(nl+1));
  while((c = getchar()) != EOF)
    {
      if(c == '\n')
        {
	  line = TRUE;
	  ++nl;
     	  //printf("\n%ld.", nl+1);
	}
      if(line == TRUE)
	{
	  //getchar("%ld.", (nl+1))
	  printf("\n%ld.", (nl+1));
	  line = FALSE;	  
	}
      putchar(c);
      ++nc;
    }
  printf("\nthere are %ld number of characters\n and %ld number of lines.", nc, nl);
      //putchar(c);
      

}
