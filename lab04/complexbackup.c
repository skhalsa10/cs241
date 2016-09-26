int complexSolution()
{
  /*printf("complexSolution has been called");*/
  if(!checkIfGridLegal())
  {
    printf("gridnotlegal THIS SHOULD NEVER PRINT!!\n");
    return 0;
  }
  int foundBlank = FALSE;
  int i = 0;
  int j = 0;
  for (i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      if (theGrid[i][j] == 0)
      {
        foundBlank = TRUE;
        break;
      }
    }
    if(foundBlank) break;
  }
  if((theGrid[i][j]==0)&&(constraintGrid[i][j] == 0))
  {
    printf("thegrid and constraingrid are ZERO returning unsuccessful");
    return 0;
  }
  printf("i: %d | j: %d\n", i, j);
  printf("constraintGrid[i][j]&ONE: %d\n", constraintGrid[i][j]&ONE);
  if(constraintGrid[i][j]&ONE)
  {
    printf("entering ONE\n");
    theGrid[i][j] = 1;
    /*printf("before restraints update i = 0 j = 1 %d\n", constraintGrid[i][j+1] );*/
    updateConstraints(i,j,1, FALSE);
    /*printf("after uypdating constraints i = 0 j = 1 %d\n",constraintGrid[i][j+1] );*/
    if(!complexSolution())
    {
      /*printf("complexSolution failed entering undoMove\n");*/
      undoMove(i,j,1);
      /*printf("After undoMove i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
      constraintGrid[i][j] ^= ONE;
    }
    /*else
    {
      printf("about to return 1?\n");
      return 1;
    }*/
  }
  printf("constraintGrid[i][j]&2: %d\n", constraintGrid[i][j]&TWO);
  if (constraintGrid[i][j]&TWO)
  {
    printf("entering TWO\n");
    theGrid[i][j] = 2;
    updateConstraints(i,j,2, FALSE);
        /*printf("After updateConstraints i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
    if(!complexSolution())
    {
      undoMove(i,j,2);
      /*printf("After undoMove i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
      constraintGrid[i][j] ^= TWO;
    }
    /*else
    {
      return 1;
    }*/
  }
  printf("constraintGrid[i][j]&THREE: %d\n", constraintGrid[i][j]&THREE);
  if (constraintGrid[i][j]&THREE)
  {
    printf("entering THREE\n");
    theGrid[i][j] = 3;
    updateConstraints(i,j,3, FALSE);
        /*printf("After updateConstraints i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
    if(!complexSolution())
    {
      undoMove(i,j,3);
      /*printf("After undoMove i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
      constraintGrid[i][j] ^= THREE;
    }
    /*else
    {
      return 1;
    }*/
  }
  printf("constraintGrid[i][j]&FOUR: %d\n", constraintGrid[i][j]&FOUR);
  if (constraintGrid[i][j]&FOUR)
  {
    printf("entering FOUR\n");
    theGrid[i][j] = 4;
    updateConstraints(i,j,4, FALSE);
        /*printf("After updateConstraints i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
    if(!complexSolution())
    {
      undoMove(i,j,4);
      /*printf("After undoMove i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
      constraintGrid[i][j] ^= FOUR;
    }
    /*else
    {
      return 1;
    }*/
  }
  printf("constraintGrid[i][j]&FIVE: %d\n", constraintGrid[i][j]&FIVE);
  if (constraintGrid[i][j]&FIVE)
  {
    printf("entering FIVE\n");
    theGrid[i][j] = 5;
    updateConstraints(i,j,5, FALSE);
      /*  printf("After updateConstraints i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
    if(!complexSolution())
    {
      undoMove(i,j,5);
      /*printf("After undoMove i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
      constraintGrid[i][j] ^= FIVE;
    }
    /*else
    {
      return 1;
    }*/
  }
  printf("constraintGrid[i][j]&SIX: %d\n", constraintGrid[i][j]&SIX);
  if (constraintGrid[i][j]&SIX)
  {
    printf("entering SIX\n");
    theGrid[i][j] = 6;
    updateConstraints(i,j,6, FALSE);
      /*  printf("After updateConstraints i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
    if(!complexSolution())
    {
      undoMove(i,j,6);
      /*printf("After undoMove i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
      constraintGrid[i][j] ^= SIX;
    }
    /*else
    {
      return 1;
    }*/
  }
  printf("constraintGrid[i][j]&SEVEN: %d\n", constraintGrid[i][j]&SEVEN);
  if (constraintGrid[i][j]&SEVEN)
  {
    printf("entering SEVEN\n");
    theGrid[i][j] = 7;
    updateConstraints(i,j,7, FALSE);
        /*printf("After updateConstraints i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
    if(!complexSolution())
    {
      undoMove(i,j,7);
      /*printf("After undoMove i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
      constraintGrid[i][j] ^= SEVEN;
    }
    /*else
    {
      return 1;
    }*/
  }
  printf("constraintGrid[i][j]&EIGHT: %d\n", constraintGrid[i][j]&EIGHT);
  if (constraintGrid[i][j]&EIGHT)
  {
    printf("entering EIGHT\n");
    theGrid[i][j] = 8;
    updateConstraints(i,j,8, FALSE);
        /*printf("After updateConstraints i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
    if(!complexSolution())
    {
      undoMove(i,j,8);
      /*printf("After undoMove i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
      constraintGrid[i][j] ^= EIGHT;
    }
    /*else
    {
      return 1;
    }*/
  }
  printf("constraintGrid[i][j]&NINE: %d\n", constraintGrid[i][j]&NINE);
  if (constraintGrid[i][j]&NINE)
  {
    printf("entering NINE\n");
    theGrid[i][j] = 9;
    updateConstraints(i,j,9, FALSE);
    /*printf("After updateConstraints i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
    if(!complexSolution())
    {
      undoMove(i,j,9);
    /*  printf("After undoMove i = 0 and j = 1: %d\n", constraintGrid[0][1] );*/
      constraintGrid[i][j] ^= NINE;
    }
    /*else
    {
      return 1;
    }*/
  }
  if (constraintGrid[i][j] == 0)
  {
    printf("about to return false from complex\n");
    return 0;
  }

  return 1;
}*/
