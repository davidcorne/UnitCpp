//=============================================================================
#include <UnitCpp/Test.h>

//=============================================================================
class TestA {

};

//=============================================================================
TEST(TestRegister, A)
{
  using namespace UnitCpp;
  TestRegister& test_register = TestRegister::test_register();
  char* one = new char[2];
  one[0] = '1';
  one[1] = 0;
  char* argv[] = {0, one};
  int value = test_register.run_tests_interactive(2, argv);
  TEST_EQUAL(value, 0);

  delete[] one;
}
