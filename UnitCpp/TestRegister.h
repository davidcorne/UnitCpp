//=============================================================================

#ifndef UnitCppTestRegister_H
#define UnitCppTestRegister_H

#include <memory>
#include <map>
#include <list>


namespace UnitCpp {

class TestCase;

//=============================================================================
class TestRegister {
public:

  static TestRegister& test_register();
  
  ~TestRegister();

  void register_test(std::string group_name, TestCase* test);
  
  int run_tests();
  // Run all of the tests.
  
  int run_tests(std::string group_name);
  // Run only the tests registed for group_name.

  int run_tests_interactive(int argc, char** argv);
  // Run tests using command line input.

  std::ostream& os();
  // Get the stream we are outputting to.
  
private:
  TestRegister();

  friend class TestMenu;
  
  std::map<std::string, std::list<TestCase*> >  m_test_table;
  std::list<TestCase*> m_failures;
  std::ostream& m_os;
};
}

#include <UnitCpp/TestCase.h>
#include <UnitCpp/TestMenu.h>
#include <iostream>

//=============================================================================
inline UnitCpp::TestRegister& UnitCpp::TestRegister::test_register()
{
  static TestRegister s_register;
  return s_register;
}

//=============================================================================
inline UnitCpp::TestRegister::TestRegister()
  : m_os(std::cout)
{
}

//=============================================================================
inline UnitCpp::TestRegister::~TestRegister()
{
}

//=============================================================================
inline void UnitCpp::TestRegister::register_test(
  std::string group_name,
  TestCase* test
)
{
  m_test_table[group_name].push_back(test);
}

//=============================================================================
inline int UnitCpp::TestRegister::run_tests(std::string group_name)
{
  int return_code = 0;
  std::list<TestCase*> tests = m_test_table.at(group_name);
  for (auto it = std::begin(tests); it != std::end(tests); ++it) {
    TestCase* test = *it;
    test->run();
    test->display_results(m_os);
    if (!test->passed()) {
      return_code = 1;
      m_failures.push_back(test);
    }
  }
  return return_code;
}

//=============================================================================
inline int UnitCpp::TestRegister::run_tests()
{
  int return_code = 0;
  for (auto it = std::begin(m_test_table); it != std::end(m_test_table); ++it) {
    return_code += run_tests(it->first);
  }
  if (return_code) {
    // there were some failures.
    m_os << "Failures:\n\n";
    for (auto it = std::begin(m_failures); it != std::end(m_failures); ++it) {
      TestCase& test = **it;
      m_os
        << "Test "
        << test.title()
        << "\n"
        << test.fail_reason()
        << "\n";
    }
  }
  return return_code;
}

//=============================================================================
inline std::ostream& UnitCpp::TestRegister::os()
{
  return m_os;
}

//=============================================================================
inline int UnitCpp::TestRegister::run_tests_interactive(int argc, char** argv)
{
  // <nnn> // string 'fill' constructor.
  // <nnn> std::string banner(80, '=');
  // <nnn> banner += "\n";
  // <nnn> int index = 1;
  // <nnn> for (
  // <nnn>   auto group_it = std::begin(m_test_table);
  // <nnn>   group_it != std::end(m_test_table);
  // <nnn>   ++group_it
  // <nnn> ) {
  // <nnn>   m_os
  // <nnn>     << banner
  // <nnn>     << group_it->first
  // <nnn>     << "\n";
  // <nnn>   for (
  // <nnn>     auto test_it = std::begin(group_it->second);
  // <nnn>     test_it != std::end(group_it->second);
  // <nnn>     ++test_it
  // <nnn>   ) {
  // <nnn>     m_os
  // <nnn>       << "  "
  // <nnn>       << index
  // <nnn>       << ") "
  // <nnn>       << (*test_it)->title()
  // <nnn>       << "\n";
  // <nnn>     ++index;
  // <nnn>   }
  // <nnn>   m_os << "\n";
  // <nnn> }
  TestMenu menu(*this);
  return menu.create(argc, argv);
}
#endif
