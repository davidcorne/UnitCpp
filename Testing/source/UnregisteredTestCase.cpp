//=============================================================================
#include "Testing/UnregisteredTestCase.h"

#include <cassert>

//=============================================================================
UnitCpp::UnregisteredTestCase::UnregisteredTestCase(
  std::function<void(TestCase&)> test_function
)
  : UnitCpp::TestCase("UnregisteredTestCase", "fake"),
    m_test_function(test_function)
{
  // should have registered "UnregisteredTestCase", remove it
  UnitCpp::TestRegister::test_register().m_test_table.erase(
    "UnregisteredTestCase"
  );
  
}

//=============================================================================
UnitCpp::UnregisteredTestCase::~UnregisteredTestCase()
{
}

//=============================================================================
void UnitCpp::UnregisteredTestCase::run()
{
  m_test_function(*this);
}
