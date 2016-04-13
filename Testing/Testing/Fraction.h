//=============================================================================
// A compile time fraction class. Nothing fancy.

#ifndef Fraction_H
#define Fraction_H

//=============================================================================
template <int N, int D>
struct Fraction {
 static const int Numerator;
 static const int Denominator;
};

template <int N, int D>
const int Fraction<N, D>::Numerator = N;

template <int N, int D>
const int Fraction<N, D>::Denominator = D;
#endif
