//=============================================================================
// Copyright (c) 2015 David Corne
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

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

  bool group(std::string group_name);
  // Is group_name a group?

  std::ostream& os();
  // Get the stream we are outputting to.
  
private:
  TestRegister();

  TestRegister(const TestRegister&);
  TestRegister& operator=(const TestRegister&);
  // Prohibited copy functions.
  
  friend class TestMenu;
  friend class UnregisteredTestCase;
  friend class UnregisteredTestCase_unregistered;
  
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
  TestMenu menu(*this);
  return menu.create(argc, argv);
}

//=============================================================================
inline bool UnitCpp::TestRegister::group(std::string group_name)
{
  return m_test_table.find(group_name) != std::end(m_test_table);
}
#endif
