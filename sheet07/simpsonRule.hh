/*
 * simpsonRule.hh
 *
 *  Created on: 8 Jun 2017
 *      Author: fighterlin
 */

#ifndef SIMPSONRULE_HH_
#define SIMPSONRULE_HH_

#include "integrator.hh"
#include <stdlib.h>

class SimpsonRule : public Integrator
{

public:
	SimpsonRule () : a(0.0), b(0.0) {}
	SimpsonRule (double a_, double b_) : a(a_), b(b_) {}

	double operator () (Functor &f) override
	{
		return ((f(a) + 4 * f(a/2 + b/2) + f(b)) * (b - a) / 6);
	}

	void setBounds(const double &l, const double &r) override
	{
		a = l;
		b = r;
	}

	size_t orderOfConvergence() const override
	{
		return 4;
	}

	size_t maxDegree() const override
	{
		return 2;
	}

private:
	double a, b; //lower bound, upper bound

};


#endif /* SIMPSONRULE_HH_ */
