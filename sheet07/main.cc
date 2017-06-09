#include "integrations.hh"
#include "functions.hh"
#include "trapezoidRule.hh"
#include "simpsonRule.hh"
#include <cmath>
#include <iostream>

double calculateEOC(Functor& f, Integrator& integrator_, Integration& integration_)
{
	TestFunctor* tf = dynamic_cast<TestFunctor*> (&f);

	size_t N = 100;

	double errorN = (*tf).exactIntegral() - integration_(integrator_, f, N);
	double error2N = (*tf).exactIntegral() - integration_(integrator_, f, 2*N);

	std::cout << "errorN: " << errorN << ", error2N : " << error2N << std::endl;
	double eoc = log(errorN/error2N) / log(2);

	return eoc;
}

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
		std::cout << "Result of integration: " << eInteg(trapezoid, quadFunc, 1000, -3, 23) << std::endl;
		std::cout << "Exact integration: " << quadFunc.exactIntegral() << std::endl;
	}

	std::cout << "EOC of trapezoid rule: " << calculateEOC(quadFunc, trapezoid, eInteg) << std::endl;

	// Test function 2 - t/PI*sin(t)
	//TestFunction func2(0.0, 1.0, 0.0, 0.0, 2*M_PI);





}
