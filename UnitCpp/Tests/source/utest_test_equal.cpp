//=============================================================================
#include <UnitCpp/Test.h>

//=============================================================================
TEST(test, test_equal)
{
  // test ints are equal
  TEST_EQUAL(-1, -1);
  test_equal(5, 5, "Custom message");

  // test some doubles
  TEST_EQUAL(-2.345, -2.345);
  test_equal(3.14, 3.14, "pi should be pi");

  // now some ints as doubles
  test_equal<double>(7, 7);
  test_equal<double>(-12, -12, "-12 should equal -12");

  // test some strings, in several ways
  TEST_EQUAL(std::string("one"), "one");
  TEST_EQUAL("TWO", "TWO");
  // Use the template methods.
  test_equal<const char*>("ThReE", "ThReE");
  test_equal<std::string>("four", "four");
}
