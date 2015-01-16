#include <UnitCpp.h>

#include <vector>

//=============================================================================
TEST(Test, loop)
{
  std::vector<int> ints;
  stop_printing();
  for (int i = 0; i < 1000; ++i) {
    ints.push_back(i);
    TEST_EQUAL(ints [i], i);
  }
  restart_printing();
  TEST_EQUAL(ints.size(), 1000);
}
