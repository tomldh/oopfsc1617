/*
 * Rational.cc
 *
 *  Created on: 23 Apr 2017
 *      Author: fighterlin
 */

#include "Rational.h"

Rational::Rational()
{
	fraction[0] = 1;
	fraction[1] = 1;
}

Rational::Rational(int wholeNum)
{
	fraction[0] = wholeNum;
	fraction[1] = 1;
}

Rational::Rational(int nr, int dr)
{
	//check for denominator error
	if (dr == 0)
	{
		nr = 0;
		dr = 1;
	}

	// ensure denominator is always positive
	if (dr < 0)
	{
		dr = -dr;
		nr = -nr;
	}

	int m_gcd = gcd(iabs(nr), iabs(dr));

	fraction[0] = nr / m_gcd;
	fraction[1] = dr / m_gcd;

}

Rational::~Rational()
{

}

int Rational::numerator() const
{
	return fraction[0];
}

int Rational::denominator() const
{
	return fraction[1];
}

Rational& Rational::operator+= (const Rational &rhs)
{

	fraction[0] = fraction[0] * rhs.denominator() + rhs.numerator() * fraction[1];
	fraction[1] = fraction[1] * rhs.denominator();

	int m_gcd = gcd(iabs(fraction[0]), iabs(fraction[1]));

	fraction[0] /= m_gcd;
	fraction[1] /= m_gcd;

	return *this;
}

Rational& Rational::operator-= (const Rational &rhs)
{

	fraction[0] = fraction[0] * rhs.denominator() - rhs.numerator() * fraction[1];
	fraction[1] = fraction[1] * rhs.denominator();

	int m_gcd = gcd(iabs(fraction[0]), iabs(fraction[1]));

	fraction[0] /= m_gcd;
	fraction[1] /= m_gcd;

	return *this;
}

Rational& Rational::operator*= (const Rational &rhs)
{

	fraction[0] = fraction[0] * rhs.numerator();
	fraction[1] = fraction[1] * rhs.denominator();

	int m_gcd = gcd(iabs(fraction[0]), iabs(fraction[1]));

	fraction[0] /= m_gcd;
	fraction[1] /= m_gcd;

	return *this;
}

Rational& Rational::operator/= (const Rational &rhs)
{

	fraction[0] = fraction[0] * rhs.denominator();
	fraction[1] = fraction[1] * rhs.numerator();

	int m_gcd = gcd(iabs(fraction[0]), iabs(fraction[1]));

	fraction[0] /= m_gcd;
	fraction[1] /= m_gcd;

	return *this;
}

bool Rational::operator== (const Rational &rhs)
{

	if (fraction[0]==rhs.numerator() && fraction[1] == rhs.denominator())
		return true;
	else
		return false;
}

Rational operator+ (const Rational &lhs, const Rational &rhs)
{
	Rational sum = lhs;
	sum += rhs;
	return sum;
}

Rational operator- (const Rational &lhs, const Rational &rhs)
{
	Rational sum = lhs;
	sum -= rhs;
	return sum;
}

Rational operator* (const Rational &lhs, const Rational &rhs)
{
	Rational sum = lhs;
	sum *= rhs;
	return sum;
}

Rational operator/ (const Rational &lhs, const Rational &rhs)
{
	Rational sum = lhs;
	sum /= rhs;
	return sum;
}







