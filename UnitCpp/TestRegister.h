//=============================================================================

#ifndef TestRegister_H
#define TestRegister_H

#include <memory>
#include <map>
#include <list>

class TestCase;

//=============================================================================
class TestRegister {
public:

  static TestRegister& test_register();
  
  ~TestRegister();

  void register_test(std::string class_name, TestCase* test);
  
  int run_tests(std::string class_name);
  // Returns an int so it can be used for return value of main().
  
private:
  TestRegister();

  std::map<std::string, std::list<TestCase*> >  m_test_table;
};

#include <UnitCpp/TestCase.h>
#include <iostream>

//=============================================================================
TestRegister& TestRegister::test_register()
{
  static TestRegister s_register;
  return s_register;
}

//=============================================================================
TestRegister::TestRegister()
{
}

//=============================================================================
TestRegister::~TestRegister()
{
}

//=============================================================================
void TestRegister::register_test(
  std::string class_name,
  TestCase* test
)
{
  m_test_table[class_name].push_back(test);
}

//=============================================================================
int TestRegister::run_tests(std::string class_name)
{
  int return_code = 0;
  std::list<TestCase*> tests = m_test_table.at(class_name);
  for (auto it = std::begin(tests); it != std::end(tests); ++it) {
    TestCase* test = *it;
    test->run();
    test->display_results(std::cout);
    if (!test->passed()) {
      return_code = 1;
    }
  }
  return return_code;
}

#endif
