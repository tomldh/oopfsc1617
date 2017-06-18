#include "matrix.h"
#include <iostream>
#include <complex>
#include "rational.hh"

typedef std::complex<double> complex;

int main()
{
	/*** DOUBLE ***/
	std::cout << "Testing data type DOUBLE:" << std::endl;
	std::cout << "-------------------------" << std::endl;
	// define matrix
    Matrix<double> A(4,6,0.);
    for (int i = 0; i < A.rows(); ++i)  
        A[i][i] = 2.;
    for (int i=0; i < A.rows()-1; ++i) 
        A[i+1][i] = A[i][i+1] = -1.;
    Matrix<double> B(6,4,0.);
    for (int i = 0; i <B.cols(); ++i)  
        B[i][i] = 2.;
    for (int i = 0; i < B.cols()-1; ++i) 
        B[i+1][i] = B[i][i+1] = -1.;
    // print matrix
    A.print();
    B.print();


    Matrix<double> C(A);
    A = 2 * C;
    A.print();
    A = C * 2.;
    A.print();
    A = C + A;
    A.print();
    const Matrix<double> D(A);
    std::cout << "Element 1,1 of D is " << D(1,1) << std::endl;
    std::cout << std::endl;
    A.resize(5,5,0.);
    for (int i = 0; i < A.rows(); ++i)  
        A(i,i) = 2.;
    for (int i = 0; i < A.rows()-1; ++i) 
        A(i+1,i) = A(i,i+1) = -1.;
    // define vector b
    std::vector<double> b(5);
    b[0] = b[4] = 5.;
    b[1] = b[3] = -4.;
    b[2] = 4.;
    std::vector<double>x = A * b;
    std::cout << "A*b = ( ";
    for (size_t i = 0; i < x.size(); ++i)
        std::cout << x[i] << "  ";
    std::cout << ")" << std::endl;
    std::cout << std::endl;
    // solve
    x = A.solve(b);
    A.print();
    std::cout << "The solution with the ordinary Gauss Elimination is: ( ";
    for (size_t i = 0; i < x.size(); ++i)
        std::cout << x[i] << "  ";
    std::cout << ")" << std::endl;



    /*** FLOAT ***/
    std::cout << "Testing data type FLOAT:" << std::endl;
    std::cout << "-------------------------" << std::endl;
    // define matrix
    Matrix<float> fA(4,6,0.);
	for (int i = 0; i < fA.rows(); ++i)
		fA[i][i] = 2.;
	for (int i=0; i < fA.rows()-1; ++i)
		fA[i+1][i] = fA[i][i+1] = -1.;
	// print matrix
	fA.print();


	/*** INTEGER ***/
	std::cout << "Testing data type INTEGER:" << std::endl;
	std::cout << "-------------------------" << std::endl;
	// define matrix
	Matrix<int> iA(4,6,0);
	for (int i = 0; i < iA.rows(); ++i)
		iA[i][i] = 2;
	for (int i=0; i < iA.rows()-1; ++i)
		iA[i+1][i] = iA[i][i+1] = -1;
	// print matrix
	iA.print();



	/*** COMPLEX ***/
	std::cout << "Testing data type COMPLEX:" << std::endl;
	std::cout << "-------------------------" << std::endl;
    // define matrix
	Matrix<complex> cA(4,6,complex(0., 0.));
	for (int i = 0; i <cA.rows(); ++i)
		cA[i][i] = complex(2., 0.);
	for (int i=0; i < cA.rows()-1; ++i)
		cA[i+1][i] = cA[i][i+1] = -1.;
	// print matrix
	cA.print();




	/*** RATIONAL ***/
	std::cout << "Testing data type RATIONAL:" << std::endl;
	std::cout << "-------------------------" << std::endl;
    Matrix<Rational> rA(4,6,Rational(0));
	for (int i = 0; i < rA.rows(); ++i)
		rA[i][i] = Rational(2);
	for (int i=0; i < rA.rows()-1; ++i)
		rA[i+1][i] = rA[i][i+1] = Rational(-1);
	// print matrix
	rA.print();


}
