//=============================================================================
// 

#include <UnitCpp.h>

#include "Testing/Fraction.h"

//=============================================================================
TEST(Wish, static_assert)
{
  TEST_STATIC(
    (Fraction<1, 2>::Numerator == 1),
    "Wish::static_assert 1/2 numerator is 1."
  );
  // Make sure that if it passes, it prints the message into the log.
  std::stringstream ss;
  display_results(ss);
  size_t index = ss.str().find("Wish::static_assert 1/2 numerator is 1.");
  TEST_NOT_EQUAL(index, std::string::npos);
  
}
