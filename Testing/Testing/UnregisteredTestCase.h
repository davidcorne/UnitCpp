//=============================================================================
#include <UnitCpp/TestCase.h>

#include <functional>

//=============================================================================
namespace UnitCpp {

//=============================================================================
class UnregisteredTestCase : public TestCase {
public:

  UnregisteredTestCase(std::function<void(TestCase&)> test_function);

  virtual ~UnregisteredTestCase();

  virtual void run() override;

private:

  std::function<void(TestCase&)> m_test_function;
};

}
