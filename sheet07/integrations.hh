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

	double operator() (Functor &f, Integrator &integrator, size_t numIntervals, double lowerlimit=0.0, double upperlimit=0.0) override
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

		double result = 0.0;

		double dt = (upperlimit - lowerlimit) / numIntervals; // length of sub-interval

		for (size_t i = 0; i < numIntervals; i++)
		{
			// for each interval, call rule to perform integration

			double a = lowerlimit + dt * i;
			double b = lowerlimit + dt * (i+1);

			integrator.setBounds(a, b);

			result += integrator(f);

		}

		return result;

	}
};

class AdaptiveIntegration : public Integration
{
public:
	AdaptiveIntegration () {}

	double operator() (Functor &f, Integrator &integrator, size_t numIntervals, double lowerlimit=0.0, double upperlimit=0.0) override
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

		return 0.0;

	}
};


#endif /* INTEGRATIONS_HH_ */
