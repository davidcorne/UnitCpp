//=============================================================================
// This is a collection of macros which guide what UnitCpp can do, depending
// on compiler capability. At the moment the only feature which may not
// be available is TEST_THROWS.

#ifndef UnitCppCapabilities_H
#define UnitCppCapabilities_H

#include <UnitCpp/Internal/VariadicTemplatesSupported.h>

#define UNITCPP_TEST_THROWS_AVAILABLE UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED


#endif
