#include <stdio.h>
#define FILLED 1
#define UNFILLED 0

/************************************************
* Siri Khalsa                                   *
* 09/15/2016                                    *
* CS241 001                                     *
* LAB04                                         *
*                                               *
* This is a sudoku solver                       *
* it will take in 81 charcters and treat        *
* it as a new line after 9 digits               *
*                                               *
* it will take in a puzzle                      *
* and it will immediagtely check to make sure   *
* it only has appropriate characters            *
* It will make sure it is not past 81 numbers   *
*                                               *
* It will then send the puzzle through          *
* solve algorithm                               *
*                                               *
*************************************************/

/* Declare variables the column arrays are specific for each numbers
for instance if there is a 1 in column 3 than column1[2] != 0 would be TRUE*/
int column1[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int column2[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int column3[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int column4[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int column4[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int column6[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int column7[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int column8[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int column9[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};

/* Declare variables the row arrays are specific for each numbers
for instance if there is a 1 in row 2 than row1[1] != 0 would be TRUE*/
int row1[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int row2[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int row3[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int row4[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int row4[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int row6[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int row7[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int row8[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};
int row9[] = {UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED,UNFILLED, UNFILLED, UNFILLED};

/* declare sub arrays sub00 refers to sub array row0 column0 */
int sub00[3][3];
int sub01[3][3];
int sub02[3][3];
int sub10[3][3];
int sub11[3][3];
int sub12[3][3];
int sub20[3][3];
int sub21[3][3];
int sub22[3][3];
