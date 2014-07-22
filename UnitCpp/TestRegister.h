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
  
  int run_tests();
  // Run all of the tests.
  
  int run_tests(std::string class_name);
  // Returns an int so it can be used for return value of main().
  
private:
  TestRegister();

  std::map<std::string, std::list<TestCase*> >  m_test_table;
};

#include <UnitCpp/TestCase.h>
#include <iostream>

//=============================================================================
inline TestRegister& TestRegister::test_register()
{
  static TestRegister s_register;
  return s_register;
}

//=============================================================================
inline TestRegister::TestRegister()
{
}

//=============================================================================
inline TestRegister::~TestRegister()
{
}

//=============================================================================
inline void TestRegister::register_test(
  std::string class_name,
  TestCase* test
)
{
  m_test_table[class_name].push_back(test);
}

//=============================================================================
inline int TestRegister::run_tests(std::string class_name)
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

//=============================================================================
inline int TestRegister::run_tests()
{
  int return_code = 0;
  for (auto it = std::begin(m_test_table); it != std::end(m_test_table); ++it) {
    return_code += run_tests(it->first);
  }
  return return_code;
}

#endif
