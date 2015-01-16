//=============================================================================
// Copyright (c) 2015 David Corne
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// //=============================================================================
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
// 2) Running all tests;
//      TestRegister::test_register().run_tests(group/class_name);
//    to run all tests in group or
//      TestRegister::test_register().run_tests();
//    to run all tests.
//
// 3) To access the internals of a class in a test (e.g. call private
//    functions/access members) you need to declare the tests a friend.
//    you do this by specifying UNITCPP_FRIEND_TEST(group, name) in the
//    class you are testing.
//    e.g.
//      class Container {
//      public:
//      ...
//      private:
//        UNITCPP_FRIEND_TEST(Container, internals)
//        int m_member;
//      };
//      
//      TEST(Container, internals)
//      {
//        Container container;
//        TEST_EQUAL(container.m_member, 5);
//      }

#ifndef UnitCppTest_H
#define UnitCppTest_H

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
  class test_##GROUP##_##NAME : public UnitCpp::TestCase { \
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
