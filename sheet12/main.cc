#include "sparsematrix.h"
#include<iostream>
#include<complex>
#include <assert.h>
#include "matrix.h"
#include <algorithm>
#include <chrono>
#include <list>

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
std::vector<double> gradientDescent(M& A, const std::vector<T>& b, std::vector<T>& x, int maxIter)
{
	std::cout << "\nStarting Gradient Descent algorithm..." << std::endl;

	assert(A.rows()==A.cols()); // ensure square matrix
	assert(A.cols()==x.size()); // ensure compatible dimension
	assert(x.size()==b.size()); // ensure compatible dimension

	if (x.size() < 10)
	{
		std::cout << "x = [";
		for (unsigned int i = 0; i < x.size(); i++)
			std::cout << x[i] << " ";
		std::cout << "]" << std::endl;
	}

	std::vector<T> r(b.size());
	std::vector<T> ar(b.size());
	std::vector<T> xtmp(x.size());
	T g(0);
	std::vector<double> convergence;

	for (int m = 0; m < maxIter; m++)
	{

		r = A*x;

		for(unsigned int i = 0; i < b.size(); i++)
		{
			r[i] = b[i] - r[i];
		}

		ar = A*r;

		g = std::inner_product(r.begin(), r.end(), r.begin(), T(0)) / std::inner_product(r.begin(), r.end(), ar.begin(), T(0));

		for (unsigned int i = 0; i < x.size(); i++)
		{
			xtmp[i] = x[i] + r[i] * g;
		}

		for(unsigned int i = 0; i < x.size(); i++)
		{
			x[i] = x[i] - xtmp[i];
		}

		convergence.push_back(std::inner_product(x.begin(), x.end(), x.begin(), double(0)));

		x = xtmp;
	}

	return convergence;

}

std::vector<double> dirichlet(unsigned int N, int maxiter, std::vector<double> x, bool useDense=false)
{

	std::cout << "\n===============================\n" << std::endl;
	std::cout << "Dirichlet, N=" << N << std::endl;

	Matrix<double> A(N, N, 0.);
	for (unsigned int i = 0; i < A.rows(); ++i)
		A[i][i] = 2.;
	for (unsigned int i= 0; i < A.rows()-1; ++i)
		A[i+1][i] = A[i][i+1] = -1.;

	A[0][0] = 1.;
	A[0][1] = 0.;
	A[A.rows()-1][A.cols()-1] = 1.;
	A[A.rows()-1][A.cols()-2] = 0.;

	if (N < 10)
	{
		std::cout << "Dense ";
		A.print();
	}


	std::vector<double> data;
	std::vector<unsigned int> columns;
	std::vector<unsigned int> rowOffset;
	A.crs(data, columns, rowOffset);

	SparseMatrix<double> sA(N, N, data.size());
	sA.fillmatrix(data, columns, rowOffset);

	if (N < 10)
	{
		std::cout << "Sparse ";
		sA.print();
	}


	std::vector<double> b(N, 1.);
	b[0] = x[0]; b[b.size()-1] = x[x.size()-1];

	if (N < 10)
	{
		std::cout << "b = [";
		for (unsigned int i = 0; i < b.size(); i++)
			std::cout << b[i] << " ";
		std::cout << "]" << std::endl;
	}

	std::vector<double> cvg;

	if (useDense)
		cvg = gradientDescent(A, b, x, maxiter);
	else
		cvg = gradientDescent(sA, b, x, maxiter);

	return cvg;

}

std::vector<double> neumann(unsigned int N, int maxiter, std::vector<double> x, bool useDense=false)
{
	std::cout << "\n===============================\n" << std::endl;
	std::cout << "Neumann, N=" << N << std::endl;

	Matrix<double> A(N, N, 0.);
	for (unsigned int i = 0; i < A.rows(); ++i)
		A[i][i] = 2.;
	for (unsigned int i= 0; i < A.rows()-1; ++i)
		A[i+1][i] = A[i][i+1] = -1.;

	if (N < 10)
	{
		std::cout << "Dense ";
		A.print();
	}

	std::vector<double> data;
	std::vector<unsigned int> columns;
	std::vector<unsigned int> rowOffset;
	A.crs(data, columns, rowOffset);

	SparseMatrix<double> sA(N, N, data.size());
	sA.fillmatrix(data, columns, rowOffset);

	if (N < 10)
	{
		std::cout << "Sparse ";
		sA.print();
	}

	std::vector<double> b(N, 1.);

	if (N < 10)
	{
		std::cout << "b = [";
		for (unsigned int i = 0; i < b.size(); i++)
			std::cout << b[i] << " ";
		std::cout << "]" << std::endl;
	}

	std::vector<double> cvg;

	if (useDense)
		cvg = gradientDescent(A, b, x, maxiter);
	else
		cvg = gradientDescent(sA, b, x, maxiter);

	return cvg;
}


int main()
{

	try
	{
		std::vector<double> data{2, 1, 1, 3, 2, 1, -4};
		std::vector<unsigned int> col{0, 1, 0, 1, 2, 1, 2};
		std::vector<unsigned int> offset{0, 2, 5};

		SparseMatrix<double> derrorA(4, 3, 7);
		derrorA.fillmatrix<std::vector<unsigned int>, std::vector<unsigned int>>(data, col, offset);


		SparseMatrix<double> terrorA(3, 3, 7);
		std::list<unsigned int> erroroffset{0, 2, 5};
		terrorA.fillmatrix<std::vector<unsigned int>, std::list<unsigned int>>(data, col, erroroffset);

		SparseMatrix<double> A(3, 3, 7);
		A.fillmatrix(data, col, offset);

		A.print();

		std::cout << frobeniusnorm<SparseMatrix<double>>(A) <<std::endl;

		std::vector<double> sx{1,1,1};
		std::vector<double> sb{1,2,3};
		int numIter = 5;

		gaussSeidel<SparseMatrix<double>, double>(A, sb, sx, numIter);

		std::cout << "Approximate solution after " << numIter << " iterations is: ";
		std::cout << "x = [" << sx[0] << " " << sx[1] << " " << sx[2] << "]" << std::endl;


		// Test convergence

		unsigned int matrixSize = 100;
		int numOfiter = 20;

		std::vector<double> x(matrixSize, 0.5);
		x[0] = 0.1; x[x.size()-1] = 10.0;

		std::vector<double> cvg_n = neumann(matrixSize, numOfiter, x);

		std::vector<double> cvg_d = dirichlet(matrixSize, numOfiter, x);

		// Write convergence to file for plotting
		//TODO


		// Test time based on problem size
		std::vector<unsigned int> problem{1000, 5000, 10000};

		for (unsigned int i = 0; i < problem.size(); i++)
		{
			std::vector<double> px(problem[i], 0.5);
			x[0] = 0.1; x[x.size()-1] = 10.0;

			auto start = std::chrono::high_resolution_clock::now();
			neumann(problem[i], numOfiter, px, true);
			auto end = std::chrono::high_resolution_clock::now();
			auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / 1000.;

			std::cout << "N=" << problem[i] << ", Neumann dense, Time=" << ms << std::endl;

			start = std::chrono::high_resolution_clock::now();
			neumann(problem[i], numOfiter, px);
			end = std::chrono::high_resolution_clock::now();
			ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / 1000.;

			std::cout << "N=" << problem[i] << ", Neumann sparse, Time=" << ms << std::endl;
		}


	}
	catch (const char* ex)
	{
		std::cout << ex << std::endl;
	}

}
