//=============================================================================
#include <UnitCpp.h>

#include "Testing/UnregisteredTestCase.h"

#include <sstream>
#include <stdexcept>

//=============================================================================
TEST(ExceptionCatch, std_exception)
{
  UnitCpp::UnregisteredTestCase test([](TestCase& test_case) {
      test_case.test_true(true, "ExceptionCatch:test:1");
      test_case.test_equal(1, 1, "ExceptionCatch:test:2");
      throw std::logic_error("Illogical!");
  });
  test.run_harness();
  // Test the case failed
  TEST_FALSE(test.passed());

  // Test the printed output.
  std::stringstream ss;
  test.display_results(ss);
  std::string results(ss.str());
  std::size_t index;
  
  index = results.find("ExceptionCatch:test:1");
  TEST_NOT_EQUAL(index, std::string::npos);

  index = results.find("ExceptionCatch:test:2");
  TEST_NOT_EQUAL(index, std::string::npos);

  index = results.find("Illogical");
  TEST_NOT_EQUAL(index, std::string::npos);
}

struct CustomException {};

//=============================================================================
TEST(ExceptionCatch, custom_exception)
{
  UnitCpp::UnregisteredTestCase test([](TestCase&) {
      throw CustomException();
  });
  test.run_harness();
  // Test the case failed
  TEST_FALSE(test.passed());
  
  std::stringstream ss;
  test.display_results(ss);
  std::string results(ss.str());
  std::size_t index;

  index = results.find("Unknown exception thrown.");
  TEST_NOT_EQUAL(index, std::string::npos);
}
