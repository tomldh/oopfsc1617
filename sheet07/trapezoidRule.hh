

#ifndef TRAPEZOIDRULE_HH_
#define TRAPEZOIDRULE_HH_

#include "integrator.hh"
#include <stdlib.h>

class TrapezoidRule : public Integrator
{

public:
	TrapezoidRule() : A(0.0), B(0.0), N(0.0) {}

	TrapezoidRule(double A_, double B_, size_t N_) : A(A_), B(B_), N(N_) {}

	double operator () (Functor &f) override
	{
		double dt = (B - A) / N; // sub-interval length

		double result = 0.0;

		for (size_t i = 0; i < (N-1); i++)
		{
			double a = A + dt * i;
			double b = A + dt * (i+1);

			result += ((f(a) + f(b)) * dt / 2);

		}

		return result;
	}

private:
	double A, B; //lower bound, upper bound
	size_t N; //number of sub-intervals

};



#endif /* TRAPEZOIDRULE_HH_ */
