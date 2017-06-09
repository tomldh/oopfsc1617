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
	SimpsonRule (double A_, double B_, size_t N_) : A(A_), B(B_), N(N_) {}

	double operator () (Functor &f) override
	{
		double dt = (B - A) / N; // sub-interval length

		double result = 0.0;

		for (size_t i = 0; i < N-1; i++)
		{
			double a = A + dt * i;
			double b = A + dt * (i+1);

			result += ((f(a) + 4 * f(a/2 + b/2) + f(b)) * dt / 6);

		}

		return result;
	}

	void setBounds(const double &l, const double &r)
	{

	}
	void setNumOfIntervals(const size_t &n)
	{

	}

private:
	double A, B; //lower bound, upper bound
	size_t N; //n subintervals

};


#endif /* SIMPSONRULE_HH_ */
