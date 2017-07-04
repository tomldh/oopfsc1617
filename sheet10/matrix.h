#include<vector>
#include<iomanip>
#include<iostream>
#include<cstdlib>

template<typename T>
class Matrix
{

public:
	class Row;

	class ColIterator
	{
	private:
		//ColIterator() {};
		ColIterator(typename std::vector<T>::iterator it_, size_t index_)
		{
			it = it_;
			index = index_;
		}

	public:
		ColIterator& operator++(int i) //move to next entry
		{
			it++;
			index++;
			return (*this);
		}
		bool operator==(const ColIterator &rhs) const //comparison of iterators
		{
			return (it == rhs.it);
		}
		bool operator!=(const ColIterator &rhs) const //comparison of iterators
		{
			return (it != rhs.it);
		}
		T& operator *() //access to current entry
		{
			return (*it);
		};
		const T& operator *() const //as above, but const
		{
			return (*it);
		}
		unsigned int col() const //number of current entry
		{
			return index;
		}

	private:
		typename std::vector<T>::iterator it;
		size_t index;

		friend class Row;

	};

	class ColIteratorConst
	{
	private:
		//ColIteratorConst() {};
		ColIteratorConst(typename std::vector<T>::const_iterator it_, size_t index_)
		{
			it = it_;
			index = index_;
		}

	public:
		ColIteratorConst& operator++(int i) //move to next entry
		{
			it++;
			index++;
			return (*this);
		}
		bool operator==(const ColIteratorConst &rhs) const //comparison of iterators
		{
			return (it == rhs.it);
		}
		bool operator!=(const ColIteratorConst &rhs) const //comparison of iterators
		{
			return (it != rhs.it);
		}
		const T& operator *() const //as above, but const
		{
			return (*it);
		}
		unsigned int col() const //number of current entry
		{
			return index;
		}

	private:
		typename std::vector<T>::const_iterator it;
		size_t index;

		friend class Row;

	};

	class Row
	{
	public:
		Row() {};
		Row(size_t n)
		{
			entries.resize(n);
		}
		ColIterator begin()
		{
			return ColIterator(entries.begin(), 0);
		};
		ColIterator end()
		{
			return ColIterator(entries.end(), entries.size());
		};

		ColIteratorConst begin() const
		{
			return ColIteratorConst(entries.cbegin(), 0);
		};
		ColIteratorConst end() const
		{
			return ColIteratorConst(entries.cend(), entries.size());
		};

		T& operator[](int i)
		{
			if (i < 0 || i >= (int)entries.size())
			{
				std::cerr << "Illegal col index " << i;
				std::cerr << " valid range is [0:" << entries.size()-1 << "]";
				std::cerr << std::endl;
				exit(EXIT_FAILURE);
			}
			return entries[i];
		}
		const T& operator[](int i) const
		{
		    if (i < 0 || i >= (int)entries.size())
		    {
		        std::cerr << "Illegal col index " << i;
		        std::cerr << " valid range is [0:" << entries.size()-1 << "]";
		        std::cerr << std::endl;
		        exit(EXIT_FAILURE);
		    }
		    return entries[i];
		}

		size_t size()
		{
			return entries.size();
		};

		void resize(size_t n)
		{
			entries.resize(n);
		};


	private:
		std::vector<T> entries;
	};

	class RowIterator
	{
	private:
		//RowIterator() {};
		RowIterator(typename std::vector<Row>::iterator it_, size_t index_)
		{
			it = it_;
			index = index_;
		};
	public:
		RowIterator& operator++(int j) //move to next row
		{
			it++;
			index++;
			return (*this);
		}
		bool operator==(const RowIterator& rhs) const //comparison of iterators
		{
			return (it == rhs.it);
		}
		bool operator!=(const RowIterator& rhs) const //comparison of iterators
		{
			return (it != rhs.it);
		}
		Row& operator *() //access to current row
		{
			return (*it);
		};
		const Row& operator *() const //as above, but const
		{
			return (*it);
		};
		unsigned int row() const //number of current row
		{
			return index;
		}

	private:
		typename std::vector<Row>::iterator it;
		size_t index;

		friend class Matrix<T>;
	};

	class RowIteratorConst
	{
	private:
		//RowIteratorConst() {};
		RowIteratorConst(typename std::vector<Row>::const_iterator it_, size_t index_)
		{
			it = it_;
			index = index_;
		};
	public:
		RowIteratorConst& operator++(int j) //move to next row
		{
			it++;
			index++;
			return (*this);
		}
		bool operator==(const RowIteratorConst& rhs) const //comparison of iterators
		{
			return (it == rhs.it);
		}
		bool operator!=(const RowIteratorConst& rhs) const //comparison of iterators
		{
			return (it != rhs.it);
		}
		const Row& operator *() const //as above, but const
		{
			return (*it);
		};
		unsigned int row() const //number of current row
		{
			return index;
		}

	private:
		typename std::vector<Row>::const_iterator it;
		size_t index;

		friend class Matrix<T>;
	};


public:
	RowIterator begin()
	{
		return RowIterator(entries.begin(), 0);
	};

	RowIterator end()
	{
		return RowIterator(entries.end(), entries.size());
	};

	RowIteratorConst begin() const
	{
		return RowIteratorConst(entries.cbegin(), 0);
	};

	RowIteratorConst end() const
	{
		return RowIteratorConst(entries.cend(), entries.size());
	};


  public:
    void resize(int numRows_, int numCols_);
    void resize(int numRows_, int numCols_, T value);
    // access elements
    T& operator()(int i, int j);
    T  operator()(int i, int j) const;
    Row& operator[](int i);
    const Row& operator[](int i) const;

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
    
    Matrix(std::vector<Row> a)
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
    //std::vector<std::vector<T> > entries;
  	std::vector<Row> entries;
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
        //entries[i].resize(numCols_);
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

        for (ColIterator cit = entries[i].begin(); cit != entries[i].end(); cit++)
		{
			(*cit) = value;
		}
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
typename Matrix<T>::Row& Matrix<T>::operator[](int i)
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


template <typename T>
const typename Matrix<T>::Row& Matrix<T>::operator[](int i) const
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
    for (RowIterator i = begin(); i != end(); i++)
    {
    	for (ColIterator j = (*i).begin(); j != (*i).end(); j++)
    		(*j) += rhs[i.row()][j.col()];
    }

    return *this;	
}


template<typename T>
void Matrix<T>::print() const
{
    std::cout << "(" << numRows << "x";
    std::cout << numCols << ") matrix:" << std::endl;
    for (RowIteratorConst i = begin(); i != end(); i++)
    {
        std::cout << std::setprecision(3);
        for (ColIteratorConst j = (*i).begin(); j != (*i).end(); j++)
            std::cout << std::setw(5) << (*j) << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Templates for multiplication
template<typename T>
template<typename T2>
Matrix<T>& Matrix<T>::operator*=(T2 value)
{
	for (RowIterator i = begin(); i != end(); i++)
	{
		for (ColIterator j = (*i).begin(); j != (*i).end(); j++)
			(*j) *= value;
	}

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

