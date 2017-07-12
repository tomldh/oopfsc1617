#include "sparsematrix.h"
#include<iostream>
#include<complex>
#include <assert.h>
#include "matrix.h"

typedef std::complex<double> complex;

template <class M>
double frobeniusnorm(const M& matrix)
{
	double sum = 0.0;

	for (typename M::RowIteratorConst i = matrix.begin(); i != matrix.end(); ++i)
	{
		for (typename M::ColIteratorConst j = (*i).begin(); j!= (*i).end(); ++j)
		{
			sum += (*j) * (*j);
		}
	}

	return std::sqrt(sum);
}

template<class M, class T>
void gaussSeidel(const M& A, const std::vector<T>& b, std::vector<T>& x, int maxIter)
{
	std::cout << "Starting Gauss Seidel algorithm..." << std::endl;
	std::cout << "A = ";
	A.print();
	std::cout << "b = [" << b[0] << " " << b[1] << " " << b[2] << "]"<< std::endl;


	assert(A.rows()==A.cols()); // ensure square matrix
	assert(A.cols()==x.size()); // ensure compatible dimension
	assert(x.size()==b.size()); // ensure compatible dimension

    // initialize x with zero values
    std::fill(x.begin(), x.end(), 0);

    std::cout << "Initialize x = [" << x[0] << " " << x[1] << " " << x[2] << "]"<< std::endl;

    for (int m = 0; m < maxIter; m++)
    {
        for (typename M::RowIteratorConst riter = A.begin(); riter != A.end(); ++riter)
        {
            unsigned int k = riter.row(); //row index

            T sum = 0;
            T a_kk = 1;

            for (typename M::ColIteratorConst citer = (*riter).begin(); citer != (*riter).end(); ++citer)
            {
                unsigned int i = citer.col(); // col index

                if (k == i)
                {
                    a_kk = (*citer);
                }
                else
                {
                    sum += (*citer) * x[i];
                }
            }
            if (a_kk == 0)
            {
            	x[k] = 0;
            }
            else
            {
            	x[k] = (b[k] - sum) / a_kk;
            }
        }

        std::cout << "Iteration " << m << ": x = [" << x[0] << " " << x[1] << " " << x[2] << "]" << std::endl;
    }

}

template <class M, class T>
void gradientDescent(M& matrix, const std::vector<T>& b, std::vector<T>& x, int maxIter)
{
	for (int m = 0; m < maxIter; m++)
	{

	}
}


int main()
{

	try
	{
		SparseMatrix<double> A(3, 3, 7);

		std::vector<double> data{2, 1, 1, 3, 2, 1, -4};
		std::vector<unsigned int> col{0, 1, 0, 1, 2, 1, 2};
		std::vector<unsigned int> offset{0, 2, 5};

		A.fillmatrix(data, col, offset);

		A.print();

		std::cout << frobeniusnorm<SparseMatrix<double>>(A) <<std::endl;

		std::vector<double> x{1,1,1};
		std::vector<double> b{1,2,3};
		int numIter = 5;

		gaussSeidel<SparseMatrix<double>, double>(A, b, x, numIter);

		std::cout << "Approximate solution after " << numIter << " iterations is: ";
		std::cout << "x = [" << x[0] << " " << x[1] << " " << x[2] << "]" << std::endl;

		/*
		Matrix<double> B(4, 4, 0.);
		for (int i = 0; i < B.rows(); ++i)
			B[i][i] = 2.;
		for (int i= 0; i < B.rows()-1; ++i)
			B[i+1][i] = B[i][i+1] = -1.;

		B[0][0] = 1.;
		B[0][1] = 0.;
		B[B.rows()-1][B.cols()-1] = 1.;
		B[B.rows()-1][B.cols()-2] = 0.;

		B.print();
		*/
		Matrix<double> B(3,3,0.);

		B[0][0] = 2; B[0][1] = 1; B[0][2] = 0;
		B[1][0] = 1; B[1][1] = 3; B[1][2] = 2;
		B[2][0] = 0; B[2][1] = 1; B[2][2] = -4;

		std::vector<double> xb {2., 2., 2.};

		std::vector<double> res = B*xb;

		std::cout << res[0] << " " << res[1] << " " << res[2] << std::endl;

		std::vector<double> dataB;
		std::vector<unsigned int> colB;
		std::vector<unsigned int> offsetB;
		B.crs(dataB, colB, offsetB);

	}
	catch (const char* ex)
	{
		std::cout << ex << std::endl;
	}


	/*

	SparseMatrix<double> A(4,4,0.);
	A.print();
    for (SparseMatrix<double>::RowIterator it = A.begin(); it != A.end(); ++it)//size_t i = 0; i < A.rows(); ++i)
    {
        SparseMatrix<double>::ColIterator cit(it.row(), &*it);
    	*cit = 2.2355323322;
    }
    A.print();
    for (size_t i=0; i < A.rows()-1; ++i)
    {
		A[i+1][i] = A[i][i+1] = -1.2323;
    }
    A.print();

	std::vector<double> b(4);
    b[0] = 5.;
    b[1] = b[3] = -4.;
    b[2] = 4.;
    std::vector<double> x =  A.solve(b);
    A.print();
    for(auto& it : x)
    	std::cout << it << std::endl;
    std::vector<double> xyz(4);

    xyz = A * x;
	std::cout << std::endl;
    for(auto& it : xyz)
    	std::cout << it << std::endl;


#if 1==1
    // test SparseMatrix<complex>
    complex xy({1, 1});
    SparseMatrix<complex> E(2,2,xy);
    E += SparseMatrix<complex>(2,2,{1, 2});
    E(0,0) = 1;
    E = E * complex{0,1};
    // define vector c
    std::vector<complex> c(2);
    c[0] = 5.;
    c[1] = -4.;
    std::vector<complex> y = E * c;
    std::cout << "E*c = ( ";
    for (size_t i = 0; i < y.size(); ++i)
        std::cout << y[i] << "  ";
    std::cout << ")" << std::endl;
    std::cout << std::endl;
    // solve
    //y = E.solve(c);
    E.print();
    std::cout << "The solution with the ordinary Gauss Elimination is: ( ";
    for (size_t i = 0; i < y.size(); ++i)
        std::cout << y[i] << "  ";
    std::cout << ")" << std::endl;
    std::cout << std::endl;

    // test SparseMatrix<float>
    SparseMatrix<float> G(3,2,1.1);
    G(0,0) = G(1,1) = G(2,0) = -1.1;
    double a = 0.9;
    SparseMatrix<float> H = a * G; // we can multiply a float matrix with a double scalar
    H.print();

    SparseMatrix<int> I(2,2,0);
    I(0,0) = I(1,1) = 2;
    I.print();
    I *= 1.0/3.0;
    I.print();
    SparseMatrix<int> J = I + SparseMatrix<int>(2,2,1);
    J.print();
#endif

*/
}
