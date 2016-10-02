
/***********************************************
*                                              *
*               By: Siri Khalsa                *
*                  10/02/16                    *
*                 CS-241 001                   *
*           Sudoku.c | Sudoku Solver           *
*                                              *
***********************************************/


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
#define CELLSELECTION 1
#define ISSIMPLESOLUTIONON 0
#define DEBUG 0
#define NUM2MASK(x) (1 << (x-1))


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
int updateConstraints(int inputRow, int inputColumn, int inputNumber, unsigned int constraintGridToUpdate[][9]);
int updateRowConstraints(int row, int number,unsigned int constraintGridToUpdate[][9]);
int updateColumnConstraints(int column, int number, unsigned int constraintGridToUpdate[][9]);
int updateBoxConstraints(int boxRow, int boxColumn, int number, unsigned int constraintGridToUpdate[][9]);
int fillInSingleConstraints();
int complexSolution(int i, int j, int n, unsigned int originalConstraintGrid[][9]);
int simpleSolution();
int howManySolutions(int row, int column, unsigned int constraintGridToCheck[][9] );
int copyConstraints(unsigned int copyToThisGrid[][9], unsigned int fromThisGrid[][9]);

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
  return 1;
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
  int n;
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
  n = 1;
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
*unsigned int
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
    if(ISSIMPLESOLUTIONON)
    {
      /*printf("performing simple solution\n");*/
      return simpleSolution();
    }
    else
    {
      /*printf("running complexSolution\n");*/
      return complexSolution(-1,-1,-1, constraintGrid);
    }
  }
  return 1;
}




/*****************************************************************
parameters:
int row: row index of cell in question
int column: column index of cell in question
****************************************************************
* this function returns how many possible solutions are left
*****************************************************************/
int howManySolutions(int row,int column, unsigned int constraintGridToCheck[][9])
{
  int i;
  int counter = 0;
  for(i = 1;i <=9; i++)
  {
    if(constraintGridToCheck[row][column]&NUM2MASK(i)) counter++;
  }

  /*if(constraintGridToCheck[row][column]&ONE) counter++;
  if(constraintGridToCheck[row][column]&TWO) counter++;
  if(constraintGridToCheck[row][column]&THREE) counter++;
  if(constraintGridToCheck[row][column]&FOUR) counter++;
  if(constraintGridToCheck[row][column]&FIVE) counter++;
  if(constraintGridToCheck[row][column]&SIX) counter++;
  if(constraintGridToCheck[row][column]&SEVEN) counter++;
  if(constraintGridToCheck[row][column]&EIGHT) counter++;
  if(constraintGridToCheck[row][column]&NINE) counter++;*/

  return counter;
}

int copyConstraints(unsigned int copyToThisGrid[][9], unsigned int fromThisGrid[][9])
{
  int i = 0;
  int j = 0;
  for(i = 0; i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      copyToThisGrid[i][j] = fromThisGrid[i][j];
    }
  }
  return 1;
}
/*****************************************************************
* This function is the complex enhanced solving algorithm:
* I am very dissapointed in the spead of this.  I am getting 2min 30 sec currently
* the single.in puzzle supposidly can be solved in 4 tenths of a second
* so something is obviously wrong.
*
* Algorithm:
* Select an open cell with the least amount of choices. if there is no more
* return 1 the puzzle is solved.
* or continue...
* select the first available choices in list of constraints plug it in and start at beginning
* if theGrid contains no solution but the constraint grid is empty or
* allconstraints have been tried with no success return 0.
*****************************************************************
* possible ways to improve:
* 1. make a copy of the constraint grid ever call to the complex solution
*    if this fails there will be no need to undo failed attempts
*    i could probably call a helper function at the beginning of the complex
     that duplicates the constrainGrid the question is what will cost less
     the 81 steps to duplicate the grid or the random steps it take to
     undo failed attempts. it is worth testing. I may be able to reintroduce
     the idea of filling in single constraints during each iteration as I dont have to
     worry about backtracking after the fact
* 2. This i know for a fact will increase speed. if I use the idea of preemptive sets
     There is a theorem around this so it will be proven to work.
     a preemptive set is  a list of M number of numbers 2<=m<=8 with a list of m cells
     with a property that only numbers from the set can occupy those cells
     this means we can aliminate it from other cells.
     so if i had the list of possible solutions as 57 i would need this exact set in
     of possible number in exactly two cells because there are two numbers in the set
     if it was 138 we would need this exact set in 3 cells
     if we find a preemptive set like 57 for example if the m cells are in the same row
     column or box  then it can be eliminated from the rest of the cells
     in the row column or box. After this is done it may immediately open
     single constrain possibility these steps can be repeated and should in theory
     eliminate MANY wrong answers from needing to be guessed.

*****************************************************************/

int complexSolution(int i, int j, int n, unsigned int originalConstraintGrid[][9])
{
  int nConversion;
  int openCell;
  /* this next set of really long code will find the
   cell with the least amount of possible solutions*/
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
  /*printf("i: %d j: %d n: %d \n",i,j,n);*/
  unsigned int localConstraintGrid[9][9];

  copyConstraints(localConstraintGrid, originalConstraintGrid);
  /*printf("before localConstraintGrid[%d][%d]: %d\n", i, j, localConstraintGrid[i][j] );*/
  if(n>=0)
  {
    updateConstraints(i,j,n,localConstraintGrid);
  }

  /*while(fillInSingleConstraints());*/



  /*printf("after localConstraintGrid[%d][%d]: %d\n", i, j, localConstraintGrid[i][j] );
  printf("after localConstraintGrid[0][1]: %d\n", localConstraintGrid[0][1] );
  printf("after theGrid[0][1]: %d\n", theGrid[0][1] );*/

  openCell = FALSE;
  i = 0;
  j = 0;
  if(CELLSELECTION ==0)
  {
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
}

if(CELLSELECTION ==1)
{
  /******************************************************************************************/
  /*this for just sents variables above to an index that hold x amount of solutions*/
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      if (theGrid[i][j]==0)
      {
        if(localConstraintGrid[i][j]==0) return 0;
        openCell = TRUE;
        switch (howManySolutions(i,j,localConstraintGrid))
        {
          case 1:
          cellWithOneR = i;
          cellWithOneC = j;

          break;
          case 2:
          cellWithTwoR = i;
          cellWithTwoC = j;

          break;
          case 3:
          cellWithThreeR = i;
          cellWithThreeC = j;

          break;
          case 4:
          cellWithFourR = i;
          cellWithFourC = j;
          break;
          case 5:
          cellWithFiveR = i;
          cellWithFiveC = j;
          break;
          case 6:
          cellWithSixR = i;
          cellWithSixC = j;
          break;
          case 7:
          cellWithSevenR = i;
          cellWithSevenC = j;
          break;
          case 8:
          cellWithEightR = i;
          cellWithEightC = j;
          break;
          case 9:
          cellWithNineR = i;
          cellWithNineC = j;
          break;
        }
      }

    }

  }

  /*a terrible hack to set i and j to the variable of lowest magnitude*/
  if((cellWithOneR>=0)&&(cellWithOneC>=0))
  {
    i = cellWithOneR;
    j = cellWithOneC;
  }
  else if((cellWithTwoR>=0)&&(cellWithTwoC>=0))
  {
    i = cellWithTwoR;
    j = cellWithTwoC;
  }
  else if((cellWithThreeR>=0)&&(cellWithThreeC>=0))
  {
    i = cellWithThreeR;
    j = cellWithThreeC;
  }
  else if((cellWithFourR>=0)&&(cellWithFourC>=0))
  {
    i = cellWithFourR;
    j = cellWithFourC;
  }
  else if((cellWithFiveR>=0)&&(cellWithFiveC>=0))
  {
    i = cellWithFiveR;
    j = cellWithFiveC;
  }
  else if((cellWithSixR>=0)&&(cellWithSixC>=0))
  {
    i = cellWithSixR;
    j = cellWithSixC;
  }
  else if((cellWithSevenR>=0)&&(cellWithSevenC>=0))
  {
    i = cellWithSevenR;
    j = cellWithSevenC;
  }
  else if((cellWithEightR>=0)&&(cellWithEightC>=0))
  {
    i = cellWithEightR;
    j = cellWithEightC;
  }
  else if((cellWithNineR>=0)&&(cellWithNineC>=0))
  {
    i = cellWithNineR;
    j = cellWithNineC;
  }
}
/*
printf("i: %d, j: %d\n",i, j );
printf("localConstraintGrid[i][j]: %d\n", localConstraintGrid[i][j]);*/
/*************************************************************************************************/

  /* if there are no open cells left it means the puzzle is finally solved*/
  if(openCell == FALSE)
  {
    return 1;
  }

  /* if this open cell has 0 solutions based on
  constraint grid or if the grid is not legal then error return 0*/
  if((localConstraintGrid[i][j] == 0))
  {
    return 0;

  }



  /*loop over ever possible solution plug it in check if legal
  * if not legal try next move if it is legal call complexSolution again.*/
  n = 1;
  nConversion = 0;
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
    /*printf("localConstraintGrid[%d][%d] = %d \n",i, j, localConstraintGrid[i][j]);
    printf("nConversion = %d\n", nConversion);
    printf("localConstraintGrid[i][j]&nConversion = %d\n", localConstraintGrid[i][j]&nConversion);*/
    if(localConstraintGrid[i][j]&nConversion)
    {
      theGrid[i][j] = n;
        if(complexSolution(i,j,n,localConstraintGrid))
        {
          return 1;
        }

    }
    theGrid[i][j] = 0;

  }

  return 0;
}


/*****************************************************************
* This function loops through constraintGrid if a cell
* has one possible solution fill in theGrid
* will return 1 if it made a change other wise
* it will return 0 if no changes were made
*****************************************************************/
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
        updateConstraints(i,j,1, constraintGrid);
        changeMade = TRUE;
        break;
        case TWO:
        theGrid[i][j] = 2;
        updateConstraints(i,j,2, constraintGrid);
        changeMade = TRUE;
        break;
        case THREE:
        theGrid[i][j] = 3;
        updateConstraints(i,j,3, constraintGrid);
        changeMade = TRUE;
        break;
        case FOUR:
        theGrid[i][j] = 4;
        updateConstraints(i,j,4, constraintGrid);
        changeMade = TRUE;
        break;
        case FIVE:
        theGrid[i][j] = 5;
        updateConstraints(i,j,5, constraintGrid);
        changeMade = TRUE;
        break;
        case SIX:
        theGrid[i][j] = 6;
        updateConstraints(i,j,6, constraintGrid);
        changeMade = TRUE;
        break;
        case SEVEN:
        theGrid[i][j] = 7;
        updateConstraints(i,j,7, constraintGrid);
        changeMade = TRUE;
        break;
        case EIGHT:
        theGrid[i][j] = 8;
        updateConstraints(i,j,8, constraintGrid);
        changeMade = TRUE;
        break;
        case NINE:
        theGrid[i][j] = 9;
        updateConstraints(i,j,9, constraintGrid);
        changeMade = TRUE;
        break;
      }
    }
  }
  return changeMade;
}

/*****************************************************************
* this function checks the board that is input to make sure it doesnt
* violate rules of sudoku. It will check to confirm  that a numbers
* doesnt appear twice in any row column or box if it does the input
* is invalid returns 1 if board is valid other wise return 0
*****************************************************************/
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

/****************************************************************
* parameters:
* int row: the row that is being checked for duplicate numbers
* int number: the number in question
*****************************************************************
* function will return 1 if more then one number exists in row
*****************************************************************/
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

/****************************************************************
* Parameters:
* int column: the column being checked for duplicate number
* int number: the num,ber in question
******************************************************************
* this funtion returns 1 if column contains more then one number
*****************************************************************/
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

/**************************************************************
* Parameters:
* int boxRow: index for boxRow
* int boxcolumn: index for box column
* int number: number being checked if it is duplicated
***************************************************************
* this functions returns 1 if a box contains duplicate number
***************************************************************/
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

/***********************************************************************
* This function assigns a number to each constraingrid location.
* based on the following: 111111111 this number means all possible numbers
* 1 through 9 can exist in this location. 000000000 this number means
* it should already have a solution in the same location in the grid
**********************************************************************/
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
        updateConstraints(i, j, theGrid[i][j], constraintGrid);
      }
    }
  }
  return 1;
}

/*************************************************************************
* Parameters:
* int inputRow: the index where the number exists
* int inputcolumn: the index where the number exists
* int inputNumber: the number in question
* int cotComplexCall: currently needs to be eliminated
**************************************************************************
* this function eliminates all usability at cell location for all numbers
* and propogates constrains for rest of board for that number
*************************************************************************/
int updateConstraints(int inputRow, int inputColumn, int inputNumber, unsigned int constraintGridToUpdate[][9])
{
  if(theGrid[inputRow][inputColumn] == inputNumber)
  {
    constraintGridToUpdate[inputRow][inputColumn] = 0;
  }
  else if (theGrid[inputRow][inputColumn] != inputNumber)
  {
    printf("returning 0 from update constraints");
    return 0;
  }
  updateRowConstraints(inputRow, inputNumber, constraintGridToUpdate);
  updateColumnConstraints(inputColumn, inputNumber, constraintGridToUpdate);
  updateBoxConstraints((inputRow/3),(inputColumn/3), inputNumber, constraintGridToUpdate);
  return 1;
}

/***********************************************************
* Parameters:
* int row: the row to elimate the number from
* int number: the number to eliminates
************************************************************
*this eliminates number from usability in row.
************************************************************/
int updateRowConstraints(int row, int number, unsigned int constraintGridToUpdate[][9])
{
  int j = 0;
  for(j = 0; j < 9; j++)
  {
    if(constraintGridToUpdate[row][j] > 0)
    {
      switch (number)
      {
        case 1:
        if(constraintGridToUpdate[row][j] & ONE) constraintGridToUpdate[row][j] ^= ONE;
        break;
        case 2:
        if(constraintGridToUpdate[row][j] & TWO) constraintGridToUpdate[row][j] ^= TWO;
        break;
        case 3:
        if(constraintGridToUpdate[row][j] & THREE) constraintGridToUpdate[row][j] ^= THREE;
        break;
        case 4:
        if(constraintGridToUpdate[row][j] & FOUR) constraintGridToUpdate[row][j] ^= FOUR;
        break;
        case 5:
        if(constraintGridToUpdate[row][j] & FIVE) constraintGridToUpdate[row][j] ^= FIVE;
        break;
        case 6:
        if(constraintGridToUpdate[row][j] & SIX) constraintGridToUpdate[row][j] ^= SIX;
        break;
        case 7:
        if(constraintGridToUpdate[row][j] & SEVEN) constraintGridToUpdate[row][j] ^= SEVEN;
        break;
        case 8:
        if(constraintGridToUpdate[row][j] & EIGHT) constraintGridToUpdate[row][j] ^= EIGHT;
        break;
        case 9:
        if(constraintGridToUpdate[row][j] & NINE) constraintGridToUpdate[row][j] ^= NINE;
        break;
      }
    }
  }
  return 1;
}

/*************************************************************
* parameters:
* int column this is the column the number will be eliminated from
* int number: the number to eliminate
**************************************************************
* this eliminates number from usabiolity in column
**************************************************************/
int updateColumnConstraints(int column, int number, unsigned int constraintGridToUpdate[][9])
{
  int i = 0;
  for(i = 0; i < 9; i++)
  {
    if(constraintGrid[i][column] > 0)
    {
      switch (number)
      {
        case 1:
        if(constraintGridToUpdate[i][column] & ONE) constraintGridToUpdate[i][column] ^= ONE;
        break;
        case 2:
        if(constraintGridToUpdate[i][column] & TWO) constraintGridToUpdate[i][column] ^= TWO;
        break;
        case 3:
        if(constraintGridToUpdate[i][column] & THREE) constraintGridToUpdate[i][column] ^= THREE;
        break;
        case 4:
        if(constraintGridToUpdate[i][column] & FOUR) constraintGridToUpdate[i][column] ^= FOUR;
        break;
        case 5:
        if(constraintGridToUpdate[i][column] & FIVE) constraintGridToUpdate[i][column] ^= FIVE;
        break;
        case 6:
        if(constraintGridToUpdate[i][column] & SIX) constraintGridToUpdate[i][column] ^= SIX;
        break;
        case 7:
        if(constraintGridToUpdate[i][column] & SEVEN) constraintGridToUpdate[i][column] ^= SEVEN;
        break;
        case 8:
        if(constraintGridToUpdate[i][column] & EIGHT) constraintGridToUpdate[i][column] ^= EIGHT;
        break;
        case 9:
        if(constraintGridToUpdate[i][column] & NINE) constraintGridToUpdate[i][column] ^= NINE;
        break;
      }
    }
  }
  return 1;
}

/**************************************************************
* Parameters:
* int boxRow: is the index used to point to box row
* int boxCOlumn: this is the index used for the box column
* int number: this is the number that we have proven cant be
* in the box and will delete from all grids
****************************************************************
* this function eliminates number from usability in box
****************************************************************/
int updateBoxConstraints(int boxRow, int boxColumn, int number, unsigned int constraintGridToUpdate[][9])
{
  int i = 0;
  int j = 0;
  for(i = 0; i <3; i++)
  {
    for(j = 0; j <3; j++)
    {
      if(constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] > 0)
      {
        switch (number)
        {
          case 1:
          if(constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] & ONE)
          {
            constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] ^= ONE;
          }
          break;
          case 2:
          if(constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] & TWO) constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] ^= TWO;
          break;
          case 3:
          if(constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] & THREE) constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] ^= THREE;
          break;
          case 4:
          if(constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] & FOUR) constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] ^= FOUR;
          break;
          case 5:
          if(constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] & FIVE) constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] ^= FIVE;
          break;
          case 6:
          if(constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] & SIX) constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] ^= SIX;
          break;
          case 7:
          if(constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] & SEVEN) constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] ^= SEVEN;
          break;
          case 8:
          if(constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] & EIGHT) constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] ^= EIGHT;
          break;
          case 9:
          if(constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] & NINE) constraintGridToUpdate[(3*boxRow + i)][3*boxColumn+j] ^= NINE;
          break;
        }
      }
    }
  }
  return 1;
}

/*
* this function checks to see if the puzzle is solved which
* by definition means every row, column, and box contains
* every number.
*/
int checkIfGridSolved()
{
  /*printf("\n\n\nevery row return value: %d\n", everyRowContainsEveryNumber());
  printf("every column return value: %d\n", columnContainsEverNumber());
  printf("every box return value: %d\n", boxContainsEveryNumber());*/
  return (everyRowContainsEveryNumber()&&columnContainsEverNumber()&&boxContainsEveryNumber());
}

/***********************************************************
* this function checks every row to
* see if it contains every number
************************************************************/
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
*parameters:
* int row: to be iterated over
* int number to check if it is in row
************************************************************
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

/********************************************************************
* Parameters:
* int column: the column that will be interated over
* int number: the number that will be checked if it is in the column
**********************************************************************
*this function checks if a column cantains 1 number
*********************************************************************/
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

/********************************************************************
* this functions checks EVERY 3 by 3 box to see if it contains every number
*It utilized boxContainsNNumber and gives it every number
*******************************************************************/
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

/*************************************************************
* Parameters:
* int boxRow: this will be an offset and mutliplied by THREE
* int boxColumn: this is an offset and miltiplied by 3
* int number: number in question
**************************************************************
* check to see if a given box contains a given number
**************************************************************/
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

/*************************************************************
* This function just loops through theGrid
* if it makes it to the end it means it is
* full and return 1
* returns 0 if not full
**************************************************************/
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


/****************************************************************
* this function converts one line at a time into a puzzle to solve
* this function garuntees the to set the charStream to \n or EOF
* if there is an error it will return 0 otherwise 1.
* it will trun on boolean flags for different errors however the
* spec doesnt ask for what is failing.
*****************************************************************/
int convertLineToGrid()
{
  /* i gave to declare this up here for some
   reason before any other types of code*/
  int i;
  int count;
  int j;
  /*reinitialize error flags to false to start  off function*/
  errorLineTooShort = FALSE;
  errorNotNumeric = FALSE;
  errorLineTooLong = FALSE;

  /* loop over line and copt to theGrid*/
  i = 0;
  count = 0;
  j = 0;
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

/*************************************************************
*
* This function just prints what is expected to the console
*
*************************************************************/
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
