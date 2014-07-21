//=============================================================================


#ifndef utest_Factorial_H
#define utest_Factorial_H

#include <iostream>
#include <UnitCpp/Test.h>
#include "Factorial.h"

//=============================================================================
class test_factorial_test_one : public TestCase { 
public:
  test_factorial_test_one(std::string group, std::string name);
  virtual void run() override; 
  
} test_factorial_test_one_instance("factorial", "test_one");
test_factorial_test_one::test_factorial_test_one(std::string group, std::string name)
  : TestCase(group, name)
{
}
void test_factorial_test_one::run()
{
  test_equal(factorial(1), 1);
  test_not_equal(factorial(1), 0);
  test_less_than(factorial(5), 35);
  test_equal(5, 5, "5 should equal 5");
}


//=============================================================================
int main()
{
  TestRegister::test_register().run_tests("factorial");
  return 0;
}

#endif
