//=============================================================================
// Internal macro for working out if variadic templates are supported by the
// compiler or not.

#ifndef VariadicTemplatesSupported_H
#define VariadicTemplatesSupported_H

#define UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED 0

// For using visual studio. Support is from Visual Studio 2013.
#ifdef _MSC_VER
#if _MSC_VER >= 1800 // Visual Studio 2013's internal code.
#undef UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED
#define UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED 1
#endif // _MSC_VER >= 1800
#endif // ifdef _MSC_VER

// For g++ variadic templates supported in 4.3 or later.
#ifdef __GNUC__
// if it's 4.X
#if __GNUC__ == 4
#if __GNUC_MINOR__ >= 3
#undef UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED
#define UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED 1
#endif // __GNUC_MINOR__ >= 3
#endif // __GNUC__ == 4

// later versions than 4.
#if __GNUC__ > 4
#undef UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED
#define UNITCPP_INTERNALS_VARIADIC_TEMPLATES_SUPPORTED 1
#endif // __GNUC__ > 4

#endif // __GNUC__

#endif // VariadicTemplatesSupported_H
