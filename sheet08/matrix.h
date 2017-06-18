#include<vector>
#include<iomanip>
#include<iostream>
#include<cstdlib>

template<typename T>
class Matrix
{
  public:
    void resize(int numRows_, int numCols_);
    void resize(int numRows_, int numCols_, T value);
    // access elements
    T& operator()(int i, int j);
    T  operator()(int i, int j) const;
    std::vector<T>& operator[](int i);
    const std::vector<T>& operator[](int i) const;

    // arithmetic functions
    template<typename T2>
    Matrix<T>& operator*=(T2 x);
    Matrix<T>& operator+=(const Matrix<T>& b);
    std::vector<T> solve(std::vector<T> b) const;

    // output
    void print() const;
    int rows() const
    {
        return numRows;
    }
    int cols() const
    {
        return numCols;
    }
    
    Matrix(int numRows_, int numCols_) :
            entries(numRows_), numRows(numRows_), numCols(numCols_)
    {
        for (int i = 0; i < numRows_; ++i)
            entries[i].resize(numCols_);
    };
    
    Matrix(int dim) : Matrix(dim,dim)
    {};
    
    Matrix(int numRows_, int numCols_, T value)
    {
        resize(numRows_,numCols_,value);
    };
    
    Matrix(std::vector<std::vector<T> > a)
    {
        entries = a;
        numRows = a.size();
        if (numRows > 0)
            numCols = a[0].size();
        else
            numCols = 0;
    }
    
    Matrix(const Matrix& b)
    {
        entries = b.entries;
        numRows = b.numRows;
        numCols = b.numCols;
    }
    
  private:
    std::vector<std::vector<T> > entries;
    int numRows = 0;
    int numCols = 0;
};
/*
std::vector<double> operator*(const Matrix& a,
                              const std::vector<double>& x);
Matrix operator*(const Matrix& a, double x);
Matrix operator*(double x, const Matrix& a);
Matrix operator+(const Matrix& a, const Matrix& b);
*/


template<typename T>
void Matrix<T>::resize(int numRows_, int numCols_)
{
    entries.resize(numRows_);
    for (size_t i = 0; i < entries.size(); ++i)
        entries[i].resize(numCols_);
    numRows = numRows_;
    numCols = numCols_;
}

template<typename T>
void Matrix<T>::resize(int numRows_, int numCols_, T value)
{
    entries.resize(numRows_);
    for (size_t i = 0; i < entries.size(); ++i)
    {
        entries[i].resize(numCols_);
        for (size_t j = 0; j < entries[i].size(); ++j)
            entries[i][j] = value;
    }
    numRows = numRows_;
    numCols = numCols_;
}

template<typename T>
T& Matrix<T>::operator()(int i, int j)
{
    if (i < 0 || i >= numRows)
    {
        std::cerr << "Illegal row index " << i;
        std::cerr << " valid range is [0:" << numRows-1 << "]";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    if (j < 0 || j >= numCols)
    {
        std::cerr << "Illegal column index " << j;
        std::cerr << " valid range is [0:" << numCols-1 << "]";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    return entries[i][j];
}

template<typename T>
T Matrix<T>::operator()(int i, int j) const
{
    if ( i < 0 || i >= numRows)
    {
        std::cerr << "Illegal row index " << i;
        std::cerr << " valid range is [0:" << numRows-1 << "]";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    if (j < 0 || j >= numCols)
    {
        std::cerr << "Illegal column index " << j;
        std::cerr << " valid range is [0:" << numCols-1 << "]";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    return entries[i][j];
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](int i)
{
    if (i < 0 || i >= numRows)
    {
        std::cerr << "Illegal row index " << i;
        std::cerr << " valid range is [0:" << numRows-1 << "]";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    return entries[i];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](int i) const
{
    if (i < 0 || i >= numRows)
    {
        std::cerr << "Illegal row index " << i;
        std::cerr << " valid range is [0:" << numRows-1 << "]";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    return entries[i];
}

template<typename T>
void Matrix<T>::print() const
{
    std::cout << "(" << numRows << "x";
    std::cout << numCols << ") matrix:" << std::endl;
    for (int i = 0; i < numRows; ++i)
    {
        std::cout << std::setprecision(3);
        for (int j = 0; j < numCols; ++j)
            std::cout << std::setw(5) << entries[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<typename T>
template<typename T2>
Matrix<T>& Matrix<T>::operator*=(T2 x)
{
	//T tx(x);
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            entries[i][j] *= x;
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& x)
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

template<typename T>
std::vector<T> Matrix<T>::solve(std::vector<T> b) const
{
    std::vector<std::vector<T> > a(entries);
    for (int m = 0; m < numRows-1; ++m)
        for (int i = m+1; i < numRows; ++i)
        {
            T q = a[i][m]/a[m][m];
            a[i][m] = 0.;
            for (int j= m+1; j < numRows; ++j)
                a[i][j] = a[i][j] - q * a[m][j];
            b[i] -= q*b[m];
        }
    std::vector<T> x(b);
    x.back() /= a[numRows-1][numRows-1];
    for (int i = numRows-2; i >= 0; --i)
    {
        for (int j = i+1; j < numRows; ++j)
            x[i] -= a[i][j] * x[j];
        x[i] /= a[i][i];
    }
    return(x);
}


template<typename T, typename T2>
Matrix<T> operator*(const Matrix<T>& a, T2 x)
{
    Matrix<T> output(a);
    output *= x;
    return output;
}

template<typename T, typename T2>
Matrix<T> operator*(T2 x, const Matrix<T>& a)
{
    Matrix<T> output(a);
    output *= x;
    return output;
}

template<typename T, typename T2>
std::vector<T2> operator*(const Matrix<T>& a,
                              const std::vector<T2>& x)
{
    if (x.size() != a.cols())
    {
        std::cerr << "Dimensions of vector " << x.size();
        std::cerr << " and matrix " << a.cols() << " do not match!";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<T2> y(a.rows());
    for (int i = 0; i < a.rows(); ++i)
    {
        y[i] = 0.;
        for (int j = 0; j < a.cols(); ++j)
            y[i] += a[i][j] * x[j];
    }
    return y;
}

template<typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
    Matrix<T> output(a);
    output += b;
    return output;
}


