#ifndef INTEGRATOR_HH_
#define INTEGRATOR_HH_


#include "functor.hh"

class Integrator
{
public:
	virtual double operator () (Functor &f) = 0;
	virtual ~Integrator() {}
};


#endif /* INTEGRATOR_HH_ */
