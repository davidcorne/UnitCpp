//=============================================================================
// Copyright (c) 2015 David Corne
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// Internal macro for working out if variadic templates are supported by the
// compiler or not.

#ifndef UnitCppVariadicTemplatesSupported_H
#define UnitCppVariadicTemplatesSupported_H

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
