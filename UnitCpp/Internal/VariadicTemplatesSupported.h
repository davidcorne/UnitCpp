//=============================================================================
// Internal macro for working out if variadic templates are supported by the
// compiler or not.

#ifndef VariadicTemplatesSupported_H
#define VariadicTemplatesSupported_H

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

#ifdef __clang__
#define UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED __has_feature(cxx_variadic_templates)
#endif // ifdef __clang__

#ifndef UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED
#define UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED 0
#endif // ifndef UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED

#endif // ifndef VariadicTemplatesSupported_H
