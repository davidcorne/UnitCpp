//=============================================================================
// 

#include <UnitCpp.h>

#include "Testing/Fraction.h"

//=============================================================================
TEST(Wish, static_assert)
{
  TEST_STATIC((Fraction<1, 2>::Numerator == 1), "1/2 numerator is 1.");
}
