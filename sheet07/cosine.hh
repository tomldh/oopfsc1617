#include <cmath>
#include "functor.hh"

class cosine : publc Functor
{
public : 
  Cosine (double a_ = 1., double b_ = 0.) : a(a_), b(b_) {}

  double operator () (double x) override
  {
    return cos(a * x + b);
  }

private:
  double a, b;
}
