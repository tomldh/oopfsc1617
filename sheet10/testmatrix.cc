#include "matrix.h"
#include <iostream>
#include <complex>
#include <vector>
#include "rational.hh"

typedef std::complex<double> complex;

int main()
{
    //test

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
    Matrix<double> D(4,6,0.);
    for (int i = 0; i < D.rows(); ++i)  
        D[i][i] = 4.;
    for (int i=0; i < D.rows()-1; ++i) 
        D[i+1][i] = D[i][i+1] = -3.;
    // print matrix
    std::cout << "A = " << std::endl;
    A.print();
    std::cout << "B = " << std::endl;
    B.print();
    std::cout << "D = " << std::endl;
    D.print();


    std::cout << "Addition: " << std::endl;
    std::cout << " A + D:" << std::endl;
    Matrix<double> E = A + D;
    E.print();
    
    std::cout << "Multiplication: " << std::endl;
    std::cout << " A * 5:" << std::endl;
    Matrix<double> C = A * 5;
    C.print();
    std::cout << " 5 * A:" << std::endl;
    C = 5 * A;
    C.print();
    std::cout << " A *= 5:" << std::endl;
    C = A;
    C *= 5;
    C.print();
    std::vector<double> v = {1,1,2,3,4,5};
    std::vector<double> v2 = A * v;
    std::cout << " v = [ ";
    for(unsigned int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << ' ';
    };
    std::cout << "]" << std::endl;
    std::cout << " A * v:" << " [ ";
    for(unsigned int i = 0; i < v2.size(); ++i)
    {
        std::cout << v2[i] << ' ';
    };
    std::cout << "]" << std::endl << std::endl;

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
    std::cout << "A = " << std::endl;
	fA.print();
    
    Matrix<float> fD(4,6,0.);
    for (int i = 0; i < fD.rows(); ++i)  
        fD[i][i] = 4.;
    for (int i=0; i < fD.rows()-1; ++i) 
        fD[i+1][i] = fD[i][i+1] = -3.;

    std::cout << "D = " << std::endl;
    fD.print();

    std::cout << "Addition: " << std::endl;
    std::cout << " A + D:" << std::endl;
    Matrix<float> fE = fA + fD;
    fE.print();

    std::cout << "Multiplication: " << std::endl;
    std::cout << " A * 5:" << std::endl;
    Matrix<float> fC = fA * 5;
    fC.print();
    std::cout << " 5 * A:" << std::endl;
    fC = 5 * fA;
    fC.print();
    std::cout << " A *= 5:" << std::endl;
    fC = fA;
    fC *= 5;
    fC.print();
    std::vector<float> fv = {1,1,2,3,4,5};
    std::vector<float> fv2 = fA * fv;
    std::cout << " v = [ ";
    for(unsigned int i = 0; i < fv.size(); ++i)
    {
        std::cout << fv[i] << ' ';
    };
    std::cout << "]" << std::endl;
    std::cout << " A * v:" << " [ ";
    for(unsigned int i = 0; i < fv2.size(); ++i)
    {
        std::cout << fv2[i] << ' ';
    };
    std::cout << "]" << std::endl << std::endl;

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
    std::cout << "A = " << std::endl;
	iA.print();

    Matrix<int> iD(4,6,0.);
    for (int i = 0; i < iD.rows(); ++i)  
        iD[i][i] = 4.;
    for (int i=0; i < iD.rows()-1; ++i) 
        iD[i+1][i] = iD[i][i+1] = -3.;

    std::cout << "D = " << std::endl;
    iD.print();

    std::cout << "Addition: " << std::endl;
    std::cout << " A + D:" << std::endl;
    Matrix<int> iE = iA + iD;
    iE.print();

    std::cout << "Multiplication: " << std::endl;
    std::cout << " A * 5:" << std::endl;
    Matrix<int> iC = iA * 5;
    iC.print();
    std::cout << " 5 * A:" << std::endl;
    iC = 5 * iA;
    iC.print();
    std::cout << " A *= 5:" << std::endl;
    iC = iA;
    iC *= 5;
    iC.print();
    std::vector<int> iv = {1,1,2,3,4,5};
    std::vector<int> iv2 = iA * iv;
    std::cout << " v = [ ";
    for(unsigned int i = 0; i < iv.size(); ++i)
    {
        std::cout << iv[i] << ' ';
    };
    std::cout << "]" << std::endl;
    std::cout << " A * v:" << " [ ";
    for(unsigned int i = 0; i < iv2.size(); ++i)
    {
        std::cout << iv2[i] << ' ';
    };
    std::cout << "]" << std::endl << std::endl;
    
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
    std::cout << "A = " << std::endl;
	cA.print();

    Matrix<complex> cD(4,6,complex(0.,0.));
    for (int i = 0; i < cD.rows(); ++i)  
        cD[i][i] = complex(4.,0.);
    for (int i=0; i < cD.rows()-1; ++i) 
        cD[i+1][i] = cD[i][i+1] = complex(-3.,1.);

    std::cout << "D = " << std::endl;
    cD.print();

    std::cout << "Addition: " << std::endl;
    std::cout << " A + D:" << std::endl;
    Matrix<complex> cE = cA + cD;
    cE.print();

    std::cout << "Multiplication: " << std::endl;
    std::cout << " A * 5:" << std::endl;
    Matrix<complex> cC = cA * 5;
    cC.print();
    std::cout << " 5 * A:" << std::endl;
    cC = 5 * cA;
    cC.print();
    std::cout << " A *= 5:" << std::endl;
    cC = cA;
    cC *= 5;
    cC.print();
    std::vector<complex> cv = {1,1,2,3,4,5};
    std::vector<complex> cv2 = cA * cv;
    std::cout << " v = [ ";
    for(unsigned int i = 0; i < cv.size(); ++i)
    {
        std::cout << cv[i] << ' ';
    };
    std::cout << "]" << std::endl;
    std::cout << " A * v:" << " [ ";
    for(unsigned int i = 0; i < cv2.size(); ++i)
    {
        std::cout << cv2[i] << ' ';
    };
    std::cout << "]" << std::endl << std::endl;

	/*** RATIONAL ***/
	std::cout << "Testing data type RATIONAL:" << std::endl;
	std::cout << "-------------------------" << std::endl;
    Matrix<Rational> rA(4,6,Rational(0));
	for (int i = 0; i < rA.rows(); ++i)
		rA[i][i] = Rational(2);
	for (int i=0; i < rA.rows()-1; ++i)
		rA[i+1][i] = rA[i][i+1] = Rational(-1);
	// print matrix
    std::cout << "A = " << std::endl;
	rA.print();

    Matrix<Rational> rD(4,6,Rational(0));
    for (int i = 0; i < rD.rows(); ++i)
        rD[i][i] = Rational(4,3);
    for (int i=0; i < rD.rows()-1; ++i)
        rD[i+1][i] = rD[i][i+1] = Rational(-3,2);
    // print matrix
    std::cout << "D = " << std::endl;
    rD.print();

    std::cout << "Addition: " << std::endl;
    std::cout << " A + D:" << std::endl;
    Matrix<Rational> rE = rA + rD;
    rE.print();

    std::cout << "Multiplication: " << std::endl;
    std::cout << " A * 5:" << std::endl;
    Matrix<Rational> rC = rA * 5;
    rC.print();
    std::cout << " 5 * A:" << std::endl;
    rC = 5 * rA;
    rC.print();
    std::cout << " A *= 5:" << std::endl;
    rC = rA;
    rC *= 5;
    rC.print();
    std::vector<Rational> rv = {1,1,2,3,4,5};
    std::vector<Rational> rv2 = rA * rv;
    std::cout << " v = [ ";
    for(unsigned int i = 0; i < rv.size(); ++i)
    {
        std::cout << rv[i] << ' ';
    };
    std::cout << "]" << std::endl;
    std::cout << " A * v:" << " [ ";
    for(unsigned int i = 0; i < rv2.size(); ++i)
    {
        std::cout << rv2[i] << ' ';
    };
    std::cout << "]" << std::endl << std::endl;
}
