//=============================================================================
// Issue 4, https://bitbucket.org/davidcorne/unitcpp/issue/4/allow-test_true-test_false-to-work-with
// The following code fails.
//
// std::unique_ptr<int> ptr(new int(5));
// TEST_TRUE(ptr);
//
// This is because test_true/test_false take by copy, not reference.

#include <UnitCpp/Test.h>

//=============================================================================
TEST(Issue, 4)
{
  std::unique_ptr<int> ptr(new int(5));
  TEST_TRUE(ptr);
}
