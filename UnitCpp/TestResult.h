//=============================================================================
#ifndef UnitCppTestResult_H
#define UnitCppTestResult_H

#include <string>

//=============================================================================
namespace UnitCpp {

//=============================================================================
struct TestResult {
  bool pass;
  std::string message;
};
  
}

#endif
