
#ifndef FUNCTOR_HH_
#define FUNCTOR_HH_

class Functor
{
public:
	virtual double operator () (double t) const = 0;
	virtual double operator [] (double t) const = 0;
	virtual ~Functor () {}
};

class TestFunctor
{
public :
	virtual void integrationInterval(double& l, double& r) const = 0;
	virtual double exactIntegral() const = 0;
	virtual ~TestFunctor() {}
};


#endif /* FUNCTOR_HH_ */
