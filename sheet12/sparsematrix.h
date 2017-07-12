
#ifndef SPARSEMATRIX_H_
#define SPARSEMATRIX_H_


#include<vector>
#include<iomanip>
#include<iostream>
#include<cstdlib>
#include <typeinfo>
#include "exceptions.h"

template<typename T>
class SparseMatrix
{
  public:
      class Row
    {
    private:
    	  SparseMatrix* parentMatrix;
    	  unsigned int bindex, eindex;

    public:
    	  Row() : parentMatrix(0), bindex(0), eindex(0) {}
    	  Row(SparseMatrix* parentMatrix_, unsigned int bindex_, unsigned int eindex_)
    	  	  : parentMatrix(parentMatrix_), bindex(bindex_), eindex(eindex_) { }
    	  ~Row() {}

        // Nested within Row. There is a typedef later to allow direct access from the SparseMatrix class
        class ColIterator
        {
        public:
            ColIterator(unsigned int pos, Row* parentRow_) : i(pos), parentRow(parentRow_){}

            // move to next entry
            ColIterator& operator++()
            {
                i++;
                return *this;
            }
            ColIterator& operator+=(unsigned int n)
            {
                i += n;
                if(i <= parentRow->eindex)
                	return *this;
                throw "iterated out of valid range";
            }

            // comparison of iterators
            bool operator==(const ColIterator& other) const
            {
                return dcol() == other.dcol();
            }
            bool operator!=(const ColIterator& other) const
            {
                return dcol() != other.dcol();
            }

            // access to current entry
            T& operator* ()
            {
            	return parentRow->parentMatrix->data[i];
            }
            const T& operator* () const
            {
                return parentRow->parentMatrix->data[i];
            }

            // number of current entry
            unsigned int col() const
            {
                return parentRow->parentMatrix->column[i];
            }

            unsigned int dcol() const
			{
				return i;
			}

        private:
        	// current Column/entry
            unsigned int i;
            // Pointer to Row
            Row* parentRow;
        };

        class ColIteratorConst
        {
        public:
            ColIteratorConst(unsigned int pos, const Row* parentRow_) : i(pos), parentRow(parentRow_){}

            // move to next entry
            ColIteratorConst& operator++()
            {
                i++;
                return *this;
            }
            ColIteratorConst& operator+=(unsigned int n)
            {
                i += n;
                if(i <= (*parentRow).eindex)
                	return *this;
                throw "col iterated out of valid range";
            }

            // comparison of iterators
            bool operator==(const ColIteratorConst& other) const
            {
                return dcol() == other.dcol();
            }
            bool operator!=(const ColIteratorConst& other) const
            {
                return dcol() != other.dcol();
            }

            const T& operator* () const
            {
                return parentRow->parentMatrix->data[i];
            }

            // number of current entry
            unsigned int col() const
            {
                return parentRow->parentMatrix->column[i];
            }

            unsigned int dcol() const
			{
            	return i;
			}

        private:
        	// current Column/entry
            unsigned int i;
            // Pointer to Row
            const Row* parentRow;
        };

        ColIterator begin()
        {
            return ColIterator(this->bindex, this);
        }

        ColIterator end()
        {
            return ColIterator(this->eindex, this);
        }

        ColIteratorConst begin() const
        {
            return ColIteratorConst(this->bindex, this);
        }

        ColIteratorConst end() const
        {
            return ColIteratorConst(this->eindex, this);
        }

        friend class ColIterator;
        friend class ColIteratorConst;
    };

	typedef typename Row::ColIterator ColIterator;
	typedef typename Row::ColIteratorConst ColIteratorConst;



    class RowIterator
    {
    public:
        RowIterator(unsigned int pos, SparseMatrix* parentMatrix_) : i(pos), parentMatrix(parentMatrix_){}

        // move to next row
        RowIterator& operator++()
        {
            i++;
            return *this;
        }
        RowIterator& operator+=(unsigned int n)
        {
            i += n;
            if(i <= (*parentMatrix).rows())
               	return *this;
            throw "iterated out of valid range";
        }

        // comparison of iterators
        bool operator==(const RowIterator& other) const
        {
            return row() == other.row();
        }
        bool operator!=(const RowIterator& other) const
        {
            return row() != other.row();
        }

        // access to current row
        Row& operator* ()
        {
            //return (*parentMatrix)[i];
        	return parentMatrix->vrows[i];
        }
        const Row& operator* () const
        {
            //return (*parentMatrix)[i];
        	return parentMatrix->vrows[i];
        }

        // number of current row
        unsigned int row() const
        {
            return i;
        }

    private:
    	// current Row number of iterator
		unsigned int i;
		// Pointer to SparseMatrix
        SparseMatrix* parentMatrix;
    };

    class RowIteratorConst
    {
    public:
        RowIteratorConst(unsigned int pos, const SparseMatrix* parentMatrix_) : i(pos), parentMatrix(parentMatrix_){}
        // move to next row
        RowIteratorConst& operator++()
        {
            i++;
			return *this;
        }
        RowIteratorConst& operator+=(unsigned int n)
        {
            i += n;
            if(i <= (*parentMatrix).rows())
               	return *this;
            throw "row iterated out of valid range";
        }

        // comparison of iterators
        bool operator==(const RowIteratorConst& other) const
        {
            return row() == other.row();
        }
        bool operator!=(const RowIteratorConst& other) const
        {
            return row() != other.row();
        }

        // read access to current row
        const Row& operator* () const
        {
            return parentMatrix->vrows[i];
        }

        // number of current row
        unsigned int row() const
        {
            return i;
        }

    private:
    	// current Row number of iterator
		unsigned int i;
		// Pointer to SparseMatrix
        const SparseMatrix* parentMatrix;

    };

    RowIterator begin()
    {
        return RowIterator(0, this);
    }

    RowIterator end()
    {
        return RowIterator(rows(), this);
    }

    RowIteratorConst begin() const
    {
        return RowIteratorConst(0, this);
    }

    RowIteratorConst end() const
    {
        return RowIteratorConst(rows(), this);
    }

    void resize(size_t numRows_, size_t numCols_)
    {
        entries.resize(numRows_);
        for (RowIterator it = begin(); it != end(); ++it)
            (*it).resize(numCols_);
    }

    template<typename T_>
    void resize(size_t numRows_, size_t numCols_, T_ value)
    {
        entries.resize(numRows_);
        for (RowIterator it = begin(); it != end(); ++it)
        {
            (*it).resize(numCols_);
            for (typename Row::ColIterator cit = (*it).begin(); cit != (*it).end();++cit)
                (*cit) = value;
        }
    }

    // access elements
    T& operator()(size_t i, size_t j)
    {
        if (i < 0 || i >= rows())
        {
            std::cerr << "Illegal row index " << i;
            std::cerr << " valid range is [0:" << rows()-1 << "]";
            std::cerr << std::endl;
            exit(EXIT_FAILURE);
        }
        if (j < 0 || j >= cols())
        {
            std::cerr << "Illegal column index " << j;
            std::cerr << " valid range is [0:" << cols()-1 << "]";
            std::cerr << std::endl;
            exit(EXIT_FAILURE);
        }
        return entries[i][j];
    }

    T  operator()(size_t i, size_t j) const
    {
        if ( i < 0 || i >= rows())
        {
            std::cerr << "Illegal row index " << i;
            std::cerr << " valid range is [0:" << rows()-1 << "]";
            std::cerr << std::endl;
            exit(EXIT_FAILURE);
        }
        if (j < 0 || j >= cols())
        {
            std::cerr << "Illegal column index " << j;
            std::cerr << " valid range is [0:" << cols()-1 << "]";
            std::cerr << std::endl;
            exit(EXIT_FAILURE);
        }
        return entries[i][j];
    }

    Row& operator[](size_t i)
    {
        if (i < 0 || i >= rows())
        {
            std::cerr << "Illegal row index " << i;
            std::cerr << " valid range is [0:" << rows()-1 << "]";
            std::cerr << std::endl;
            exit(EXIT_FAILURE);
        }
        return entries[i];
    }

    const Row& operator[](size_t i) const
    {
        if (i < 0 || i >= rows())
        {
            std::cerr << "Illegal row index " << i;
            std::cerr << " valid range is [0:" << rows()-1 << "]";
            std::cerr << std::endl;
            exit(EXIT_FAILURE);
        }
        return entries[i];
    }

    // arithmetic functions
    template<typename T_>
    SparseMatrix<T>& operator*=(T_ x)
    {
        for (RowIterator it = begin(); it != end(); ++it)
            for (typename Row::ColIterator cit = (*it).begin(); cit != (*it).end();++cit)
                *cit *= x;
        return *this;
    }

    SparseMatrix<T>& operator+=(const SparseMatrix<T>& x)
    {
        if (x.rows() != rows() || x.cols() != cols())
        {
            std::cerr << "Dimensions of matrix a (" << rows()
                    << "x" << cols() << ") and matrix x ("
                    << x.rows() << "x" << x.cols() << ") do not match!";
            exit(EXIT_FAILURE);
        }
        for (RowIterator it = begin(); it != end(); ++it)
            for (typename Row::ColIterator cit = (*it).begin(); cit != (*it).end();++cit)
                *cit += x[it.row()][cit.col()];
        return *this;
    }

    // output
    void print() const
    {
        std::cout << "(" << rows() << "x"
        				 << cols() << ") matrix:" << std::endl;
        for(RowIteratorConst it = begin(); it != end(); ++it)
        {
        	std::cout << std::setprecision(3);

        	for (ColIteratorConst cit = (*it).begin(); cit != (*it).end(); ++cit)
        	{
        		std::cout << std::setw(5) << *cit << " ";
        	}
        	std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    size_t rows() const
    {
        return _rows;
    }
    size_t cols() const
    {
        return _cols;
    }
/*
    SparseMatrix(size_t numRows_, size_t numCols_) : entries(numRows_)
    {
        for (RowIterator it = begin(); it != end(); ++it)
            *it.resize(numCols_);
    }

    SparseMatrix(size_t dim) : SparseMatrix(dim,dim)
    {}

    SparseMatrix(size_t numRows_, size_t numCols_, T value)
    {
        resize(numRows_,numCols_,value);
    };

    SparseMatrix(std::vector<Row > a)
    {
        entries = a;
    }

    SparseMatrix(const SparseMatrix<T>& b)
    {
        entries = b.entries;
    }
*/
    SparseMatrix(unsigned int rows, unsigned int cols, unsigned int nonZeros)
    	: _rows(rows), _cols(cols), vrows(rows), rowOffset(rows), data(nonZeros), column(nonZeros)
    {

    }

    template <typename T1, typename T2>
    void fillmatrix(const std::vector<T>& data_, const T1& column_, const T2& rowOffset_)
    {
    	try
    	{
    		if (typeid(column_) != typeid(column))
			{
				throw TypeException("column vector type mismatch", "std::vector<unsigned int>");
			}

    		if (typeid(rowOffset_) != typeid(rowOffset))
			{
				throw TypeException("rowOffset vector type mismatch", "std::vector<unsigned int>");
			}

    		if (data_.size() != column_.size())
    		{
    			throw DimensionException("Dimension mismatch of data and column vector", "data", data_.size(), "column", column_.size());
    		}

    		if (rowOffset_.size() != _rows)
    		{
    			throw DimensionException("Dimension mismatch of rowOffset and sparse matrix rows", "rowOffset", rowOffset_.size(), "Sparse matrix", _rows);
    		}

    		// fill sparse matrix with given arguments
    		data = data_;
    		column = column_;
    		rowOffset = rowOffset_;

    		for (unsigned int i = 0; i < rowOffset.size()-1; i++)
    		{
    			vrows[i] = Row(this, rowOffset[i], rowOffset[i+1]);
    		}

    		vrows[rowOffset.size()-1] = Row(this, rowOffset[rowOffset.size()-1], data.size());


    	}
		catch(const std::bad_typeid& e)
		{
			std::cout << e.what() << '\n';
		}
    	catch (TypeException& e)
    	{
    		std::cout << e.what() << std::endl;
    	}
    	catch (DimensionException& e)
    	{
    		std::cout << e.what() << std::endl;
    	}

    }

  private:

    unsigned int _rows;
    unsigned int _cols;
    std::vector<Row> vrows;
    std::vector<unsigned int> rowOffset;
    std::vector<T> data;
    std::vector<unsigned int> column;



    std::vector<Row> entries;


    unsigned int pos;

    friend class RowIterator;
    friend class RowIteratorConst;
    friend class Row::ColIterator;
	friend class Row::ColIteratorConst;

};

//Template for vector multiplication
template<typename T, typename T2>
std::vector<T2> operator*(const SparseMatrix<T>& a, const std::vector<T2>& x)
{
    if (x.size() != unsigned(a.cols()))
    {
        std::cerr << "Dimensions of vector " << x.size();
        std::cerr << " and matrix " << a.cols() << " do not match!";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    };

    std::vector<T2> y(a.rows());
    for(typename SparseMatrix<T>::RowIteratorConst it = a.begin(); it != a.end(); ++it)
	{
    	y[it.row()] = 0.;

		for (typename SparseMatrix<T>::ColIteratorConst cit = (*it).begin(); cit != (*it).end(); ++cit)
		{
			y[it.row()] += (*cit) * x[cit.col()];
		}
	}

    return y;
};

template<typename T, typename T_>
SparseMatrix<T> operator*(const SparseMatrix<T>& a, T_ x)
{
    SparseMatrix<T> output(a);
    output *= x;
    return output;
}

template<typename T, typename T_>
SparseMatrix<T> operator*(T_ x, const SparseMatrix<T>& a)
{
    SparseMatrix<T> output(a);
    output *= x;
    return output;
}

template<typename T>
SparseMatrix<T> operator+(const SparseMatrix<T>& a, const SparseMatrix<T>& b)
{
    SparseMatrix<T> output(a);
    output += b;
    return output;
}



#endif /* SPARSEMATRIX_H_ */
