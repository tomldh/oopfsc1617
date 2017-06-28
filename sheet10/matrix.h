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

    Matrix<T>& operator+=(const Matrix<T>& b);
    
    /*
    // arithmetic functions
    Matrix& operator*=(double x);
    
    std::vector<double> solve(std::vector<double> b) const;
    */

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


    template<typename T2>
    Matrix<T>& operator*=(T2 value);

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

/*

Matrix<double> operator+(const Matrix<double>& a, const Matrix<double>& b)
{
    Matrix<double> output(a);
    output += b;
    return output;
}
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
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs)
{
    if (rhs.numRows != numRows || rhs.numCols != numCols)
    {
        std::cerr << "Dimensions of matrix a (" << numRows
                  << "x" << numCols << ") and matrix right hand side (" 
                  << rhs.numRows << "x" << rhs.numCols << ") do not match!";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numRows; ++i)
        for (int j = 0;j < numCols; ++j)
            entries[i][j] += rhs[i][j];
    return *this;	
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

// Templates for multiplication
template<typename T>
template<typename T2>
Matrix<T>& Matrix<T>::operator*=(T2 value)
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            entries[i][j] *= value;
        };
    };
    return *this;
};

template<typename T, typename T2>
Matrix<T> operator*(const Matrix<T>& a, T2 value)
{
    Matrix<T> result(a);
    result *= value;
    return result;
};

template<typename T, typename T2>
Matrix<T> operator*(T2 value, const Matrix<T>& a)
{
    Matrix<T> result(a);
    result *= value;
    return result;
};

/*
//Templates for Addition
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& a)
{
    if (a.numRows != numRows || a.numCols != numCols)
    {
        std::cerr << "Dimensions of matrix 1 (" << numRows
                  << "x" << numCols << ") and matrix 2 (" 
                  << a.numRows << "x" << a.numCols << ") do not match!";
        exit(EXIT_FAILURE);
    };
    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            entries[i][j] += a[i][j];
        };
    };
    return *this;
};

*/

template<typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
    Matrix<T> result(a);
    result += b;
    return result;
};

//Template for vector multiplication
template<typename T, typename T2>
std::vector<T2> operator*(const Matrix<T>& a, const std::vector<T2>& x)
{
    if (x.size() != unsigned(a.cols()))
    {
        std::cerr << "Dimensions of vector " << x.size();
        std::cerr << " and matrix " << a.cols() << " do not match!";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    };
    std::vector<T> y(a.rows());
    for (int i = 0; i < a.rows(); ++i)
    {
        y[i] = 0.;
        for (int j = 0; j < a.cols(); ++j)
            y[i] += a[i][j] * x[j];
    };
    return y;
};