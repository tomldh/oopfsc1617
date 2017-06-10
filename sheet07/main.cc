#include "integrations.hh"
#include "functions.hh"
#include "trapezoidRule.hh"
#include "simpsonRule.hh"
#include <cmath>
#include <iostream>

double calculateEOC(Functor& f, Integrator& integrator_, Integration& integration_, size_t N)
{
	TestFunctor* tf = dynamic_cast<TestFunctor*> (&f);

	double exact = (*tf).exactIntegral();
	double resultN = integration_(f, integrator_, N);
	double result2N = integration_(f, integrator_, 2*N);

	std::cout << "Exact: " << exact << ", result of N integration: " << resultN << ", result of 2N integration: " << result2N << std::endl;

	double errorN = std::abs(exact - resultN);
	double error2N = std::abs(exact - result2N);

	if (errorN == 0 || error2N == 0)
	{
		std::cout << "Exact approximation found!" << std::endl;
		exit(0);
	}

	std::cout << "errorN: " << errorN << ", error2N : " << error2N << std::endl;
	double eoc = log(errorN / error2N) / log(2);

	// depending on the two intervals, the order may not be 2???
	std::cout << "Expected: " << integrator_.orderOfConvergence() << ", Observed: " << eoc << std::endl;

	if ((unsigned int)eoc == integrator_.orderOfConvergence())
	{
		std::cout << "Expected matches observed oder of convergence!" << std::endl;
	}

	return eoc;
}

int main()
{
	EquidistantIntegration eInteg;

	// Quadrature rules
	TrapezoidRule trapezoid;
	SimpsonRule simpson;

	// Test function 1 - 2*t^2+5
	TestQuadratic quadFunc(2.0, 0.0, 5.0, -3.0, 13.0);
	//Quadratic quadFunc(2.0, 0.0, 5.0);

	size_t N = 10;

	std::cout << "Result of integration: " << eInteg(quadFunc, simpson, N) << std::endl;
	std::cout << "Exact integration: " << quadFunc.exactIntegral() << std::endl;

	std::cout << "EOC of trapezoid rule: " << calculateEOC(quadFunc, simpson, eInteg, N) << std::endl;

	std::cout << std::endl;
	std::cout << "Function 2 test:" << std::endl;

	// Test function 2 - t/PI*sin(t)
	TestXPiSine xpisineFunc(0.0, 1.0, 0.0, 0.0, 2*M_PI);

	std::cout << "Result of integration: " << eInteg(xpisineFunc, simpson, N) << std::endl;
	std::cout << "Exact integration: " << xpisineFunc.exactIntegral() << std::endl;

	std::cout << "EOC of trapezoid rule: " << calculateEOC(xpisineFunc, simpson, eInteg, N) << std::endl;





}
