/***********************************************
*                                              *
*               By: Siri Khalsa                *
*                  10/29/16                    *
*                 CS-241 001                   *
*      lcg.c | Linear Congruential Generator   *
*                                              *
***********************************************/
#include "lcg.h"

/*declare typedef and external fns*/
typedef unsigned long u64;
typedef struct LinearCongruentialGenerator LCG;
u64 calculateP(u64 m);

/***************************************************
* Perameters:
* u64 m is the modulus for LCG
* u64 c is the incrementer for the LCG
****************************************************
* this function wil create an LCG with given input
****************************************************
* Returns LCG
****************************************************/
LCG makeLCG(u64 m, u64 c)
{
  LCG lcg;
  lcg.x = c;
  lcg.m = m;
  lcg.c = c;
  lcg.a = (m%4 == 0) ? (1+2*calculateP(m)):(1+calculateP(m)) ;

  if(lcg.c >= lcg.m || lcg.a >= lcg.m || lcg.a <= 0 || lcg.m <= 0 || lcg.c <= 0)
  {
    lcg.x = 0;
    lcg.m = 0;
    lcg.a = 0;
    lcg.c = 0;
  }

  return lcg;
}

/***************************************************
* Perameters:
* u64 m is the modulus for LCG
****************************************************
* Returns product of m’s unique prime factors).
****************************************************/
u64 calculateP(u64 m)
{
  int i;
  int p = 1;
  int factorFound = 1;
  for(i = 2;( i*i < m );i++)
  {
    while(m%i ==0)
    {
      if(factorFound) p *= i;
      factorFound = 0;
      m /= i;
    }

    factorFound = 1;
  }
  return (p*m);
}

/***************************************************
* Perameters:
* LCG* lcg
****************************************************
* updates x to hold next number in sequence
****************************************************
* Returns x(value in psuedo random sequence)
* before it is updated
****************************************************/
u64 getNextRandomValue(LCG* lcg)
{
  u64 temp = lcg->x;
  lcg->x = ((lcg->a*lcg->x) +lcg->c) % lcg->m;
  return temp;
}
