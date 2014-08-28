//=============================================================================
#include <UnitCpp/TestRegister.h>

//=============================================================================
int main(int argc, char** argv)
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(
    argc,
    argv
  );
}
