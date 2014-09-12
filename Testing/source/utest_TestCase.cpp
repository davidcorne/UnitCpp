//=============================================================================
#include <UnitCpp/Test.h>
#include "Testing/TestClass.h"

#include <sstream>

//=============================================================================
TEST(TestCast, test_display)
{
  TEST_TRUE(4 < 7);
  std::stringstream ss;
  display_results(ss);
  size_t index = ss.str().find("4 < 7");
  TEST_NOT_EQUAL(index, std::string::npos);
}

//=============================================================================
TEST(TestClass, test_constructor)
{
  // demonstrates class internals access.
  TestClass example(5);
  example.double_value();
  TEST_EQUAL(example.m_i, 10);
}

//=============================================================================
TEST(TestClass, stop_print)
{
  stop_print();
  TEST_TRUE(4 < 7);
  restart_print();
  TEST_TRUE(4 < 8);
  std::stringstream ss;
  display_results(ss);
  size_t index = ss.str().find("4 < 7");
  TEST_EQUAL(index, std::string::npos);
  index = ss.str().find("4 < 8");
  TEST_NOT_EQUAL(index, std::string::npos);
}
