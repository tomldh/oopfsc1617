#include "matrix.h"
#include<iomanip>
#include<iostream>
#include<cstdlib>


/*
Matrix& Matrix::operator*=(double x)
{
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            entries[i][j] *= x;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& x)
{
    if (x.numRows != numRows || x.numCols != numCols)
    {
        std::cerr << "Dimensions of matrix a (" << numRows
                  << "x" << numCols << ") and matrix x (" 
                  << x.numRows << "x" << x.numCols << ") do not match!";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numRows; ++i)
        for (int j = 0;j < numCols; ++j)
            entries[i][j] += x[i][j];
    return *this;
}

std::vector<double> Matrix::solve(std::vector<double> b) const
{
    std::vector<std::vector<double> > a(entries);
    for (int m = 0; m < numRows-1; ++m)
        for (int i = m+1; i < numRows; ++i)
        {
            double q = a[i][m]/a[m][m];
            a[i][m] = 0.;
            for (int j= m+1; j < numRows; ++j)
                a[i][j] = a[i][j] - q * a[m][j];
            b[i] -= q*b[m];
        }
    std::vector<double> x(b);
    x.back() /= a[numRows-1][numRows-1];
    for (int i = numRows-2; i >= 0; --i)
    {
        for (int j = i+1; j < numRows; ++j)
            x[i] -= a[i][j] * x[j];
        x[i] /= a[i][i];
    }
    return(x);    
}
*/

/*
Matrix operator*(const Matrix& a, double x)
{
    Matrix output(a);
    output *= x;
    return output;
}

Matrix operator*(double x, const Matrix& a)
{
    Matrix output(a);
    output *= x;
    return output;
}

std::vector<double> operator*(const Matrix& a,
                              const std::vector<double>& x)
{
    if (x.size() != a.cols())
    {
        std::cerr << "Dimensions of vector " << x.size();
        std::cerr << " and matrix " << a.cols() << " do not match!";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<double> y(a.rows());
    for (int i = 0; i < a.rows(); ++i)
    {
        y[i] = 0.;
        for (int j = 0; j < a.cols(); ++j)
            y[i] += a[i][j] * x[j];
    }
    return y;
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
    Matrix output(a);
    output += b;
    return output;
}
*/
