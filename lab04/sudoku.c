#include <stdio.h>
#define FALSE 0
#define TRUE 1
#define ONE 1
#define TWO 2
#define THREE 4
#define FOUR 8
#define FIVE 16
#define SIX 32
#define SEVEN 64
#define EIGHT 128
#define NINE 256
#define ISSIMPLESOLUTIONON 0


/* declare all functions here */
int convertLineToGrid();
int checkIfGridLegal();
int checkIfGridFull();
int checkIfGridSolved();
int createConstraintGrid();
void printResults();
int solvePuzzle();
int everyRowContainsEveryNumber();
int rowContainsNNumber(int row, int number);
int columnContainsEverNumber();
int columnContainsNNumber(int column, int number);
int boxContainsEveryNumber();
int boxContainsNNumber(int boxRow, int boxColumn, int number);
int checkRowDuplicateN(int row, int number);
int checkColumnDuplicateN(int column, int number);
int checkBoxDuplicateN(int boxRow, int boxColumn, int number);
int updateConstraints(int inputRow, int inputColumn, int inputNumber, int notComplexCall);
int updateRowConstraints(int row, int number);
int updateColumnConstraints(int column, int number);
int updateBoxConstraints(int boxRow, int boxColumn, int number);
int fillInSingleConstraints();
int complexSolution();
int undoRowConstraint(int row, int number);
int undoColumnConstraint(int column, int number);
int undoBoxConstraint(int boxRow, int boxColumn, int number);
int turnOffConstraint(int row, int column, int toTurnOff);
void printConstraintGrid();
int simpleSolution();
int deleteFalseConstraints(int row, int column, int number);
int howManySolutions(int row, int column);

/* 2d array i'll call theGrid */
int theGrid[9][9];
/* 2d array that will hold all constraints*/
unsigned int constraintGrid[9][9];
/* declare variable for charStream*/
int charStream = 0;
/* declare String used for printing results */
char inputLine[100];
/*declare and initialize error boolean variables*/
int errorLineTooLong = FALSE;
int errorLineTooShort = FALSE;
int errorNotNumeric = FALSE;
int puzzleSolved = FALSE;
int puzzleError = FALSE;
int noSolution = FALSE;

int main()
{

  /*the program continues until the EOF characters
  it will copy 81 numbers and blanks int a 2d array.
  if it comes accross a non number character then the
  error flag is turned on. if there are not 81 characters
  '\n' error flag turned on. if there are more then 81
  characters before '\n' error flag is turned on. */
  while((charStream = getchar()) != EOF)
  {
    noSolution = FALSE;
    puzzleError = FALSE;
    puzzleSolved = FALSE;
    /*this will always only happen once
    but I want to break out of the set
    of instructions when certain criteria is met
    like an error flag is turned on or a function
    returns 0 */
    do
    {
      if(!convertLineToGrid())
      {

        puzzleError = TRUE;
        break;
      }
      if(checkIfGridFull())
      {
        if(checkIfGridSolved())
        {
          puzzleSolved = TRUE;
        }
        break;
      }
      if(!checkIfGridLegal())
      {
        puzzleError = TRUE;
        break;
      }
      createConstraintGrid();
      if(solvePuzzle())
      {
        puzzleSolved = TRUE;
      }
      else
      {
        noSolution = TRUE;
      }
    }
    while(0);
    printResults();


  }
}

/****************************************************
*
* This function returns 1 if puzzle has a Solution
* and has been solved. It return 0 if there is no solution
*
* This is the simple backtracking solution:
* First it picks an open cell
* and loops over numbers 1 through 9  it tries a number
* checks if it the board is still legal(doesnt violate rules of game)
* if it is legal it calls itself.
* if not legal it undoes move and tries the next number
*
* REMARK: this takes about 3min 20 sec to finish single.in
*****************************************************/
int simpleSolution()
{
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

  /*loop over ever possible solution plug it in check if legal
  * if not legal try next move if it is legal call simple solution again.*/
  int n = 1;
  for(n=1;n<=9;n++)
  {
    theGrid[i][j] = n;
    if(checkIfGridLegal())
    {
      if(simpleSolution())
      {
        return 1;
      }
    }
    theGrid[i][j] = 0;

  }

  return 0;
}

/*
* This function returns 1 if puzzle is solved or 0 if no solution
*
* this function takes a strategic approach to solving. it uses the
* initial constrain grid first attepts to solve by filling in all
* squares that have only one option if it fills up the grid is now full
* the puzzle is solved return 1
*
* if the grid is not full then perform a more rigourous technique
* if the simple solution is switch on from define then perform this algorithm
* else th complexSolution is run which will have its return function returned.
*/
int solvePuzzle()
{
  while(fillInSingleConstraints());
  if(!checkIfGridFull())
  {
    printConstraintGrid();
    if(ISSIMPLESOLUTIONON)
    {
      printf("performing simple solution\n");
      return simpleSolution();
    }
    else
    {
      printf("running complexSolution\n");
      return complexSolution();
    }
  }
  return 1;
}


/************************************
* Parameters:
* inputRow is the row index of the "currentCell"
* inputColumn is the column index of the "currentCell"
* inputNumber is the number we are readding to the
* appropriate list of available constraints
***************************************
*  this function calls other smaller helper functions that
* perform undos for the row the column and the box
****************************************/
int undoMove(int inputRow,int inputColumn,int inputNumber)
{
  printf("undomove entered\n");
  theGrid[inputRow][inputColumn] = 0;
  /*createConstraintGrid();*/
  undoRowConstraint(inputRow, inputNumber);
  undoColumnConstraint(inputRow, inputNumber);
  undoBoxConstraint((inputRow/3), (inputColumn/3), inputNumber);
  return 1;
}

/**************************************************************
* Parameters:
* int row - the row that will be iterated over
* int number - the number to add back as a constraintGrid
***************************************************************
* Returns 1 if successful and 0 if there is an error
***************************************************************
*  this function just loops over every cell in row and adds
* Number Back in as a possible solution.
*
* Is this adding steps that do not need to be done?
**************************************************************/
int undoRowConstraint(int row, int number)
{
  int j = 0;
  for (j=0;j<9;j++)
  {
    if (theGrid[row][j] >0)
    {
      switch (number)
      {
        case 1:
        constraintGrid[row][j] |= ONE;
        break;
        case 2:
          constraintGrid[row][j] |= TWO;
        break;
        case 3:
          constraintGrid[row][j] |= THREE;
        break;
        case 4:
          constraintGrid[row][j] |= FOUR;
        break;
        case 5:
          constraintGrid[row][j] |= FIVE;
        break;
        case 6:
          constraintGrid[row][j] |= SIX;
        break;
        case 7:
          constraintGrid[row][j] |= SEVEN;
        break;
        case 8:
          constraintGrid[row][j] |= EIGHT;
        break;
        case 9:
          constraintGrid[row][j] |= NINE;
        break;
      }
    }
  }
  return 1;
}

int undoColumnConstraint(int column, int number)
{
  int i = 0;
  for (i=0;i<9;i++)
  {
    if (theGrid[i][column] >0)
    {
      switch (number)
      {
        case 1:
        constraintGrid[i][column] |= ONE;
        break;
        case 2:
          constraintGrid[i][column] |= TWO;
        break;
        case 3:
          constraintGrid[i][column] |= THREE;
        break;
        case 4:
          constraintGrid[i][column] |= FOUR;
        break;
        case 5:
          constraintGrid[i][column] |= FIVE;
        break;
        case 6:
          constraintGrid[i][column] |= SIX;
        break;
        case 7:
          constraintGrid[i][column] |= SEVEN;
        break;
        case 8:
          constraintGrid[i][column] |= EIGHT;
        break;
        case 9:
          constraintGrid[i][column] |= NINE;
        break;
      }
    }
  }
  return 1;
}

int undoBoxConstraint(int boxRow, int boxColumn, int number)
{
  int i = 0;
  int j = 0;
  for(i = 0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if (theGrid[3*boxRow+i][3*boxColumn+j] >0)
      {
        switch (number)
        {
          case 1:
          constraintGrid[3*boxRow+i][3*boxColumn+j] |= ONE;
          break;
          case 2:
            constraintGrid[3*boxRow+i][3*boxColumn+j] |= TWO;
          break;
          case 3:
            constraintGrid[3*boxRow+i][3*boxColumn+j] |= THREE;
          break;
          case 4:
            constraintGrid[3*boxRow+i][3*boxColumn+j] |= FOUR;
          break;
          case 5:
            constraintGrid[3*boxRow+i][3*boxColumn+j] |= FIVE;
          break;
          case 6:
            constraintGrid[3*boxRow+i][3*boxColumn+j] |= SIX;
          break;
          case 7:
            constraintGrid[3*boxRow+i][3*boxColumn+j] |= SEVEN;
          break;
          case 8:
            constraintGrid[3*boxRow+i][3*boxColumn+j] |= EIGHT;
          break;
          case 9:
            constraintGrid[3*boxRow+i][3*boxColumn+j] |= NINE;
          break;
        }
      }
    }
  }
  return 1;
}

int turnOffConstraint(int row, int column, int toTurnOff)
{
  if(constraintGrid[row][column]&toTurnOff)
  {
    constraintGrid[row][column] ^= toTurnOff;
  }
  return 1;
}

int howManySolutions(int row,int column)
{
  int counter = 0;

  if(constraintGrid[row][column]&ONE) counter++;
  if(constraintGrid[row][column]&TWO) counter++;
  if(constraintGrid[row][column]&THREE) counter++;
  if(constraintGrid[row][column]&FOUR) counter++;
  if(constraintGrid[row][column]&FIVE) counter++;
  if(constraintGrid[row][column]&SIX) counter++;
  if(constraintGrid[row][column]&SEVEN) counter++;
  if(constraintGrid[row][column]&EIGHT) counter++;
  if(constraintGrid[row][column]&NINE) counter++;

  return counter;
}

/*
* This will go to each open cell  and go throgh possible
* solutions and pick a random one usoing recursion it will call itself
* if after it callis itself if it gets a 0 back it will
* revert the change and undo the constrain propogation
*
* Just so I dont forget my idea for later to speed up
* for super complex solutions after propogating several answers  there should become
* sinlge solutions maybe I can run through my simplesolution algorithm but I wont know
* what was propagted by the single solution so if i try this there will
* need to be a snap shot taken of data this might be a terrible idea and the over
* head might  extend the time it takes to solve.
*
* maybe I take a snapshot and attempt to finish solving the snapshot
* if succesfful could luck out but this might be pointless as i add N steps
* for potential success when This is guarenteed
*/
int complexSolution()
{
  /* I want to put this findopen cell step into a function
  but think i need to learn structs to return multiple values
  which I havent learned yet so I can come update later*/
  int cellWithOneR = -1;
  int cellWithTwoR = -1;
  int cellWithThreeR = -1;
  int cellWithFourR = -1;
  int cellWithFiveR = -1;
  int cellWithSixR = -1;
  int cellWithSevenR = -1;
  int cellWithEightR = -1;
  int cellWithNineR = -1;
  int cellWithOneC = -1;
  int cellWithTwoC = -1;
  int cellWithThreeC = -1;
  int cellWithFourC = -1;
  int cellWithFiveC = -1;
  int cellWithSixC = -1;
  int cellWithSevenC = -1;
  int cellWithEightC = -1;
  int cellWithNineC = -1;

  int openCell = FALSE;
  int i = 0;
  int j = 0;
  for (i=0;i<9;i++)
  {
    for (j=0;j<9;j++)
    {
      /*set array location arrays that hold the
      value of a cell with n number of possible solutions*/
      switch (howManySolutions(i,j)) {
        case 1:
        openCell = TRUE;
        cellWithOneR = i;
        cellWithOneC = j;
        break;
        case 2:
        openCell = TRUE;
        cellWithTwoR = i;
        cellWithTwoC = j;
        break;
        case 3:
        openCell = TRUE;
        cellWithThreeR = i;
        cellWithThreeC = j;
        break;
        case 4:
        openCell = TRUE;
        cellWithFourR = i;
        cellWithFourC = j;
        break;
        case 5:
        openCell = TRUE;
        cellWithFiveR = i;
        cellWithFiveC = j;
        break;
        case 6:
        openCell = TRUE;
        cellWithSixR = i;
        cellWithSixC = j;
        break;
        case 7:
        openCell = TRUE;
        cellWithSevenR = i;
        cellWithSevenC = j;
        break;
        case 8:
        openCell = TRUE;
        cellWithEightR = i;
        cellWithEightC = j;
        break;
        case 9:
        openCell = TRUE;
        cellWithNineR = i;
        cellWithNineC = j;
        break;
      }
    }
  }

  if(openCell)
  {
    if(cellWithOneR >=0 && cellWithOneC >=0)
    {
      i = cellWithOneR;
      j = cellWithOneC;
    }
    else if(cellWithTwoR >=0 && cellWithTwoC >=0)
    {
      i = cellWithTwoR;
      j = cellWithTwoC;
    }
    else if(cellWithThreeR >=0 && cellWithThreeC >=0)
    {
      i = cellWithThreeR;
      j = cellWithThreeC;
    }
    else if(cellWithFourR >=0 && cellWithFourC >=0)
    {
      i = cellWithFourR;
      j = cellWithFourC;
    }
    else if(cellWithFiveR >=0 && cellWithFiveC >=0)
    {
      i = cellWithFiveR;
      j = cellWithFiveC;
    }
    else if(cellWithSixR >=0 && cellWithSixC >=0)
    {
      i = cellWithSixR;
      j = cellWithSixC;
    }
    else if(cellWithSevenR >=0 && cellWithSevenC >=0)
    {
      i = cellWithSevenR;
      j = cellWithSevenC;
    }
    else if(cellWithEightR >=0 && cellWithEightC >=0)
    {
      i = cellWithEightR;
      j = cellWithEightC;
    }
    else if(cellWithNineR >=0 && cellWithNineC >=0)
    {
      i = cellWithNineR;
      j = cellWithNineC;
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

int deleteFalseConstraints(int row, int column, int number)
{
  switch (number)
  {
    case 1:
    turnOffConstraint(row,column,ONE);
    return 1;
    case 2:
    turnOffConstraint(row,column,ONE);
    turnOffConstraint(row,column,TWO);
    return 1;
    case 3:
    turnOffConstraint(row,column,ONE);
    turnOffConstraint(row,column,TWO);
    turnOffConstraint(row,column,THREE);
    return 1;
    case 4:
    turnOffConstraint(row,column,ONE);
    turnOffConstraint(row,column,TWO);
    turnOffConstraint(row,column,THREE);
    turnOffConstraint(row,column,FOUR);
    return 1;
    case 5:
    turnOffConstraint(row,column,ONE);
    turnOffConstraint(row,column,TWO);
    turnOffConstraint(row,column,THREE);
    turnOffConstraint(row,column,FOUR);
    turnOffConstraint(row,column,FIVE);
    return 1;
    case 6:
    turnOffConstraint(row,column,ONE);
    turnOffConstraint(row,column,TWO);
    turnOffConstraint(row,column,THREE);
    turnOffConstraint(row,column,FOUR);
    turnOffConstraint(row,column,FIVE);
    turnOffConstraint(row,column,SIX);
    return 1;
    case 7:
    turnOffConstraint(row,column,ONE);
    turnOffConstraint(row,column,TWO);
    turnOffConstraint(row,column,THREE);
    turnOffConstraint(row,column,FOUR);
    turnOffConstraint(row,column,FIVE);
    turnOffConstraint(row,column,SIX);
    turnOffConstraint(row,column,SEVEN);
    return 1;
    case 8:
    turnOffConstraint(row,column,ONE);
    turnOffConstraint(row,column,TWO);
    turnOffConstraint(row,column,THREE);
    turnOffConstraint(row,column,FOUR);
    turnOffConstraint(row,column,FIVE);
    turnOffConstraint(row,column,SIX);
    turnOffConstraint(row,column,SEVEN);
    turnOffConstraint(row,column,EIGHT);
    return 1;
    case 9:
    turnOffConstraint(row,column,ONE);
    turnOffConstraint(row,column,TWO);
    turnOffConstraint(row,column,THREE);
    turnOffConstraint(row,column,FOUR);
    turnOffConstraint(row,column,FIVE);
    turnOffConstraint(row,column,SIX);
    turnOffConstraint(row,column,SEVEN);
    turnOffConstraint(row,column,EIGHT);
    turnOffConstraint(row,column,NINE);
    return 1;

  }
}

void printConstraintGrid()
{
  printf("\n");
  int i = 0;
  int j = 0;
  for(i=0;i<9;i++)
  {
    printf("\n---------------------------\n");
    for(j=0;j<9;j++)
    {
      printf("%3d:%3d|",theGrid[i][j], constraintGrid[i][j]);
    }

  }
}

int tryNextSolution(int row, int column)
{
  int isSuccess = FALSE;

  /*1*/
  if(constraintGrid[row][column]&ONE)
  {
    theGrid[row][column] = 1;
    updateConstraints(row, column, 1, FALSE);
    isSuccess = complexSolution();
    if(isSuccess)
    {
      printf("isSuccess from 1: %d\n", isSuccess);
      return isSuccess;
    }
    else
    {
      theGrid[row][column] = 0;
      /*printConstraintGrid();*/
      createConstraintGrid(); /* could possibly speed up this step*/
      /*printConstraintGrid();*/
      turnOffConstraint(row,column,ONE);
      return 0;
    }
  }

  /*2*/
  if(constraintGrid[row][column]&TWO)
  {
    theGrid[row][column] = 2;
    updateConstraints(row, column, 2, FALSE);
    isSuccess = complexSolution();
    if(isSuccess)
    {
      printf("isSuccess from 2: %d\n", isSuccess);
      return isSuccess;
    }
    else
    {
      theGrid[row][column] = 0;
      /*printConstraintGrid();*/
      createConstraintGrid(); /* could possibly speed up this step*/
      /*printConstraintGrid();*/
      turnOffConstraint(row,column,ONE);
      turnOffConstraint(row,column,TWO);
      return 0;
    }
  }

  /*3*/
  if(constraintGrid[row][column]& THREE)
  {
    theGrid[row][column] = 3;
    updateConstraints(row, column, 3, FALSE);
    isSuccess = complexSolution();
    if(isSuccess)
    {
      printf("isSuccess from 3: %d\n", isSuccess);
      return isSuccess;
    }
    else
    {
      theGrid[row][column] = 0;
      /*printConstraintGrid();*/
      createConstraintGrid(); /* could possibly speed up this step*/
      /*printConstraintGrid();*/
      turnOffConstraint(row,column,ONE);
      turnOffConstraint(row,column,TWO);
      turnOffConstraint(row,column,THREE);
      return 0;
    }
  }

  /*4*/
  if(constraintGrid[row][column]& FOUR)
  {
    theGrid[row][column] = 4;
    updateConstraints(row, column, 4, FALSE);
    isSuccess = complexSolution();
    if(isSuccess)
    {
      printf("isSuccess from 4: %d\n", isSuccess);
      return isSuccess;
    }
    else
    {
      theGrid[row][column] = 0;
      /*printConstraintGrid();*/
      createConstraintGrid(); /* could possibly speed up this step*/
      /*printConstraintGrid();*/
      turnOffConstraint(row,column,ONE);
      turnOffConstraint(row,column,TWO);
      turnOffConstraint(row,column,THREE);
      turnOffConstraint(row,column,FOUR);
      return 0;
    }
  }

  /*5*/
  if(constraintGrid[row][column]& FIVE)
  {
    theGrid[row][column] = 5;
    updateConstraints(row, column, 5, FALSE);
    isSuccess = complexSolution();
    if(isSuccess)
    {
      printf("isSuccess from 5: %d\n", isSuccess);
      return isSuccess;
    }
    else
    {
      theGrid[row][column] = 0;
      /*printConstraintGrid();*/
      createConstraintGrid(); /* could possibly speed up this step*/
      /*printConstraintGrid();*/
      turnOffConstraint(row,column,ONE);
      turnOffConstraint(row,column,TWO);
      turnOffConstraint(row,column,THREE);
      turnOffConstraint(row,column,FOUR);
      turnOffConstraint(row,column,FIVE);
      return 0;
    }
  }

  /*6*/
  if(constraintGrid[row][column]& SIX)
  {
    theGrid[row][column] = 6;
    updateConstraints(row, column, 6, FALSE);
    isSuccess = complexSolution();
    if(isSuccess)
    {
      printf("isSuccess from 6: %d\n", isSuccess);
      return isSuccess;
    }
    else
    {
      theGrid[row][column] = 0;
      /*printConstraintGrid();*/
      createConstraintGrid(); /* could possibly speed up this step*/
      /*printConstraintGrid();*/
      turnOffConstraint(row,column,ONE);
      turnOffConstraint(row,column,TWO);
      turnOffConstraint(row,column,THREE);
      turnOffConstraint(row,column,FOUR);
      turnOffConstraint(row,column,FIVE);
      turnOffConstraint(row,column,SIX);
      return 0;
    }
  }

  /*7*/
  if(constraintGrid[row][column]& SEVEN)
  {
    theGrid[row][column] = 7;
    updateConstraints(row, column, 7, FALSE);
    isSuccess = complexSolution();
    if(isSuccess)
    {
      printf("isSuccess from 7: %d\n", isSuccess);
      return isSuccess;
    }
    else
    {
      theGrid[row][column] = 0;
      /*printConstraintGrid();*/
      createConstraintGrid(); /* could possibly speed up this step*/
      /*printConstraintGrid();*/
      turnOffConstraint(row,column,ONE);
      turnOffConstraint(row,column,TWO);
      turnOffConstraint(row,column,THREE);
      turnOffConstraint(row,column,FOUR);
      turnOffConstraint(row,column,FIVE);
      turnOffConstraint(row,column,SIX);
      turnOffConstraint(row,column,SEVEN);
      return 0;
    }
  }

  /*8*/
  if(constraintGrid[row][column]& EIGHT)
  {
    theGrid[row][column] = 8;
    updateConstraints(row, column, 8, FALSE);
    isSuccess = complexSolution();
    if(isSuccess)
    {
      printf("isSuccess from 8: %d\n", isSuccess);
      return isSuccess;
    }
    else
    {
      theGrid[row][column] = 0;
      /*printConstraintGrid();*/
      createConstraintGrid(); /* could possibly speed up this step*/
      /*printConstraintGrid();*/
      turnOffConstraint(row,column,ONE);
      turnOffConstraint(row,column,TWO);
      turnOffConstraint(row,column,THREE);
      turnOffConstraint(row,column,FOUR);
      turnOffConstraint(row,column,FIVE);
      turnOffConstraint(row,column,SIX);
      turnOffConstraint(row,column,SEVEN);
      turnOffConstraint(row,column,EIGHT);
      return 0;
    }
  }

  /*9*/
  if(constraintGrid[row][column]& NINE)
  {
    theGrid[row][column] = 9;
    updateConstraints(row, column, 9, FALSE);
    isSuccess = complexSolution();
    if(isSuccess)
    {
      printf("isSuccess from 9: %d\n", isSuccess);
      return isSuccess;
    }
    else
    {
      theGrid[row][column] = 0;
      /*printConstraintGrid();*/
      createConstraintGrid(); /* could possibly speed up this step*/
      /*printConstraintGrid();*/
      turnOffConstraint(row,column,ONE);
      turnOffConstraint(row,column,TWO);
      turnOffConstraint(row,column,THREE);
      turnOffConstraint(row,column,FOUR);
      turnOffConstraint(row,column,FIVE);
      turnOffConstraint(row,column,SIX);
      turnOffConstraint(row,column,SEVEN);
      turnOffConstraint(row,column,EIGHT);
      turnOffConstraint(row,column,NINE);
      return 0;
    }

    printf("this should never be reached");
    return 0;
  }
}
/*
* This function loops through constraintGrid if a cell has one possible solution
* fill in theGrid
* will return 1 if it made a change other wise it will return 0 if no changes were made
*/
int fillInSingleConstraints()
{
  int changeMade = FALSE;
  int i = 0;
  int j = 0;
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      switch (constraintGrid[i][j])
      {
        case ONE:
        theGrid[i][j] = 1;
        updateConstraints(i,j,1, TRUE);
        changeMade = TRUE;
        break;
        case TWO:
        theGrid[i][j] = 2;
        updateConstraints(i,j,2, TRUE);
        changeMade = TRUE;
        break;
        case THREE:
        theGrid[i][j] = 3;
        updateConstraints(i,j,3, TRUE);
        changeMade = TRUE;
        break;
        case FOUR:
        theGrid[i][j] = 4;
        updateConstraints(i,j,4, TRUE);
        changeMade = TRUE;
        break;
        case FIVE:
        theGrid[i][j] = 5;
        updateConstraints(i,j,5, TRUE);
        changeMade = TRUE;
        break;
        case SIX:
        theGrid[i][j] = 6;
        updateConstraints(i,j,6, TRUE);
        changeMade = TRUE;
        break;
        case SEVEN:
        theGrid[i][j] = 7;
        updateConstraints(i,j,7, TRUE);
        changeMade = TRUE;
        break;
        case EIGHT:
        theGrid[i][j] = 8;
        updateConstraints(i,j,8, TRUE);
        changeMade = TRUE;
        break;
        case NINE:
        theGrid[i][j] = 9;
        updateConstraints(i,j,9, TRUE);
        changeMade = TRUE;
        break;
      }
    }
  }
  return changeMade;
}

/*this function checks the board that is input to make sure it doesnt
* violate rules of sudoku. It will check to confirm  that a numbers
* doesnt appear twice in any row column or box if it does the input
* is invalid returns 1 if board is valid other wise return 0
*/
int checkIfGridLegal()
{
  int i = 0;
  int j = 0;
  for(i = 0; i <9;i++)
  {
    for(j = 0; j < 9; j++)
    {
      if(theGrid[i][j] > 0)
      {
        if(checkRowDuplicateN(i, theGrid[i][j])) return 0;
        if(checkColumnDuplicateN(j, theGrid[i][j])) return 0;
        if(checkBoxDuplicateN( (i/3), (j/3), theGrid[i][j])) return 0;
      }
    }
  }
  return 1;
}

/*
* function will return 1 if more then one number exists in row
*/
int checkRowDuplicateN(int row, int number)
{
  int numberCounter = 0;
  int j = 0;
  for(j=0;j<9;j++)
  {
    if(theGrid[row][j] == number)
    {
      numberCounter++;
    }
  }
  if(numberCounter >1)
  {
    return 1;
  }
  else
  {
      return 0;
  }
}

/*
* this funtion returns 1 if column contains more then one number
*/
int checkColumnDuplicateN(int column, int number)
{
  int numberCounter = 0;
  int i = 0;
  for(i=0;i<9;i++)
  {
    if(theGrid[i][column] == number)
    {
      numberCounter++;
    }
  }
  if (numberCounter>1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*
* this functions returns 1 if a box contains duplicate number
*/
int checkBoxDuplicateN(int boxRow, int boxColumn, int number)
{
  int numberCounter = 0;
  int i = 0;
  int j = 0;
  for(i=0; i<3; i++)
  {
    for(j = 0; j<3; j++)
    {
      if(theGrid[3*boxRow + i][3*boxColumn+j] == number)
      {
        numberCounter++;
        if(numberCounter>1)
        {
          return 1;
        }
      }
    }
  }
  if(numberCounter>1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*
* My initial thought to attack this function is to assign
* a value to each square that explains what moves are legal.
* if a square can contain all 9 numbers it would be
* represented by 11111111 i can use & to check if available
* or | to add it. if I use up a value i can ^ to get it out of the list
*
* I still need some logic to check if a move is valid.
* This helper method needs to be made first.
*
*/
int createConstraintGrid()
{
  int i = 0;
  int j = 0;
  /* ONE|TWO|THREE|FOUR|FIVE|SIX|SEVEN|EIGHT|NINE == 511 == 111111111
  * I will initialize the constrain grid with 511
  */
  for (i = 0; i < 9; i++)
  {
    for(j=0;j<9;j++)
    {
      constraintGrid[i][j] = 511;
    }
  }

  /* update constraintGrid based on initial
  * theGrid will utilize updateConstraints()
  */
  for(i = 0; i < 9; i++)
  {
    for(j=0; j < 9; j++)
    {
      if (theGrid[i][j] > 0)
      {
        updateConstraints(i, j, theGrid[i][j], TRUE);
      }
    }
  }
  return 1;
}

/*
*this function eliminates all usability at cell location for all numbers
*and propogates constrains for rest of board for that number
*/
int updateConstraints(int inputRow, int inputColumn, int inputNumber, int notComplexCall)
{
  if(theGrid[inputRow][inputColumn] == inputNumber)
  {
    constraintGrid[inputRow][inputColumn] = 0;
  }
  else if (theGrid[inputRow][inputColumn] != inputNumber)
  {
    return 0;
  }
  updateRowConstraints(inputRow, inputNumber);
  updateColumnConstraints(inputColumn, inputNumber);
  updateBoxConstraints((inputRow/3),(inputColumn/3), inputNumber);
  return 1;
}

/*
*this eliminates number from usability in row.
*/
int updateRowConstraints(int row, int number)
{
  int j = 0;
  for(j = 0; j < 9; j++)
  {
    if(constraintGrid[row][j] > 0)
    {
      switch (number)
      {
        case 1:
        if(constraintGrid[row][j] & ONE) constraintGrid[row][j] ^= ONE;
        break;
        case 2:
        if(constraintGrid[row][j] & TWO) constraintGrid[row][j] ^= TWO;
        break;
        case 3:
        if(constraintGrid[row][j] & THREE) constraintGrid[row][j] ^= THREE;
        break;
        case 4:
        if(constraintGrid[row][j] & FOUR) constraintGrid[row][j] ^= FOUR;
        break;
        case 5:
        if(constraintGrid[row][j] & FIVE) constraintGrid[row][j] ^= FIVE;
        break;
        case 6:
        if(constraintGrid[row][j] & SIX) constraintGrid[row][j] ^= SIX;
        break;
        case 7:
        if(constraintGrid[row][j] & SEVEN) constraintGrid[row][j] ^= SEVEN;
        break;
        case 8:
        if(constraintGrid[row][j] & EIGHT) constraintGrid[row][j] ^= EIGHT;
        break;
        case 9:
        if(constraintGrid[row][j] & NINE) constraintGrid[row][j] ^= NINE;
        break;
      }
    }
  }
  return 1;
}

/*
* this eliminates number from usabiolity in column
*/
int updateColumnConstraints(int column, int number)
{
  int i = 0;
  for(i = 0; i < 9; i++)
  {
    if(constraintGrid[i][column] > 0)
    {
      switch (number)
      {
        case 1:
        if(constraintGrid[i][column] & ONE) constraintGrid[i][column] ^= ONE;
        break;
        case 2:
        if(constraintGrid[i][column] & TWO) constraintGrid[i][column] ^= TWO;
        break;
        case 3:
        if(constraintGrid[i][column] & THREE) constraintGrid[i][column] ^= THREE;
        break;
        case 4:
        if(constraintGrid[i][column] & FOUR) constraintGrid[i][column] ^= FOUR;
        break;
        case 5:
        if(constraintGrid[i][column] & FIVE) constraintGrid[i][column] ^= FIVE;
        break;
        case 6:
        if(constraintGrid[i][column] & SIX) constraintGrid[i][column] ^= SIX;
        break;
        case 7:
        if(constraintGrid[i][column] & SEVEN) constraintGrid[i][column] ^= SEVEN;
        break;
        case 8:
        if(constraintGrid[i][column] & EIGHT) constraintGrid[i][column] ^= EIGHT;
        break;
        case 9:
        if(constraintGrid[i][column] & NINE) constraintGrid[i][column] ^= NINE;
        break;
      }
    }
  }
  return 1;
}

/*
*this function eliminates number from usability in box
*/
int updateBoxConstraints(int boxRow, int boxColumn, int number)
{
  int i = 0;
  int j = 0;
  for(i = 0; i <3; i++)
  {
    for(j = 0; j <3; j++)
    {
      if(constraintGrid[(3*boxRow + i)][3*boxColumn+j] > 0)
      {
        switch (number)
        {
          case 1:
          if(constraintGrid[(3*boxRow + i)][3*boxColumn+j] & ONE) constraintGrid[(3*boxRow + i)][3*boxColumn+j] ^= ONE;
          break;
          case 2:
          if(constraintGrid[(3*boxRow + i)][3*boxColumn+j] & TWO) constraintGrid[(3*boxRow + i)][3*boxColumn+j] ^= TWO;
          break;
          case 3:
          if(constraintGrid[(3*boxRow + i)][3*boxColumn+j] & THREE) constraintGrid[(3*boxRow + i)][3*boxColumn+j] ^= THREE;
          break;
          case 4:
          if(constraintGrid[(3*boxRow + i)][3*boxColumn+j] & FOUR) constraintGrid[(3*boxRow + i)][3*boxColumn+j] ^= FOUR;
          break;
          case 5:
          if(constraintGrid[(3*boxRow + i)][3*boxColumn+j] & FIVE) constraintGrid[(3*boxRow + i)][3*boxColumn+j] ^= FIVE;
          break;
          case 6:
          if(constraintGrid[(3*boxRow + i)][3*boxColumn+j] & SIX) constraintGrid[(3*boxRow + i)][3*boxColumn+j] ^= SIX;
          break;
          case 7:
          if(constraintGrid[(3*boxRow + i)][3*boxColumn+j] & SEVEN) constraintGrid[(3*boxRow + i)][3*boxColumn+j] ^= SEVEN;
          break;
          case 8:
          if(constraintGrid[(3*boxRow + i)][3*boxColumn+j] & EIGHT) constraintGrid[(3*boxRow + i)][3*boxColumn+j] ^= EIGHT;
          break;
          case 9:
          if(constraintGrid[(3*boxRow + i)][3*boxColumn+j] & NINE) constraintGrid[(3*boxRow + i)][3*boxColumn+j] ^= NINE;
          break;
        }
      }
    }
  }
}

/*
* I am thinking about using some sort of
* propositional satisfiability to assert
* that the puzzle is solved. still researching.
this will use recursive calls to check the truth
value of 9*9*9 = 729 logical tests. This is a logic puzzle.
i feel. the goal of sudoku fro this perspective is to find a solution
for logical values. I feel there is a way to solve the puzzle this way
but I havent figured it out yet
I will build a check the performs the following check
(rowContainsEveryNumber()&columnContainsEverNumber()&boxContainsEveryNumber())
return 0 if false and true otherwise
*/
int checkIfGridSolved()
{
  /*printf("\n\n\nevery row return value: %d\n", everyRowContainsEveryNumber());
  printf("every column return value: %d\n", columnContainsEverNumber());
  printf("every box return value: %d\n", boxContainsEveryNumber());*/
  return (everyRowContainsEveryNumber()&&columnContainsEverNumber()&&boxContainsEveryNumber());
}

int everyRowContainsEveryNumber()
{
  int truthValue = 1;
  int i = 0;
  int n = 1;
  for(i= 0;i < 9; i++)
  {
    for(n=1;n < 9; n++)
    {
      truthValue = (truthValue && rowContainsNNumber(i,n));
      if(truthValue==0)return truthValue;
    }
  }
  return truthValue;
}
/*
* this function returns nonZero if the row contains n number
*/
int rowContainsNNumber(int row, int number)
{
  int containsNumber = 0;
  int j = 0;
  for (j=0;j<9;j++)
  {
    containsNumber = containsNumber||(theGrid[row][j] == number);
    /*printf("ROW: %d\n column: %d\n number%d\n containsNumber%d", row, j, number, containsNumber);*/
    if (containsNumber) return containsNumber;
  }
  return containsNumber;
}
/*
* this functions checks all
* columns to see if they contain all numbers
*/
int columnContainsEverNumber()
{
  int truthValue = 1;
  int j = 0;
  int n = 1;
  for(j= 0;j < 9; j++)
  {
    for(n=1;n < 9; n++)
    {
      truthValue = (truthValue && columnContainsNNumber(j,n));
      if(truthValue==0)return truthValue;
    }
  }
  return truthValue;
}
/*
*this function checks if a column cantains 1 number
*/
int columnContainsNNumber(int column, int number)
{
  int containsNumber = 0;
  int i = 0;
  for(i=0;i<9;i++)
  {
    containsNumber = containsNumber||(theGrid[i][column] == number);
    if (containsNumber) return containsNumber;
  }
  return containsNumber;
}

/*
* this functions checks 3 by 3 box to see if it contains every number
*/
int boxContainsEveryNumber()
{
  int truthValue = 1;
  int r = 0;
  int c = 0;
  int n = 1;
  for (r=0; r<3;r++)
  {
    for(c=0;c<3;c++)
    {
      for(n=1; n < 9; n++)
      {
        truthValue = (truthValue && boxContainsNNumber(r,c,n));
        if (truthValue == 0) return truthValue;
      }
    }
  }
  return truthValue;
}

/*
* check to see if a given box contains a given number
*/
int boxContainsNNumber(int boxRow, int boxColumn, int number)
{
  int containsNumber = 0;
  int i = 0;
  int j = 0;
  for(i=0; i <3;i++)
  {
    for (j=0; j < 3; j++)
    {
      containsNumber = containsNumber||(theGrid[3*boxRow+i][3*boxColumn +j]== number);
      if (containsNumber) return containsNumber;
    }
  }
  return containsNumber;
}

/*
* This function just loops through theGrid
* if it makes it to the end it means it is
* full and return 1
* returns 0 if not full
*/
int checkIfGridFull()
{
  int i = 0;
  int j = 0;
  for(i= 0;i<9;i++)
  {
    for(j = 0;j<9;j++)
    {
      if(theGrid[i][j]==0)return 0;
    }
  }
  return 1;
}


/*
* this function converts one line at a time into a puzzle to solve
* this function garuntees the to set the charStream to \n or EOF
* if there is an error it will return 0 otherwise 1.
**/
int convertLineToGrid()
{
  /*reinitialize error flags to false to start  off function*/
  errorLineTooShort = FALSE;
  errorNotNumeric = FALSE;
  errorLineTooLong = FALSE;

  /* loop over line and copt to theGrid*/
  int i = 0;
  int count = 0;
  int j = 0;
  for(i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {

      inputLine[count]= charStream;

      if(charStream == '.')
      {
        theGrid[i][j] = 0;
      }
      else if ((charStream >= '0' ) && (charStream <= '9'))
      {
        theGrid[i][j] = (charStream - '0');
      }
      /*test for line to short error */
      else if (charStream == '\n')
      {
        errorLineTooShort = TRUE;
        break;
      }
      /*if it makes it this far than we have nonnumeric char*/
      else
      {
        count++;
        errorNotNumeric = TRUE;
        break;
      }
      count++;
      charStream = getchar();
    }
    /* if we broke out of the first loop due
     to error just break the second one */
    if (errorNotNumeric||errorLineTooShort)
    {
      break;
    }
  }

  /* if we get 81 characters the next char should be'\n'
  but if our line is too short this will keep the stream in order
  if(!errorLineTooShort)
  {
    charStream = getchar();
  }*/
  /* successfull return!!! */
  if(charStream == '\n')
  {
    inputLine[count] = '\0';
    if(errorLineTooShort)
    {
      return 0;
    }
    return 1;
  }
  /* I MEAN ALMOST FRIGGIN successfull!! our line seems to
  be more then 81 characters UGHHH!... we could also have a
  nonnumerical value here as well*/
  else
  {
    errorLineTooLong = TRUE;
    /* we need to return this function with a '\n'...
    ....
    ....   while loop: do your thing */
    while (charStream != '\n' && charStream != EOF)
    {
      inputLine[count] = charStream;
      charStream = getchar();
      count++;
    }
    inputLine[count] ='\0';
    return 0;
  }
}

void printResults()
{
  printf("%s\n", inputLine);
  if(puzzleSolved)
  {
    int i = 0;
    int j = 0;
    for(i=0;i<9;i++)
    {
      for(j=0;j<9;j++)
      {
        printf("%d", theGrid[i][j]);
      }
    }
    printf("\n\n");
  }
  if(noSolution)
  {
    printf("No solution\n\n");
  }
  if(puzzleError)
  {
    printf("Error\n\n");
  }
}
