//=============================================================================
//
// This is the header to include for all the functionality of UnitCpp.
//
// This library should be used as follows;
// 1) Creating a test;
//      TEST(group/class_name, test_name)
//      {
//        ...
//      }
//    e.g.
//      TEST(PrimeCalculator, test_first_5)
//      {
//        test_false(is_prime(0));
//        test_false(is_prime(1));
//        test_true(is_prime(2));
//        test_true(is_prime(3));
//        test_false(is_prime(4));
//      }
//     To see what functions to use inside tests, check out TestCase.h
//
//  2) Running all tests;
//       TestRegister::test_register().run_tests(group/class_name);
//     to run all tests in group or
//       TestRegister::test_register().run_tests();
//     to run all tests.

#ifndef Test_H
#define Test_H

#include <UnitCpp/TestRegister.h>
#include <UnitCpp/TestCase.h>

// This is the implementation, you don't need to look at this, but if you're
// interested read on.

// This is the macro which expands to create a new test case.
// TEST(factorial, test_one) expands to (with newlines added);
//   class test_factorial_test_one : public TestCase {
//   public:
//
//     test_factorial_test_one(std::string group, std::string name);
//   
//     virtual void run() override;
//   } test_factorial_test_one_instance("factorial", "test_one");
//   
//   test_factorial_test_one::test_factorial_test_one(
//     std::string group,
//     std::string name
//   )
//     : TestCase(group, name)
//   {
//   }
//   void test_factorial_test_one::run()
//
// How this works is each test is a new class deriving from TestCase. Also
// each one has an instance in global scope (test_factorial_test_one_instance)
// which on construction registers itself with the singleton TestRegister.

//=============================================================================
#define TEST(GROUP, NAME)                            \
  class test_##GROUP##_##NAME : public TestCase { \
public: \
  test_##GROUP##_##NAME(std::string group, std::string name); \
  virtual void run() override; \
  \
  } test_##GROUP##_##NAME##_instance(#GROUP, #NAME);        \
test_##GROUP##_##NAME::test_##GROUP##_##NAME(std::string group, std::string name) \
  : TestCase(group, name) \
{ \
} \
void test_##GROUP##_##NAME::run() 

#endif
