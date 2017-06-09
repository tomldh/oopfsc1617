#include "integrations.hh"
#include "functions.hh"
#include "trapezoidRule.hh"
#include "simpsonRule.hh"
#include <cmath>
#include <iostream>

int main()
{
	EquidistantIntegration eInteg;

	// Quadrature rules
	TrapezoidRule trapezoid;

	// Test function 1 - 2*t^2+5
	//TestFunction func1(2.0, 0.0, 5.0, -3.0, 13.0);

	TestQuadratic quadFunc(2.0, 0.0, 5.0, -3.0, 13.0);
	//Quadratic quadFunc(2.0, 0.0, 5.0);

	//Quadratic* quadFunc = dynamic_cast<Quadratic*> (&func1);

	if (&quadFunc == nullptr)
	{
		std::cout << "Error: cannot cast test function to quadratic function!" << std::endl;
	}
	else
	{
		eInteg(trapezoid, quadFunc, -3, 23);
	}


	// Test function 2 - t/PI*sin(t)
	//TestFunction func2(0.0, 1.0, 0.0, 0.0, 2*M_PI);





}
