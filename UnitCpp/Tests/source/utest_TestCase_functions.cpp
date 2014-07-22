//=============================================================================
#include <UnitCpp/Test.h>

//=============================================================================
TEST(test, test_equal)
{
  // test ints are equal
  TEST_EQUAL(-1, -1);
  test_equal(5, 5, "Custom message.");

  // test some doubles
  TEST_EQUAL(-2.345, -2.345);
  test_equal(3.14, 3.14, "pi should be pi.");

  // now some ints as doubles
  test_equal<double>(7, 7);
  test_equal<double>(-12, -12, "-12 should equal -12.");

  // test some strings, in several ways
  TEST_EQUAL(std::string("one"), "one");
  TEST_EQUAL("TWO", "TWO");
  // Use the template methods.
  test_equal<const char*>("ThReE", "ThReE");
  test_equal<std::string>("four", "four");
}

//=============================================================================
TEST(test, test_not_equal)
{
  // test ints are not equal
  TEST_NOT_EQUAL(12, -1);
  test_not_equal(5, 1, "Custom message");

  // test some doubles
  TEST_NOT_EQUAL(-2.345, 2.345);
  test_not_equal(3.14, 2.72, "pi should not be e.");

  // now some ints as doubles
  test_not_equal<double>(7, 4);
  test_not_equal<double>(-12, 12, "-12 should equal -12.");

  // test some strings, in several ways
  TEST_NOT_EQUAL(std::string("one"), "1");
  TEST_NOT_EQUAL("TWO", "tWo");
  // Use the template methods.
  test_not_equal<const char*>("THREE", "three");
  test_not_equal<std::string>("Four", "four");
}

//=============================================================================
TEST(test, test_less_than)
{
  // test ints are not equal
  TEST_LESS_THAN(-12, -1);
  test_less_than(1, 5, "Custom message.");

  // test some doubles
  TEST_LESS_THAN(-2.345, 2.345);
  test_less_than(2.72, 3.14, "e should be less than pi.");

  // now some ints as doubles
  test_less_than<double>(4, 7);
  test_less_than<double>(-12, 12, "-12 should be less than 12.");
}

//=============================================================================
TEST(test, test_more_than)
{
  // test ints are not equal
  TEST_MORE_THAN(12, -1);
  test_more_than(6, 5, "Custom message.");

  // test some doubles
  TEST_MORE_THAN(6.345, 2.345);
  test_more_than(3.14, 2.72, "pi should be more than e.");

  // now some ints as doubles
  test_more_than<double>(7, 4);
  test_more_than<double>(12, -12, "12 should be more than -12.");
}

//=============================================================================
TEST(test, test_true)
{
  TEST_TRUE(4 < 7);
  TEST_TRUE(4 == 4);
  TEST_TRUE(8 / 2 == 4);
  TEST_TRUE(true);
  TEST_TRUE(1);
  std::string str;
  TEST_TRUE(str.empty());
  TEST_TRUE(!false);
  TEST_TRUE(!0);
}

//=============================================================================
TEST(test, test_false)
{
  TEST_FALSE(4 > 7);
  TEST_FALSE(4 != 4);
  TEST_FALSE(8 / 2 == 4.1);
  TEST_FALSE(false);
  TEST_FALSE(!1);
  std::string str;
  TEST_FALSE(!str.empty());
  TEST_FALSE(!true);
  TEST_FALSE(0);
}

//=============================================================================
TEST(test, test_approx_equal)
{
  double tol = 0.00000001;
  TEST_APPROX_EQUAL(3.0 / 2.0, 1.5, tol);
}

//=============================================================================
class TestException {};

//=============================================================================
void test_exception_function_1(int i)
{
  if (i < 0) {
    throw TestException();
  }
}

//=============================================================================
void test_exception_function_2(int i, int j)
{
  if (i != j) {
    throw TestException();
  }
}


//=============================================================================
TEST(test, test_throws)
{
  bool exception = false;
  try {
    test_exception_function_1(-1);
  } catch (TestException e) {
    exception = true;
  }
  TEST_TRUE(exception);

  test_throws<TestException>(
    "Should throw.",
    test_exception_function_1,
    -1
  );
  TEST_THROWS(test_exception_function_1, TestException, -10);
  TEST_THROWS(test_exception_function_2, TestException, 1, 2);
}
