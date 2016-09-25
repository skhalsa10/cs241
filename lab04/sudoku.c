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


/* declare all functions here */
int convertLineToGrid();
int checkIfGridLegal();/*still need to create*/
int checkIfGridFull();
int checkIfGridSolved();
int createConstraintGrid();/*still need to create*/
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
    /*this will always only happen once
    but I want to break out of the set
    of instructions when certain criteria is met
    like an error flag is turned on or a function
    returns 0 */
    /*do
    {
      if(!convertLineToGrid()) break;
      if(checkIfGridFull())
      {
        puzzleSolved = FALSE;
        if(checkIfGridSolved())
        {
          puzzleSolved = TRUE;
        }
        break;
      }
      checkIfGridLegal();
      createConstraintGrid();
      solvePuzzle();
    }
    while(0);*?
    /*printResults();*/
    convertLineToGrid();
    createConstraintGrid();
    printf("solve puzzle: %d\n", solvePuzzle());

  }
}

/*
* this is the brains on this program. it is the algorithm that solves the puzzle
*/
int solvePuzzle()
{
  while(fillInSingleConstraints());
  if(!checkIfGridFull())
  {
    return complexSolution();
  }
  return 1;
}

int undoMove(int inputRow,int inputColumn,int inputNumber)
{
  printf("undoMove entered\n");
  theGrid[inputRow][inputColumn] = 0;
  undoRowConstraint(inputRow, inputNumber);
  undoColumnConstraint(inputRow, inputNumber);
  undoBoxConstraint((inputRow/3), (inputColumn/3), inputNumber);
  return 1;
}

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
  /*printf("complexSolution has been called\n");*/
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
  printf("i: %d | j: %d\n", i, j);
  if(constraintGrid[i][j]&ONE)
  {
    printf("entering ONE\n");
    theGrid[i][j] = 1;
    updateConstraints(i,j,1, FALSE);
    if(!complexSolution())
    {
      undoMove(i,j,1);
      constraintGrid[i][j] ^= ONE;
    }
    else
    {
      return 1;
    }
  }
  else if (constraintGrid[i][j]&TWO)
  {
    printf("entering TWO\n");
    theGrid[i][j] = 2;
    updateConstraints(i,j,2, FALSE);
    if(!complexSolution())
    {
      undoMove(i,j,2);
      constraintGrid[i][j] ^= TWO;
    }
    else
    {
      return 1;
    }
  }
  else if (constraintGrid[i][j]&THREE)
  {
    printf("entering THREE\n");
    theGrid[i][j] = 3;
    updateConstraints(i,j,3, FALSE);
    if(!complexSolution())
    {
      undoMove(i,j,3);
      constraintGrid[i][j] ^= THREE;
    }
    else
    {
      return 1;
    }
  }
  else if (constraintGrid[i][j]&FOUR)
  {
    printf("entering FOUR\n");
    theGrid[i][j] = 4;
    updateConstraints(i,j,4, FALSE);
    if(!complexSolution())
    {
      undoMove(i,j,4);
      constraintGrid[i][j] ^= FOUR;
    }
    else
    {
      return 1;
    }
  }
  else if (constraintGrid[i][j]&FIVE)
  {
    printf("entering FIVE\n");
    theGrid[i][j] = 5;
    updateConstraints(i,j,5, FALSE);
    if(!complexSolution())
    {
      undoMove(i,j,5);
      constraintGrid[i][j] ^= FIVE;
    }
    else
    {
      return 1;
    }
  }
  else if (constraintGrid[i][j]&SIX)
  {
    printf("entering SIX\n");
    theGrid[i][j] = 6;
    updateConstraints(i,j,6, FALSE);
    if(!complexSolution())
    {
      undoMove(i,j,6);
      constraintGrid[i][j] ^= SIX;
    }
    else
    {
      return 1;
    }
  }
  else if (constraintGrid[i][j]&SEVEN)
  {
    printf("entering SEVEN\n");
    theGrid[i][j] = 7;
    updateConstraints(i,j,7, FALSE);
    if(!complexSolution())
    {
      undoMove(i,j,7);
      constraintGrid[i][j] ^= SEVEN;
    }
    else
    {
      return 1;
    }
  }
  else if (constraintGrid[i][j]&EIGHT)
  {
    printf("entering EIGHT\n");
    theGrid[i][j] = 8;
    updateConstraints(i,j,8, FALSE);
    if(!complexSolution())
    {
      undoMove(i,j,8);
      constraintGrid[i][j] ^= EIGHT;
    }
    else
    {
      return 1;
    }
  }
  else if (constraintGrid[i][j]&NINE)
  {
    printf("entering NINE\n");
    theGrid[i][j] = 9;
    updateConstraints(i,j,9, FALSE);
    if(!complexSolution())
    {
      undoMove(i,j,9);
      constraintGrid[i][j] ^= NINE;
    }
    else
    {
      return 1;
    }
  }
  else
  {
    printf("about to return false from complex\n");
    return 0;
  }

  /*for (i = 0; i < 9; i++)
  {
    for(j=0;j<9;j++)
    {
      while(constraintGrid[i][j] != 0)
      {
        if(constraintGrid[i][j]&ONE)
        {
          theGrid[i][j] = 1;
          updateConstraints(i,j,1, FALSE);
          if(!complexSolution())
          {
            undoMove(i,j,1);
            constraintGrid[i][j] ^= ONE;
          }
          else
          {
            return 1;
          }
        }
        else if (constraintGrid[i][j]&TWO)
        {
          theGrid[i][j] = 2;
          updateConstraints(i,j,2, FALSE);
          if(!complexSolution())
          {
            undoMove(i,j,2);
            constraintGrid[i][j] ^= TWO;
          }
          else
          {
            return 1;
          }
        }
        else if (constraintGrid[i][j]&THREE)
        {
          theGrid[i][j] = 3;
          updateConstraints(i,j,3, FALSE);
          if(!complexSolution())
          {
            undoMove(i,j,3);
            constraintGrid[i][j] ^= THREE;
          }
          else
          {
            return 1;
          }
        }
        else if (constraintGrid[i][j]&FOUR)
        {
          theGrid[i][j] = 4;
          updateConstraints(i,j,4, FALSE);
          if(!complexSolution())
          {
            undoMove(i,j,4);
            constraintGrid[i][j] ^= FOUR;
          }
          else
          {
            return 1;
          }
        }
        else if (constraintGrid[i][j]&FIVE)
        {
          theGrid[i][j] = 5;
          updateConstraints(i,j,5, FALSE);
          if(!complexSolution())
          {
            undoMove(i,j,5);
            constraintGrid[i][j] ^= FIVE;
          }
          else
          {
            return 1;
          }
        }
        else if (constraintGrid[i][j]&SIX)
        {
          theGrid[i][j] = 6;
          updateConstraints(i,j,6, FALSE);
          if(!complexSolution())
          {
            undoMove(i,j,6);
            constraintGrid[i][j] ^= SIX;
          }
          else
          {
            return 1;
          }
        }
        else if (constraintGrid[i][j]&SEVEN)
        {
          theGrid[i][j] = 7;
          updateConstraints(i,j,7, FALSE);
          if(!complexSolution())
          {
            undoMove(i,j,7);
            constraintGrid[i][j] ^= SEVEN;
          }
          else
          {
            return 1;
          }
        }
        else if (constraintGrid[i][j]&EIGHT)
        {
          theGrid[i][j] = 8;
          updateConstraints(i,j,8, FALSE);
          if(!complexSolution())
          {
            undoMove(i,j,8);
            constraintGrid[i][j] ^= EIGHT;
          }
          else
          {
            return 1;
          }
        }
        else if (constraintGrid[i][j]&NINE)
        {
          theGrid[i][j] = 9;
          updateConstraints(i,j,9, FALSE);
          if(!complexSolution())
          {
            undoMove(i,j,9);
            constraintGrid[i][j] ^= NINE;
          }
          else
          {
            return 1;
          }
        }
        else
        {
          printf("about to return false from complex\n");
          return 0;
        }
      }
    }
  }*/
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
  if((theGrid[inputRow][inputColumn] == inputNumber) && notComplexCall)
  {
    constraintGrid[inputRow][inputColumn] = 0;
  }
  else
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
}
