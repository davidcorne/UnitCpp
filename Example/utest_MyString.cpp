#include <UnitCpp/Test.h>
#include "MyString.h"

//=============================================================================
TEST(MyString, length_test)
{
  MyString str("This is a string");
  TEST_EQUAL(str.length(), 16);
  TEST_NOT_EQUAL(str.length(), 17);
  TEST_LESS_THAN(str.length(), 20);
  TEST_MORE_THAN(str.length(), 10);
  TEST_APPROX_EQUAL(str.length(), 15, 1.1); // test the length is within 1.1 of 15
}

//=============================================================================
TEST(MyString, validity_test)
{
  MyString invalid_string;
  TEST_FALSE(invalid_string.valid());

  MyString valid_string("");
  TEST_TRUE(valid_string.valid());

#ifdef UNITCPP_TEST_THROWS_AVAILABLE
  TEST_THROWS([&](){invalid_string.length();}, MyString::InvalidStringException);
#endif // UNITCPP_TEST_THROWS_AVAILABLE

}
