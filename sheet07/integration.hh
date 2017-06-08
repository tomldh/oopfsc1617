/*
 * Integration.hh
 *
 *  Created on: 8 Jun 2017
 *      Author: fighterlin
 */

#ifndef INTEGRATION_HH_
#define INTEGRATION_HH_

#include "integrator.hh"
#include "functor.hh"

class Integration
{
public:
	virtual double operator () (Integrator &integrator_, Functor &f) = 0;
	virtual ~Integration() {}
};



#endif /* INTEGRATION_HH_ */
