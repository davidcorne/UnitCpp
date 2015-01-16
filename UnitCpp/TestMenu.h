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
//
// This is a class for creating a test menu. This can be interactive or it will
// choose a test based on command line arguments.
//
// The interactive menu will look something like this:
//
// ================================================================================
// 0) All tests.
// 
// ================================================================================
// 1) TestCast
//   2) "TestCast:test_display"
// 
// ================================================================================
// 3) TestRegister
//   4) "TestRegister:A"
// 
// ================================================================================
// 5) test
//   6) "test:test_equal"
//   7) "test:test_not_equal"
//   8) "test:test_less_than"
//   9) "test:test_more_than"
//   10) "test:test_true"
//   11) "test:test_false"
//   12) "test:test_approx_equal"
//   13) "test:test_throws"

#ifndef UnitCppInteractiveTestMenu_H
#define UnitCppInteractiveTestMenu_H

#include <memory>
#include <vector>

//=============================================================================
namespace UnitCpp {

class TestRegister;
class TestCase;
  
//=============================================================================
class TestMenu {
public:

  TestMenu(TestRegister& test_register);

  ~TestMenu();

  int create(int argc, char** argv);
  // Creates a menu or chooses from the menu depending on the arguments.
  
private:

  TestMenu(const TestMenu&);
  TestMenu& operator=(const TestMenu&);
  // Prohibited copy functions.
  
  void draw_interactive_menu();
  // Prints the interactive menu.

  int run_interactively();
  // Prints the interactive menu, gets a valid choice from it then returns the
  // test result.

  int run_test(int choice);
  // Runs the choosen test.

  int run_test(std::stringstream& ss, bool& ok) const;
  // Pass in a stringstream, get a number out of it and run the test, bool is
  // for if the stringstream does not contain a valid test.
  
  //===========================================================================
  class TestMenuItem {
  public:

    TestMenuItem();
    
    virtual ~TestMenuItem() = 0;

    virtual size_t indent() const = 0;
    // How far down the tree is this?

    virtual bool banner() const = 0;
    // Should we print a banner before it?

    virtual std::string title() const = 0;
    // The title to print.
    
    virtual int run() = 0;
    // Run this test.

  private:

    TestMenuItem(const TestMenuItem&);
    TestMenuItem& operator=(const TestMenuItem&);
    // Prohibited copy functions.
    
  };

  //===========================================================================
  class TestMenuItemCase : public TestMenuItem {
  public:
    
    TestMenuItemCase(TestCase* test_case);

    virtual ~TestMenuItemCase();

    virtual size_t indent() const override;
    // How far down the tree is this?

    virtual bool banner() const override;
    // Should we print a banner before it?

    virtual std::string title() const override;
    // The title to print.
    
    virtual int run() override;
    // Run this test.
    
  private:

    TestMenuItemCase(const TestMenuItemCase&);
    TestMenuItemCase& operator=(const TestMenuItemCase&);
    // Prohibited copy functions.

    TestCase* m_test_case;
  };

  //===========================================================================
  class TestMenuItemGroup : public TestMenuItem {
  public:
    
    TestMenuItemGroup(TestRegister& test_register, std::string group_name);

    virtual ~TestMenuItemGroup();

    virtual bool banner() const override;
    // Should we print a banner before it?

    virtual std::string title() const override;
    // The title to print.
    
    virtual size_t indent() const override;
    // How far down the tree is this?

    virtual int run() override;
    // Run this test.
    
  private:
    
    TestMenuItemGroup(const TestMenuItemGroup&);
    TestMenuItemGroup& operator=(const TestMenuItemGroup&);
    // Prohibited copy functions.

    TestRegister& m_test_register;
    std::string m_group_name;
  };
  
  //===========================================================================
  class TestMenuAllTests : public TestMenuItem {
  public:
    
    TestMenuAllTests(TestRegister& test_register);

    virtual ~TestMenuAllTests();

    virtual bool banner() const override;
    // Should we print a banner before it?

    virtual std::string title() const override;
    // The title to print.
    
    virtual size_t indent() const override;
    // How far down the tree is this?

    virtual int run() override;
    // Run this test.
    
  private:
    
    TestMenuAllTests(const TestMenuAllTests&);
    TestMenuAllTests& operator=(const TestMenuAllTests&);
    // Prohibited copy functions.

    TestRegister& m_test_register;
  };
  
  std::vector<std::shared_ptr<TestMenuItem> > m_tests;
};
  
}

//----- Source

#include <UnitCpp/TestRegister.h>
#include <sstream>
//----- TestMenu

//=============================================================================
inline UnitCpp::TestMenu::TestMenu(
  UnitCpp::TestRegister& test_register
)
{
  std::map<std::string, std::list<TestCase*> >& test_table =
    test_register.m_test_table;
  m_tests.push_back(
    std::make_shared<TestMenu::TestMenuAllTests>(test_register)
  );
  for (
    auto group_it = std::begin(test_table);
    group_it != std::end(test_table);
    ++group_it
  ) {
    auto group_item = std::make_shared<TestMenu::TestMenuItemGroup>(
      test_register,
      group_it->first
    );
    m_tests.push_back(group_item);
    for (
      auto test_it = std::begin(group_it->second);
      test_it != std::end(group_it->second);
      ++test_it
    ) {
      auto test_item = std::make_shared<TestMenu::TestMenuItemCase>(*test_it);
      m_tests.push_back(test_item);
    }
  }
}

//=============================================================================
inline UnitCpp::TestMenu::~TestMenu()
{
}

//=============================================================================
inline int UnitCpp::TestMenu::create(int argc, char** argv)
{
  if (argc == 1) {
    // no command line arguments given.
    return run_interactively();
  } else if (argc == 2) {
    // Run the test number given.
    std::string argument(argv[1]);
    std::stringstream ss(argument);
    bool ok = false;
    int result = run_test(ss, ok);
    if (ok) {
      return result;
    }    
  } else {
    std::cerr << "Too many arguments given." << std::endl;
  }
  return 1;
}

//=============================================================================
inline int UnitCpp::TestMenu::run_test(std::stringstream& ss, bool& ok) const
{
  size_t choice = m_tests.size() + 1;
  if (!(ss >> choice) || choice >= m_tests.size()) {
    std::cerr << ss.str() << " is not a valid test number." << std::endl;
    ok = false;
  } else {
    ok = true;
    return m_tests[choice]->run();
  }
  return 1;
}

//=============================================================================
inline int UnitCpp::TestMenu::run_interactively()
{
  draw_interactive_menu();
  std::ostream& os = TestRegister::test_register().os();
  std::string input("");
  bool ok = false;
  int result = 1;
  while (!ok) {
    os << "Choose: ";
    std::getline(std::cin, input);
    std::stringstream ss(input);
    result = run_test(ss, ok);
  }
  return result;
}

//=============================================================================
inline void UnitCpp::TestMenu::draw_interactive_menu()
{
  std::ostream& os = TestRegister::test_register().os();
  // string 'fill' constructor.
  std::string banner(80, '=');
  int index = 0;
  for (auto it = std::begin(m_tests); it != std::end(m_tests); ++it) {
    auto test_item = *it;
    if (test_item->banner()) {
      os << "\n" << banner << "\n";
    }
    std::string indent(test_item->indent(), ' ');
    os << indent << index << ") " << test_item->title() << "\n";
    ++index;
  }
  os << "\n";
}

//----- TestMenuItem

//=============================================================================
inline UnitCpp::TestMenu::TestMenuItem::TestMenuItem()
{
}

//=============================================================================
inline UnitCpp::TestMenu::TestMenuItem::~TestMenuItem()
{
}

//----- TestMenuItemGroup

//=============================================================================
inline UnitCpp::TestMenu::TestMenuItemGroup::TestMenuItemGroup(
  TestRegister& test_register,
  std::string group_name
)
  : m_test_register(test_register),
    m_group_name(group_name)
{
}

//=============================================================================
inline UnitCpp::TestMenu::TestMenuItemGroup::~TestMenuItemGroup()
{
}

//=============================================================================
inline size_t UnitCpp::TestMenu::TestMenuItemGroup::indent() const
{
  return 0;
}

//=============================================================================
inline bool UnitCpp::TestMenu::TestMenuItemGroup::banner() const
{
  return true;
}

//=============================================================================
inline std::string UnitCpp::TestMenu::TestMenuItemGroup::title() const
{
  return m_group_name;
}

//=============================================================================
inline int UnitCpp::TestMenu::TestMenuItemGroup::run()
{
  return UnitCpp::TestRegister::test_register().run_tests(m_group_name);
}

//----- TestMenuAllTests

//=============================================================================
inline UnitCpp::TestMenu::TestMenuAllTests::TestMenuAllTests(
  TestRegister& test_register
)
  : m_test_register(test_register)
{
}

//=============================================================================
inline UnitCpp::TestMenu::TestMenuAllTests::~TestMenuAllTests()
{
}

//=============================================================================
inline size_t UnitCpp::TestMenu::TestMenuAllTests::indent() const
{
  return 0;
}

//=============================================================================
inline bool UnitCpp::TestMenu::TestMenuAllTests::banner() const
{
  return true;
}

//=============================================================================
inline std::string UnitCpp::TestMenu::TestMenuAllTests::title() const
{
  return "All tests.";
}

//=============================================================================
inline int UnitCpp::TestMenu::TestMenuAllTests::run()
{
  return UnitCpp::TestRegister::test_register().run_tests();
}

//----- TestMenuItemCase

//=============================================================================
inline UnitCpp::TestMenu::TestMenuItemCase::TestMenuItemCase(
  TestCase* test_case
)
  : m_test_case(test_case)
{
}

//=============================================================================
inline UnitCpp::TestMenu::TestMenuItemCase::~TestMenuItemCase()
{
}

//=============================================================================
inline size_t UnitCpp::TestMenu::TestMenuItemCase::indent() const
{
  return 2;
}

//=============================================================================
inline bool UnitCpp::TestMenu::TestMenuItemCase::banner() const
{
  return false;
}

//=============================================================================
inline std::string UnitCpp::TestMenu::TestMenuItemCase::title() const
{
  return m_test_case->title();
}

//=============================================================================
inline int UnitCpp::TestMenu::TestMenuItemCase::run()
{
  m_test_case->run();
  m_test_case->display_results(TestRegister::test_register().os());
  int ret_val = 1;
  if (m_test_case->passed()) {
    ret_val = 0;
  }
  return ret_val;
}

#endif
