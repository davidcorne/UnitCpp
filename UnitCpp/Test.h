//=============================================================================

#ifndef Test_H
#define Test_H

#include <UnitCpp/TestRegister.h>
#include <UnitCpp/TestCase.h>

#define TEST(cls, test_name) \
  class test_factorial_test_one : public TestCase { \
public: \
  void run(); \
  \
}; \
test_factorial_test_one; \
void test_factorial_test_one::run()

#define RUN_TESTS(cls) \
  TestRegistertest_factorial_test_one test; \
  test.run();
#endif
