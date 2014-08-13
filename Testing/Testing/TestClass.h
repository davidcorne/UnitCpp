//=============================================================================

#ifndef TestClass_H
#define TestClass_H

#include <UnitCpp/Test.h>

//=============================================================================
class TestClass {
public:

  TestClass(int i);

  ~TestClass();
  
private:

  TestClass(const TestClass& other);
  TestClass& operator=(const TestClass& other);
  // Prohibited copying.

  void double_value();
  
  int m_i;
};

#endif
