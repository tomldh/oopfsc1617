#ifndef _FUNCTOR_HH_
#define _FUNCTOR_HH_

class Functor
{
public:
  virtual double operator () (double x) = 0;
  virtual ~Functor () {}
}

#endif
