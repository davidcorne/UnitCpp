//=============================================================================


#ifndef utest_Factorial_H
#define utest_Factorial_H

#include <iostream>
#include <UnitCpp/Test.h>
#include "Factorial.h"

//=============================================================================
TEST(factorial, test_one)
{
  test_equal(factorial(1), 1);
  test_not_equal(factorial(1), 0);
  test_less_than(factorial(5), 356);
  test_equal(5, 5, "5 should equal 5");
}

//=============================================================================
TEST(factorial, test_two)
{
  test_equal(factorial(1), 1);
  test_not_equal(factorial(1), 0);
  test_less_than(factorial(5), 356);
  test_equal(5, 5, "5 should equal 5");
}

//=============================================================================
int main()
{
  return TestRegister::test_register().run_tests("factorial");
}

#endif
