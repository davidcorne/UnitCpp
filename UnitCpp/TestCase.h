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

#ifndef TestCase_H
#define TestCase_H

#include <UnitCpp/TestResult.h>

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

//=============================================================================
class TestCase {
public:

  TestCase(std::string group, std::string name);

  virtual void run() = 0;
  
  virtual ~TestCase();

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

  void test_true(bool ok);

  void test_true(bool ok, std::string message);

  void test_false(bool not_ok);

  void test_false(bool not_ok, std::string message);

  void display_results(std::ostream& os);

  bool passed() const;
  
private:

  std::string m_group;
  std::string m_name;
  bool m_passed;
  std::list<TestResult> m_results;
};

//=============================================================================
inline TestCase::TestCase(std::string group, std::string name)
  : m_group(group),
    m_name(name),
    m_passed(true)
{
  TestRegister::test_register().register_test(group, this);
}

//=============================================================================
inline TestCase::~TestCase()
{
}

//=============================================================================
template <typename U, typename V>
void TestCase::test_equal(const U& first, const V& second)
{
  test_equal(first, second, "These arguments should be equal");
}

//=============================================================================
template <typename U, typename V>
void TestCase::test_equal(const U& first, const V& second, std::string message)
{
  test_true(first == second, message);
}

//=============================================================================
template <typename U, typename V>
void TestCase::test_not_equal(const U& first, const V& second)
{
  test_not_equal(first, second, "These arguments should not be equal");
}

//=============================================================================
template <typename U, typename V>
void TestCase::test_not_equal(const U& first, const V& second, std::string message)
{
  test_true(first != second, message);
}

//=============================================================================
template <typename U, typename V>
void TestCase::test_less_than(const U& first, const V& second)
{
  test_less_than(first, second, "Argument 1 should be less than argument 2");
}

//=============================================================================
template <typename U, typename V>
void TestCase::test_less_than(const U& first, const V& second, std::string message)
{
  test_true(first < second, message);
}

//=============================================================================
template <typename U, typename V>
void TestCase::test_more_than(const U& first, const V& second)
{
  test_more_than(first, second, "Argument 1 should be more than argument 2");
}

//=============================================================================
template <typename U, typename V>
void TestCase::test_more_than(const U& first, const V& second, std::string message)
{
  test_true(first > second, message);
}

//=============================================================================
template <typename U, typename V, typename W>
void TestCase::test_approx_equal(
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
void TestCase::test_approx_equal(
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

//=============================================================================
inline void TestCase::test_true(bool ok)
{
  test_true(ok, "Should be true.");
}

//=============================================================================
inline void TestCase::test_true(bool ok, std::string message)
{
  m_results.push_back({ok, message});
  if (!ok) {
    m_passed = false;
  }
}

//=============================================================================
inline void TestCase::test_false(bool not_ok)
{
  test_false(not_ok, "Should be false.");
}

//=============================================================================
inline void TestCase::test_false(bool not_ok, std::string message)
{
  test_true(!not_ok, message);
}

//=============================================================================
inline void TestCase::display_results(std::ostream& os)
{
  os << "Test \"" << m_group << ":" << m_name << "\"\n\n";
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
inline bool TestCase::passed() const
{
  return m_passed;
}
#endif
