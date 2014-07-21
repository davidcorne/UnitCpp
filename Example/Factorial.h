#ifndef Factorial_H
#define Factorial_H

//=============================================================================
double factorial(int i)
{
  if (i == 0) return 1;
  return i * factorial(i-1);
}

#endif
