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
#include <stdlib.h>
#include <iostream>
#include <string>

class EquidistantIntegration : public Integration
{
public:
	EquidistantIntegration() {}

	double operator() (Integrator &integrator, Functor &f, double lowerlimit=0.0, double upperlimit=0.0) override
	{

		TestFunctor* tf = dynamic_cast<TestFunctor*> (&f);

		if (tf != nullptr)
		{
			(*tf).integrationInterval(lowerlimit, upperlimit);
			std::cout << "Lower limit is " << lowerlimit << ", Upper limit is " << upperlimit << std::endl;
		}
		else
		{
			if (lowerlimit == upperlimit)
			{
				std::cout << "Error: no interval defined." << std::endl;
				exit(0);
			}
			else
			{
				std::cout << "Lower limit is " << lowerlimit << ", Upper limit is " << upperlimit << std::endl;
			}

		}

		double df = f(1);
		//double dtf = (*tf)[1];

		std::cout << "f() = " << df << std::endl;
		//std::cout << "f[] = " << dtf << std::endl;

		/*
		double h = (upperlimit - lowerlimit) / N;

		for (size_t i = 0; i < (N-1); i++)
		{
			// for each interval, call rules to perform integration
			// the a = lowerlimit + i * h, b = lowerlimit + (i+1)h, N = 1 by default


		}
		*/
		double result = 0.0;

		return result;
	}
};



#endif /* INTEGRATIONS_HH_ */
