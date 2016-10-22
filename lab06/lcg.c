#include "lcg.h"

typedef unsigned long = u64;
typedef struct LinearCongruentialGenerator = LCG;

LCG makeLCG(u64 m, u64 c)
{
  LCG lcg;
  lcg.x = c;

  return lcg;
}

u64 calculateP(u64 m)
{
  /*algorithm to calculate the unique prime factorization*/
  return p;
}
