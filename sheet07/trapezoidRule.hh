

#ifndef TRAPEZOIDRULE_HH_
#define TRAPEZOIDRULE_HH_

#include "integrator.hh"
#include <stdlib.h>

class TrapezoidRule : public Integrator
{

public:
	TrapezoidRule() : a(0.0), b(0.0) {}

	TrapezoidRule(double a_, double b_) : a(a_), b(b_) {}

	double operator () (Functor &f) override
	{
		return (f(a) + f(b)) * (b - a) / 2;
	}

	void setBounds(const double &l, const double &r) override
	{
		a = l;
		b = r;
	}

	size_t orderOfConvergence() const override
	{
		return 2;
	}

	size_t maxDegree() const override
	{
		return 1;
	}

private:
	double a, b; //lower bound, upper bound

};



#endif /* TRAPEZOIDRULE_HH_ */
