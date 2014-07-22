//=============================================================================
#include <UnitCpp/Test.h>

//=============================================================================
TEST(test, test_equal)
{
  // test ints are equal
  test_equal(-1, -1);
  test_equal(5, 5, "5 should equal 5");

  // test some doubles
  test_equal(-2.345, -2.345);
  test_equal(3.14, 3.14, "pi should be pi");
}
