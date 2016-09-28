int complexSolution()
{
  /* I want to put this findopen cell step into a function
  but think i need to learn structs to return multiple values
  which I havent learned yet so I can come update later*/
  int cellWithOneR = 0;
  int cellWithTwoR = 0;
  int cellWithThreeR = 0;
  int cellWithFourR = 0;
  int cellWithFiveR = 0;
  int cellWithSixR = 0;
  int cellWithSevenR = 0;
  int cellWithEightR = 0;
  int cellWithNineR = 0;
  int cellWithOneC = 0;
  int cellWithTwoC = 0;
  int cellWithThreeC = 0;
  int cellWithFourC = 0;
  int cellWithFiveC = 0;
  int cellWithSixC = 0;
  int cellWithSevenC = 0;
  int cellWithEightC = 0;
  int cellWithNineC = 0;

  int openCell = FALSE;
  int i = 0;
  int j = 0;
  for (i=0;i<9;i++)
  {
    for (j=0;j<9;j++)
    {
      if(theGrid[i][j] == 0)
      {
        openCell = TRUE;
        break;
      }

    }
    if(openCell)
    {
      break;
    }
  }

  /* if there are no open cells left it means the puzzle is finally solved*/
  if(openCell == FALSE)
  {
    return 1;
  }


  int n = 1;
  int nConversion = 0;
  for(n=1;n<=9;n++)
  {
    /*might want to extract this switch statement into a function for readability*/
    switch (n)
    {
      case 1:
      nConversion = ONE;
      break;
      case 2:
      nConversion = TWO;
      break;
      case 3:
      nConversion = THREE;
      break;
      case 4:
      nConversion = FOUR;
      break;
      case 5:
      nConversion = FIVE;
      break;
      case 6:
      nConversion = SIX;
      break;
      case 7:
      nConversion = SEVEN;
      break;
      case 8:
      nConversion = EIGHT;
      break;
      case 9:
      nConversion = NINE;
      break;
    }
    if(constraintGrid[i][j] & nConversion)
    {
      theGrid[i][j] = n;
      updateConstraints(i,j,n, FALSE);
      if(simpleSolution())
      {
        return 1;
      }
    }


      /*if this is not successful undo move reset constraintgrid and delete proven false constraints*/
    theGrid[i][j] = 0;
    undoMove(i,j,n);
    /*createConstraintGrid();*/
    deleteFalseConstraints(i, j, n);

  }

  return 0;
}
