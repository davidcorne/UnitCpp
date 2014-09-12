//=============================================================================
// Test the UnregisteredTestCase

#include <UnitCpp/Test.h>

#include "Testing/UnregisteredTestCase.h"

using namespace UnitCpp;

//=============================================================================
TEST(UnregisteredTestCase, constructor)
{
  UnregisteredTestCase unregistered_test(
    [](TestCase&){}
  );
  
}

//=============================================================================
TEST(UnregisteredTestCase, unregistered)
{
  UnregisteredTestCase unregistered_test(
    [](TestCase&){}
  );
  TEST_FALSE(TestRegister::test_register().group("UnregisteredTestCase"));
}

//=============================================================================
TEST(UnregisteredTestCase, run)
{
  bool was_run = false;
  UnregisteredTestCase unregistered_test(
    [&was_run](TestCase&){was_run = true;}
  );
  TEST_FALSE(was_run);  
  unregistered_test.run();
  TEST_TRUE(was_run);  
}
