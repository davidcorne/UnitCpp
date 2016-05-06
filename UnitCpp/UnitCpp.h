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
// This is the header to include for all the functionality of UnitCpp.
//
// This library should be used as follows;
// 1) Creating a test;
//      TEST(group/class_name, test_name)
//      {
//        ...
//      }
//    e.g.
//      TEST(PrimeCalculator, test_first_5)
//      {
//        test_false(is_prime(0));
//        test_false(is_prime(1));
//        test_true(is_prime(2));
//        test_true(is_prime(3));
//        test_false(is_prime(4));
//      }
//     To see what functions to use inside tests, check out TestCase.h
//
// 2) Running all tests;
//      TestRegister::test_register().run_tests(group/class_name);
//    to run all tests in group or
//      TestRegister::test_register().run_tests();
//    to run all tests.
//
// 3) To access the internals of a class in a test (e.g. call private
//    functions/access members) you need to declare the tests a friend.
//    you do this by specifying UNITCPP_FRIEND_TEST(group, name) in the
//    class you are testing.
//    e.g.
//      class Container {
//      public:
//      ...
//      private:
//        UNITCPP_FRIEND_TEST(Container, internals)
//        int m_member;
//      };
//      
//      TEST(Container, internals)
//      {
//        Container container;
//        TEST_EQUAL(container.m_member, 5);
//      }

#ifndef UnitCpp_H
#define UnitCpp_H

// System includes
#include <memory>
#include <map>
#include <iostream>
#include <vector>
#include <sstream>

//=============================================================================
//----- Compiler detail
//=============================================================================

// For using visual studio. Support is from Visual Studio 2013.
#ifdef _MSC_VER
#if _MSC_VER >= 1800 // Visual Studio 2013's internal code.
#define UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED 1
#endif // _MSC_VER >= 1800
#endif // ifdef _MSC_VER

// For g++ variadic templates supported in 4.3 or later.
#ifdef __GNUC__
// if it's 4.X
#if __GNUC__ == 4
#if __GNUC_MINOR__ >= 3
#define UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED 1
#endif // __GNUC_MINOR__ >= 3
#endif // __GNUC__ == 4

// later versions than 4.
#if __GNUC__ > 4
#define UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED 1
#endif // __GNUC__ > 4

#endif // ifdef __GNUC__

#if defined(__clang__) && !defined(_MSC_VER)
#define UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED __has_feature(cxx_variadic_templates)
#endif // ifdef __clang__

#ifndef UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED
#define UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED 0
#endif // ifndef UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED

//=============================================================================
//----- Capabilities
//=============================================================================

#define UNITCPP_TEST_THROWS_AVAILABLE UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED

//=============================================================================
//----- Macro defines.
//=============================================================================

#define TEST(GROUP, NAME)                            \
  class test_##GROUP##_##NAME : public UnitCpp::TestCase { \
public: \
  test_##GROUP##_##NAME(std::string group, std::string name); \
  virtual void run() override; \
  \
  } test_##GROUP##_##NAME##_instance(#GROUP, #NAME);        \
test_##GROUP##_##NAME::test_##GROUP##_##NAME(std::string group, std::string name) \
  : TestCase(group, name) \
{ \
} \
void test_##GROUP##_##NAME::run() 

#define UNITCPP_INTERNALS_S(x) #x
#define UNITCPP_INTERNALS_S_(x) UNITCPP_INTERNALS_S(x)

#define TEST_MESSAGE(MESSAGE) \
  "\"" MESSAGE "\" " __FILE__ ":" UNITCPP_INTERNALS_S_(__LINE__)

#define TEST_EQUAL(A, B, ...)                                       \
  test_equal((A), (B), TEST_MESSAGE(#A " should equal " #B ". " #__VA_ARGS__))

#define TEST_NOT_EQUAL(A, B, ...) \
  test_not_equal((A), (B), TEST_MESSAGE(#A " should not equal " #B ". " #__VA_ARGS__))

#define TEST_LESS_THAN(A, B, ...) \
  test_less_than((A), (B), TEST_MESSAGE(#A " should be less than " #B ". " #__VA_ARGS__))

#define TEST_MORE_THAN(A, B, ...) \
  test_more_than((A), (B), TEST_MESSAGE(#A " should be more than " #B ". " #__VA_ARGS__))

#define TEST_APPROX_EQUAL(A, B, TOLERANCE, ...)                               \
  test_approx_equal(                                                          \
    (A),                                                                      \
    (B),                                                                      \
    TOLERANCE,                                                                \
    TEST_MESSAGE(#A " should be within " #TOLERANCE " of " #B ". " #__VA_ARGS__) \
  )

#define TEST_TRUE(A, ...) \
  test_true((A), TEST_MESSAGE(#A " should be true. " #__VA_ARGS__))

#define TEST_FALSE(A, ...) \
  test_false((A), TEST_MESSAGE(#A " should be false. " #__VA_ARGS__))

#define TEST_STATIC(A, ...) \
  static_assert(A, "" #__VA_ARGS__);\
  test_true(true, "" #__VA_ARGS__);


#if UNITCPP_TEST_THROWS_AVAILABLE
#define TEST_THROWS(FUNCTION, EXCEPTION, ...)   \
  test_throws<EXCEPTION>( \
    #FUNCTION " should throw " #EXCEPTION " when given arguments {" #__VA_ARGS__ "}.", \
    FUNCTION, \
    ##__VA_ARGS__ \
  )
#endif // UNITCPP_TEST_THROWS_AVAILABLE

// #define for access to private/protected members.
#define UNITCPP_FRIEND_TEST(GROUP, NAME) \
  friend class test_##GROUP##_##NAME;

//=============================================================================
//----- Class headers, in UnitCpp namespace
//=============================================================================

namespace UnitCpp {

// Class predeclarations
class TestCase;

//=============================================================================
struct TestResult {
  bool pass;
  std::string message;
};

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
  
  std::map<std::string, std::vector<TestCase*> >  m_test_table;
  std::vector<TestCase*> m_failures;
  std::ostream& m_os;
};

//=============================================================================
class TestCase {
public:

  TestCase(std::string group, std::string name);

  virtual void run() = 0;
  
  virtual ~TestCase() = 0;

  void run_harness();
  
  void stop_printing();
  // Stops printing the results untill restarted.
  
  void restart_printing();
  // Restarts printing results.
  
  template <typename U, typename V>
  void test_equal(const U& first, const V& second);

  template <typename U, typename V>
  void test_equal(const U& first, const V& second, std::string message);

  template <typename U, typename V>
  void test_not_equal(const U& first, const V& second);

  template <typename U, typename V>
  void test_not_equal(const U& first, const V& second, std::string message);

  template <typename U, typename V>
  void test_less_than(const U& first, const V& second);

  template <typename U, typename V>
  void test_less_than(const U& first, const V& second, std::string message);

  template <typename U, typename V>
  void test_more_than(const U& first, const V& second);

  template <typename U, typename V>
  void test_more_than(const U& first, const V& second, std::string message);

  template <typename U, typename V, typename W>
  void test_approx_equal(const U& first, const V& second, const W& tolerance);

  template <typename U, typename V, typename W>
  void test_approx_equal(const U& first, const V& second, const W& tolerance, std::string message);

#if UNITCPP_TEST_THROWS_AVAILABLE
  template <typename Texception, typename TFunction, typename... Args >
  void test_throws(std::string message, TFunction func, Args... arguments);
#endif // UNITCPP_TEST_THROWS_AVAILABLE

  template <typename U>
  void test_true(const U& ok);

  template <typename U>
  void test_true(const U& ok, std::string message);

  template <typename U>
  void test_false(const U& not_ok);

  template <typename U>
  void test_false(const U& not_ok, std::string message);

  void display_results(std::ostream& os);

  //----- API for querying information.
  bool passed() const;

  std::string fail_reason() const;

  std::string title() const;
  // Returns "group:name".
  
private:

  std::string m_group;
  std::string m_name;
  bool m_passed;
  bool m_printing;
  
  std::string m_fail_reason;
  std::vector<TestResult> m_results;
};

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

//=============================================================================
//----- Inline source for the classes
//=============================================================================

//=============================================================================
inline UnitCpp::TestCase::TestCase(std::string group, std::string name)
  : m_group(group),
    m_name(name),
    m_passed(true),
    m_printing(true),
    m_fail_reason("")
{
  UnitCpp::TestRegister::test_register().register_test(group, this);
}

//=============================================================================
inline UnitCpp::TestCase::~TestCase()
{
}

//=============================================================================
inline void UnitCpp::TestCase::run_harness()
{
  try {
    run();
  } catch (std::exception& e) {
    // Newing memory after catching an exception, possibly dodgy.
    std::string message =
      std::string("Exception caught, what(): ") + std::string(e.what());
    TestResult result = {false, message};
    m_results.push_back(result);
    m_passed = false;
    m_fail_reason += message + "\n";
  } catch (...) {
    // Newing memory after catching an exception, possibly dodgy.
    std::string message =
      std::string("Unknown exception thrown.");
    TestResult result = {false, message};
    m_results.push_back(result);
    m_passed = false;
    m_fail_reason += message + "\n";
  }
}

//=============================================================================
template <typename U, typename V>
void UnitCpp::TestCase::test_equal(const U& first, const V& second)
{
  test_equal(first, second, "These arguments should be equal");
}

//=============================================================================
template <typename U, typename V>
void UnitCpp::TestCase::test_equal(const U& first, const V& second, std::string message)
{
  test_true(first == second, message);
}

//=============================================================================
template <typename U, typename V>
void UnitCpp::TestCase::test_not_equal(const U& first, const V& second)
{
  test_not_equal(first, second, "These arguments should not be equal");
}

//=============================================================================
template <typename U, typename V>
void UnitCpp::TestCase::test_not_equal(const U& first, const V& second, std::string message)
{
  test_true(first != second, message);
}

//=============================================================================
template <typename U, typename V>
void UnitCpp::TestCase::test_less_than(const U& first, const V& second)
{
  test_less_than(first, second, "Argument 1 should be less than argument 2");
}

//=============================================================================
template <typename U, typename V>
void UnitCpp::TestCase::test_less_than(const U& first, const V& second, std::string message)
{
  test_true(first < second, message);
}

//=============================================================================
template <typename U, typename V>
void UnitCpp::TestCase::test_more_than(const U& first, const V& second)
{
  test_more_than(first, second, "Argument 1 should be more than argument 2");
}

//=============================================================================
template <typename U, typename V>
void UnitCpp::TestCase::test_more_than(const U& first, const V& second, std::string message)
{
  test_true(first > second, message);
}

//=============================================================================
template <typename U, typename V, typename W>
void UnitCpp::TestCase::test_approx_equal(
  const U& first,
  const V& second,
  const W& tolerance
)
{
  test_approx_equal(
    first,
    second,
    tolerance,
    "Argument 1 should be within tolerance of argument 2"
  );
}

//=============================================================================
template <typename U, typename V, typename W>
void UnitCpp::TestCase::test_approx_equal(
  const U& first,
  const V& second,
  const W& tolerance,
  std::string message
)
{
  test_true(
    first - tolerance < second && second < first + tolerance,
    message
  );
}

#if UNITCPP_TEST_THROWS_AVAILABLE
//=============================================================================
template <typename Texception, typename TFunction, typename... Args >
void UnitCpp::TestCase::test_throws(
  std::string message,
  TFunction func,
  Args... arguments
)
{
  bool exception_thrown = false;
  try {
    func(arguments...);
  } catch (Texception) {
    exception_thrown = true;
  }
  test_true(exception_thrown, message);
}
#endif // UNITCPP_TEST_THROWS_AVAILABLE

//=============================================================================
template <typename U>
inline void UnitCpp::TestCase::test_true(const U& ok)
{
  test_true(ok, "Should be true.");
}

//=============================================================================
template <typename U>
inline void UnitCpp::TestCase::test_true(const U& ok, std::string message)
{
  bool passed = ok ? true : false;
  TestResult result = {passed, message};
  // if it's printing or a failure push the result.
  if (m_printing || !passed) {
    m_results.push_back(result);
  }
  if (!passed) {
    m_passed = false;
    m_fail_reason += "  " + message + "\n";
  }
}

//=============================================================================
template <typename U>
inline void UnitCpp::TestCase::test_false(const U& not_ok)
{
  test_false(not_ok, "Should be false.");
}

//=============================================================================
template <typename U>
inline void UnitCpp::TestCase::test_false(const U& not_ok, std::string message)
{
  test_true(!not_ok, message);
}

//=============================================================================
inline void UnitCpp::TestCase::display_results(std::ostream& os)
{
  os << "Test " << title() << "\n\n";
  for (auto it = begin(m_results); it != end(m_results); ++it) {
    TestResult result = *it;
    if (result.pass) {
      os << "Pass: ";
    } else {
      os << "Fail: ";
    }
    os << result.message << "\n";
  }
  os << "\n";
  if (!m_passed) {
    os << m_group << ":" << m_name << " failed.\n";
  }
}

//=============================================================================
inline bool UnitCpp::TestCase::passed() const
{
  return m_passed;
}

//=============================================================================
inline std::string UnitCpp::TestCase::fail_reason() const
{
  return m_fail_reason;
}

//=============================================================================
inline std::string UnitCpp::TestCase::title() const
{
  std::string a_title("\"");
  a_title += m_group + ":" + m_name + "\"";
  return a_title;
}

//=============================================================================
inline void UnitCpp::TestCase::stop_printing()
{
  m_printing = false;
}

//=============================================================================
inline void UnitCpp::TestCase::restart_printing()
{
  m_printing = true;
}

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
  std::vector<TestCase*> tests = m_test_table.at(group_name);
  for (auto it = begin(tests); it != end(tests); ++it) {
    TestCase* test = *it;
    test->run_harness();
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
  for (auto it = begin(m_test_table); it != end(m_test_table); ++it) {
    return_code += run_tests(it->first);
  }
  if (return_code) {
    // there were some failures.
    m_os << "Failures:\n\n";
    for (auto it = begin(m_failures); it != end(m_failures); ++it) {
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
  return m_test_table.find(group_name) != end(m_test_table);
}

//=============================================================================
inline UnitCpp::TestMenu::TestMenu(
  UnitCpp::TestRegister& test_register
)
{
  std::map<std::string, std::vector<TestCase*> >& test_table =
    test_register.m_test_table;
  m_tests.push_back(
    std::make_shared<TestMenu::TestMenuAllTests>(test_register)
  );
  for (
    auto group_it = begin(test_table);
    group_it != end(test_table);
    ++group_it
  ) {
    auto group_item = std::make_shared<TestMenu::TestMenuItemGroup>(
      test_register,
      group_it->first
    );
    m_tests.push_back(group_item);
    for (
      auto test_it = begin(group_it->second);
      test_it != end(group_it->second);
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
  for (auto it = begin(m_tests); it != end(m_tests); ++it) {
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
  m_test_case->run_harness();
  m_test_case->display_results(TestRegister::test_register().os());
  int ret_val = 1;
  if (m_test_case->passed()) {
    ret_val = 0;
  }
  return ret_val;
}

#endif // UnitCpp_H
