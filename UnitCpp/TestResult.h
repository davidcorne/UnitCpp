//=============================================================================
#ifndef TestResult_H
#define TestResult_H

#include <string>

// <nnn> //=============================================================================
// <nnn> class TestResult {
// <nnn> public:

// <nnn>   TestResult(bool pass, std::string message);
// <nnn>   ~TestResult();

// <nnn>   bool pass() const;

// <nnn>   std::string message() const;
  
// <nnn> private:

// <nnn>   bool m_pass;
// <nnn>   std::string m_message;
// <nnn> };

// <nnn> //=============================================================================
// <nnn> TestResult::TestResult(bool pass, std::string message) 
// <nnn>   : m_pass(pass),
// <nnn>     m_message(message)
// <nnn> {
// <nnn> }

// <nnn> //=============================================================================
// <nnn> TestResult::~TestResult()
// <nnn> {
// <nnn> }

// <nnn> //=============================================================================
// <nnn> std::string TestResult::message() const
// <nnn> {
// <nnn>   return m_message;
// <nnn> }

// <nnn> //=============================================================================
// <nnn> bool TestResult::pass() const
// <nnn> {
// <nnn>   return m_pass;
// <nnn> }

//=============================================================================
struct TestResult {
  bool pass;
  std::string message;
};

#endif
