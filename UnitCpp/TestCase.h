//=============================================================================
//
// This is the main class of UnitCpp. All of the tests are derived from
// TestCase. In general you should use the preprocessor macros as they
// give the best information. However you can get more flexiblity using the
// functions directly.
// e.g.
//   TEST_EQUAL("C:/Users", "C:\Users")
// will fail, but
//   test_equal<path>("C:/Users", "C:\Users")
// will pass.

#ifndef UnitCppTestCase_H
#define UnitCppTestCase_H

#include <UnitCpp/TestResult.h>
#include <UnitCpp/Capabilities.h>

#include <list>
#include <iostream>

// Helpful preprocessor macros.

#define UNITCPP_INTERNALS_S(x) #x
#define UNITCPP_INTERNALS_S_(x) UNITCPP_INTERNALS_S(x)

#define TEST_MESSAGE(MESSAGE) \
  "\"" MESSAGE "\" " __FILE__ ":" UNITCPP_INTERNALS_S_(__LINE__)

#define TEST_EQUAL(A, B) \
  test_equal(A, B, TEST_MESSAGE(#A " should equal " #B "."))

#define TEST_NOT_EQUAL(A, B) \
  test_not_equal(A, B, TEST_MESSAGE(#A " should not equal " #B "."))

#define TEST_LESS_THAN(A, B) \
  test_less_than(A, B, TEST_MESSAGE(#A " should be less than " #B "."))

#define TEST_MORE_THAN(A, B) \
  test_more_than(A, B, TEST_MESSAGE(#A " should be more than " #B "."))

#define TEST_APPROX_EQUAL(A, B, TOLERANCE) \
  test_approx_equal(\
    A, \
    B, \
    TOLERANCE, \
    TEST_MESSAGE(#A " should be within " #TOLERANCE " of " #B ".")\
  )

#define TEST_TRUE(A) \
  test_true(A, TEST_MESSAGE(#A " should be true."))

#define TEST_FALSE(A) \
  test_false(A, TEST_MESSAGE(#A " should be false."))

#ifdef UNITCPP_TEST_THROWS_AVAILABLE
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
namespace UnitCpp {
  
//=============================================================================
class TestCase {
public:

  TestCase(std::string group, std::string name);

  virtual void run() = 0;
  
  virtual ~TestCase() = 0;

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
  
  void test_true(bool ok);

  void test_true(bool ok, std::string message);

  void test_false(bool not_ok);

  void test_false(bool not_ok, std::string message);

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
  std::list<TestResult> m_results;
};

}

//----- Source
#include <UnitCpp/TestRegister.h>

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
  } catch (Texception e) {
    exception_thrown = true;
  }
  test_true(exception_thrown, message);
}
#endif // UNITCPP_TEST_THROWS_AVAILABLE

//=============================================================================
inline void UnitCpp::TestCase::test_true(bool ok)
{
  test_true(ok, "Should be true.");
}

//=============================================================================
inline void UnitCpp::TestCase::test_true(bool ok, std::string message)
{
  TestResult result = {ok, message};
  // if it's printing or a failure push the result.
  if (m_printing || !ok) {
    m_results.push_back(result);
  }
  if (!ok) {
    m_passed = false;
    m_fail_reason += "  " + message + "\n";
  }
}

//=============================================================================
inline void UnitCpp::TestCase::test_false(bool not_ok)
{
  test_false(not_ok, "Should be false.");
}

//=============================================================================
inline void UnitCpp::TestCase::test_false(bool not_ok, std::string message)
{
  test_true(!not_ok, message);
}

//=============================================================================
inline void UnitCpp::TestCase::display_results(std::ostream& os)
{
  os << "Test " << title() << "\n\n";
  for (auto it = std::begin(m_results); it != std::end(m_results); ++it) {
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

#endif
