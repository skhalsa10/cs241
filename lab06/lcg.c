#include "lcg.h"

typedef unsigned long u64;
typedef struct LinearCongruentialGenerator LCG;
u64 calculateP(u64 m);

LCG makeLCG(u64 m, u64 c)
{
  LCG lcg;
  lcg.x = c;
  lcg.m = m;
  lcg.c = c;
  lcg.a = (m%4 == 0) ? (1+2*calculateP(m)):(1+calculateP(m)) ;

  if(lcg.c >= lcg.m || lcg.a >= lcg.m || lcg.a <= 0 || lcg.m <= 0)
  {
    lcg.x = 0;
    lcg.m = 0;
    lcg.a = 0;
    lcg.c = 0;
  }

  return lcg;
}

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
      m /= 2;
    }

    factorFound = 1;
  }
  return (p*m);
}

u64 getNextRandomValue(LCG* lcg)
{
  lcg->x = ((lcg->a*lcg->x) +lcg->c) % lcg->m;
  return lcg->x;
}
