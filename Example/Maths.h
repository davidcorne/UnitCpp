//=============================================================================
// This is just an example class to show how the UnitCpp works.

#ifndef Maths_H
#define Maths_H

//=============================================================================
namespace Maths {

  class OutOfRangeException{};
  
  double sqrt(double number);
  // Returns the square root of the number.
  // if number is <= 0, an OutOfRangeException will be thrown.
  
  bool is_square(int number);
  // Returns if the number is a perfect square. i.e. the square of an integer.

};

#include <math.h>

//=============================================================================
double Maths::sqrt(double number)
{
  if (number < 0) {
    throw OutOfRangeException();
  }
  return ::sqrt(number);
}

//=============================================================================
bool Maths::is_square(int number)
{
  double root = sqrt(static_cast<double>(number));
  int int_root = static_cast<int>(root);
  return (int_root * int_root) == number;
}

#endif
