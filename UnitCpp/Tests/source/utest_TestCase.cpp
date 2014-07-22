//=============================================================================
#include <UnitCpp/Test.h>

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
