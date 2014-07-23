//=============================================================================
#include "Maths.h"
#include <UnitCpp/Test.h>

//=============================================================================
TEST(Maths, sqrt_results)
{
  double result = Maths::sqrt(4.0);
  TEST_EQUAL(result, 2);

  result = Maths::sqrt(2);
  TEST_APPROX_EQUAL(result, 1.414, 0.001);
  
}

//=============================================================================
TEST(Maths, is_square)
{
  int square = 16;
  TEST_TRUE(Maths::is_square(square));
  int non_square = 5;
  TEST_FALSE(Maths::is_square(non_square));
}

#ifdef UNITCPP_TEST_THROWS_AVAILABLE
//=============================================================================
TEST(Maths, sqrt_precondition)
{
  TEST_THROWS(Maths::sqrt, Maths::OutOfRangeException, -1);
}
#endif // UNITCPP_TEST_THROWS_AVAILABLE

