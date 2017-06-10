#ifndef INTEGRATOR_HH_
#define INTEGRATOR_HH_


#include "functor.hh"
#include <stdlib.h>

class Integrator
{
public:
	virtual double operator () (Functor &f) = 0;
	virtual void setBounds(const double &l, const double &r) = 0;
	virtual size_t orderOfConvergence() const = 0;
	virtual size_t maxDegree() const  = 0;
	virtual ~Integrator() {}
};


#endif /* INTEGRATOR_HH_ */
