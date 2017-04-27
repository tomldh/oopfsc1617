#ifndef RATIONAL_H_
#define RATIONAL_H_

#include "Utility.h"

class Rational
{

public:
	// constructor
	Rational();
	Rational(int wholeNum);
	Rational(int numer, int denom);
	~Rational();

	// data retrieval
	int numerator() const;
	int denominator() const;

	// operator overloading
	Rational& operator+=(const Rational &rhs);
	Rational& operator-=(const Rational &rhs);
	Rational& operator*=(const Rational &rhs);
	Rational& operator/=(const Rational &rhs);
	bool operator==(const Rational &rhs);

private:
	// variables
	int fraction[2];

};

//free operators
Rational operator+(const Rational &lhs, const Rational &rhs);
Rational operator-(const Rational &lhs, const Rational &rhs);
Rational operator*(const Rational &lhs, const Rational &rhs);
Rational operator/(const Rational &lhs, const Rational &rhs);


#endif /* RATIONAL_H_ */
