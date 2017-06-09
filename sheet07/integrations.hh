/*
 * integrations.hh
 *
 *  Created on: 8 Jun 2017
 *      Author: fighterlin
 */

#ifndef INTEGRATIONS_HH_
#define INTEGRATIONS_HH_

#include "integration.hh"
#include "functions.hh"

#include <iostream>
#include <string>

class EquidistantIntegration : public Integration
{
public:
	EquidistantIntegration() {}

	double operator() (Integrator &integrator, Functor &f, size_t numIntervals, double lowerlimit=0.0, double upperlimit=0.0) override
	{

		TestFunctor* tf = dynamic_cast<TestFunctor*> (&f);

		// Testing function
		if (tf != nullptr)
		{
			(*tf).integrationInterval(lowerlimit, upperlimit);
			std::cout << "Lower limit is " << lowerlimit << ", Upper limit is " << upperlimit << std::endl;
		}

		if (lowerlimit > upperlimit)
		{
			std::cout << "Error: no valid interval defined for integration!" << std::endl;
		}

		integrator.setBounds(lowerlimit, upperlimit);
		integrator.setNumOfIntervals(numIntervals);

		return integrator(f);

		/*
		double h = (upperlimit - lowerlimit) / N; // length of sub-interval

		for (size_t i = 0; i < (N-1); i++)
		{
			// for each interval, call rules to perform integration
			// the a = lowerlimit + i * h, b = lowerlimit + (i+1)h, N = 1 by default

		}

		double result = 0.0;

		return result;
		*/
	}
};



#endif /* INTEGRATIONS_HH_ */
