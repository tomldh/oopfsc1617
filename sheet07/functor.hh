
#ifndef FUNCTOR_HH_
#define FUNCTOR_HH_

class Functor
{
public:
	virtual double operator () (double t) = 0;
	virtual void integrationInterval(double& l, double& r) = 0; // FIXME: should this go to inheritance of a specific function instead?
	virtual double exactIntegral() const = 0;
	virtual ~Functor () {}
};


#endif /* FUNCTOR_HH_ */
