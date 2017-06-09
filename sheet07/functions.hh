/*
 * functions.hh
 *
 *  Created on: 8 Jun 2017
 *      Author: fighterlin
 */

#ifndef FUNCTIONS_HH_
#define FUNCTIONS_HH_

#include "functor.hh"
#include <cmath>

// realization of function a * x^2 + b * x + c
class Quadratic : public Functor
{
public:
	Quadratic (double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

	double operator () (double t) const override
	{
		return (a * t * t + b * t + c);
	}

	double operator [] (double t) const override
	{
		// a * x ^ 3 / 3 + b * x ^ 2 / 2 + c * x

		return (a * pow(t, 3) / 3 + b * pow(t, 2) / 2 + c * t);
	}

protected:
	double a, b, c; // coefficients

};

// realization of function (a * t + b) / PI * sin(a * t + b)
class XPiSine : public Functor
{
public:
	XPiSine (double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

	double operator () (double t) const override
	{
		double x = a * t * t + b * t + c;

		return (x) / M_PI * sin(x);
	}

	double operator [] (double t) const override
	{
		double x = a * t * t + b * t + c;

		//return (-x * cos(x) + sin(x)) / M_PI;;

		return (t);
	}

private:
	double a, b, c;
};

/*
class TestFunction : public XPiSine, public Quadratic
{
public:
	TestFunction(double a_, double b_, double c_, double lb_, double ub_)
		: XPiSine(a_, b_, c_), Quadratic(a_, b_, c_), lb(lb_), ub(ub_) {}


	double operator () (double t) override
	{
		return -1.0;
	}

	double operator [] (double t) override
	{
		return -1.0;
	}


	void integrationInterval(double& l, double& r) const
	{
		l = lb;
		r = ub;
	}

	double exactIntegral() const
	{
		//return ((*this)[ub] - (*this)[lb]);
		return 0.0;
	}

private:
	double lb, ub;
};

*/


class TestXPiSine : public XPiSine, public TestFunctor
{

public:
	TestXPiSine(double a_, double b_, double c_, double lb_, double ub_) : XPiSine(a_, b_, c_), lb(lb_), ub(ub_) {}

	void integrationInterval(double& l, double& r) const override
	{
		l = lb;
		r = ub;
	}

	double exactIntegral() const override
	{
		// -x * cos(x) + sin(x)
		return (XPiSine::operator[](ub) - XPiSine::operator[](lb));

		//return 0.0;
	}

private:
	double lb, ub;
};


class TestQuadratic : public Quadratic, public TestFunctor
{
public:
	TestQuadratic (double a_, double b_, double c_, double lb_, double ub_) : Quadratic(a_, b_, c_), lb(lb_), ub(ub_) {}

	void integrationInterval(double& l, double& r) const override
	{
		l = lb;
		r = ub;
	}

	double exactIntegral() const override
	{
		// a * x ^ 3 / 3 + b * x ^ 2 / 2 + c * x
		double diff = ub - lb;

		return (a * pow(diff, 3) / 3 + b * pow(diff, 2) / 2 + c * diff);
	}

private:
	double lb, ub;

};


#endif /* FUNCTIONS_HH_ */
