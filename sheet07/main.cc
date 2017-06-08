#include "integrations.hh"
#include "functions.hh"
#include "trapezoidRule.hh"
#include "simpsonRule.hh"

int main()
{
	double upperLimit = 0.0, lowerLimit = 0.0;

	// Test function 1
	Quadratic qfunc(2.0, 5.0); //2*t^2+5
	lowerLimit = -3.0;
	upperLimit = 13.0;
	qfunc.integrationInterval(lowerLimit, upperLimit);

	// Quadrature rules
	TrapezoidRule trapezoid;

	EquidistantIntegration eInteg;
	eInteg(trapezoid, qfunc);


	// Test function 2
	XSine xsine(1.0, 0.0); //t/PI*sin(t)





}
