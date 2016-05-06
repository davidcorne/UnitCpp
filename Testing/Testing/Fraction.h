//=============================================================================
// A compile time fraction class. Nothing fancy.

#ifndef Fraction_H
#define Fraction_H

//=============================================================================
template <int N, int D>
struct Fraction {
 static const int Numerator = N;
 static const int Denominator = D;
};

#endif
