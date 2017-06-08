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

// realization of function a * x^2 + b
class Quadratic : public Functor
{
public:
	Quadratic (double a_, double b_) : a(a_), b(b_), lb(0.0), ub(0.0) {}

	double operator () (double t) override
	{
		return (a * t * t + b);
	}

	void integrationInterval(double& l, double& r)override
	{
		lb = l;
		ub = r;
	}

	double exactIntegral() const override
	{
		// a * x ^ 3 / 3 + b * x
		return (a * pow((ub - lb), 3) / 3 + b * (ub - lb));
	}


private:
	double a, b;
	double lb, ub; // lower bound, upper bound

};

// realization of function sin(a * x + b)
class Sine : public Functor
{
public:
	Sine (double a_, double b_) : a(a_), b(b_) , lb(0.0), ub(0.0){}

	double operator () (double t) override
	{
		return sin(a * t + b);
	}

	void integrationInterval(double& l, double& r) override
	{
		lb = l;
		ub = r;
	}

	double exactIntegral() const override
	{
		return 0.0;
	}

private:
	double a, b;
	double lb, ub; // lower bound, upper bound
};

// realization of function t / PI * sin(a * x + b)
//FIXME: inherit from Sine?
class XSine : public Functor
{
public:
	XSine (double a_, double b_) : a(a_), b(b_), lb(0.0), ub(0.0) {}

	double operator () (double t) override
	{
		return t / M_PI * sin(a * t + b);
	}

	void integrationInterval(double& l, double& r) override
	{
		lb = l;
		ub = r;
	}

	double exactIntegral() const override
	{
		return 0.0;
	}

private:
	double a, b;
	double lb, ub; // lower bound, upper bound
};


#endif /* FUNCTIONS_HH_ */
