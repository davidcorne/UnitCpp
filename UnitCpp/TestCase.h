//=============================================================================
#ifndef TestCase_H
#define TestCase_H

#include <UnitCpp/TestResult.h>

#include <list>
#include <iostream>

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
void TestCase::test_equal(const U& first, const V& second, std::string message)
{
  test_true(first == second, message);
}

//=============================================================================
template <typename U, typename V>
void TestCase::test_less_than(const U& first, const V& second, std::string message)
{
  test_true(first < second, message);
}

//=============================================================================
template <typename U, typename V>
void TestCase::test_less_than(const U& first, const V& second)
{
  test_less_than(first, second, "Argument 1 should be less than argument 2");
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
