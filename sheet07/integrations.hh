/*
 * integrations.hh
 *
 *  Created on: 8 Jun 2017
 *      Author: fighterlin
 */

#ifndef INTEGRATIONS_HH_
#define INTEGRATIONS_HH_

#include "integration.hh"

class EquidistantIntegration : public Integration
{
public:
	EquidistantIntegration() {}

	double operator() (Integrator &integrator_, Functor &f) override
	{

		double N = 10; // number of intervals
		double lowerlimit = 0.0, upperlimit = 0.0;

		double h = (upperlimit - lowerlimit) / N;

		for (size_t i = 0; i < (N-1); i++)
		{
			// for each interval, call rules to perform integration
			// the a = lowerlimit + i * h, b = lowerlimit + (i+1)h, N = 1 by default


		}

		double result = 0.0;

		return result;
	}
};



#endif /* INTEGRATIONS_HH_ */
