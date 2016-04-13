//=============================================================================
// Issue 3, https://bitbucket.org/davidcorne/unitcpp/issue/3/test-macros-fail-with-some-arguments
// The following code fails.
//
// template <int N, int D>
// struct Fraction {
//   constexpr static const int Numerator = N;
//   constexpr static const int Denominator = D;
// };
// 
// TEST(MetaFractions, dimensions)
// {
//   TEST_EQUAL(Fraction<1, 2>::Numerator, 1);
// }

// Note: removed constexpr to work in older compilers.

#include <UnitCpp.h>
#include "Testing/Fraction.h"

//=============================================================================
TEST(Issue, 3)
{
  // The original code:
  //   TEST_EQUAL(Fraction<1, 2>::Numerator, 1);
  // This was a mistake of mine, this seperates into
  //   test_equal((Fraction<1), (2>::Numerator)...
  // The problem is the comma, this needs to be protected from the macro by the
  // caller.
  TEST_EQUAL((Fraction<1, 2>::Numerator), 1);
  TEST_EQUAL((Fraction<1, 2>::Denominator), 2);
}
