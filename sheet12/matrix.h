#include<vector>
#include<iomanip>
#include<iostream>
#include<cstdlib>

template<typename T>
class Matrix
{
  public:
      class Row : public std::vector<T>
    {
        public:
        // Inheriting constructors from std::vector<double>
        using std::vector<T>::vector; 
        
        // Nested within Row. There is a typedef later to allow direct access from the Matrix class
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
                if(i <= (*parentRow).size())
                	return *this;
                throw "iterated out of valid range";
            }
            
            // comparison of iterators
            bool operator==(const ColIterator& other) const        
            {
                return i == other.col();
            }
            bool operator!=(const ColIterator& other) const       
            {
                return i != other.col();
            }
            
            // access to current entry
            T& operator* ()                
            {
            	return (*parentRow)[i];
            }           
            const T& operator* () const    
            {
                return (*parentRow)[i];
            }
            
            // number of current entry
            unsigned int col() const       
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
                if(i <= (*parentRow).size())
                	return *this;
                throw "iterated out of valid range";
            }
            ColIteratorConst& operator+=(unsigned int n)     
            {
                i += n;
                if(i <= (*parentRow).size())
                	return *this;
                throw "iterated out of valid range";
            }
            
            // comparison of iterators
            bool operator==(const ColIteratorConst& other) const        
            {
                return i == other.col();
            }
            bool operator!=(const ColIteratorConst& other) const       
            {
                return i != other.col();
            }
                  
            const T& operator* () const    
            {
                return (*parentRow)[i];
            }
            
            // number of current entry
            unsigned int col() const       
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
            return ColIterator(0, this);
        }
        
        ColIterator end()
        {
            return ColIterator(this->size(), this);
        }
        
        ColIteratorConst begin() const
        {
            return ColIteratorConst(0, this);
        }
        
        ColIteratorConst end() const
        {
            return ColIteratorConst(this->size(), this);
        }
    };

	typedef typename Row::ColIterator ColIterator;
	typedef typename Row::ColIteratorConst ColIteratorConst;

    class RowIterator
    {
    public:
        RowIterator(unsigned int pos, Matrix* parentMatrix_) : i(pos), parentMatrix(parentMatrix_){}
        
        // move to next row
        RowIterator& operator++()      
        {
            i++;
            if(i <= (*parentMatrix).rows())
            	return *this;
            throw "iterated out of valid range";
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
            return i == other.row();
        }
        bool operator!=(const RowIterator& other) const        
        {
            return i != other.row();
        }
        
        // access to current row
        Row& operator* ()              
        {
            return (*parentMatrix)[i];
        }        
        const Row& operator* () const  
        {
            return (*parentMatrix)[i];
        }
        
        // number of current row
        unsigned int row() const       
        {
            return i;
        }
        
    private:
    	// current Row number of iterator
		unsigned int i;
		// Pointer to Matrix
        Matrix* parentMatrix;
    };
       
    class RowIteratorConst
    {
    public:     
        RowIteratorConst(unsigned int pos, const Matrix* parentMatrix_) : i(pos), parentMatrix(parentMatrix_){}
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
            throw "iterated out of valid range";
        }
                
        // comparison of iterators
        bool operator==(const RowIteratorConst& other) const        
        {
            return i == other.row();
        }
        bool operator!=(const RowIteratorConst& other) const        
        {
            return i != other.row();
        }
        
        // read access to current row     
        const Row& operator* () const  
        {
            return (*parentMatrix)[i];
        }
        
        // number of current row
        unsigned int row() const       
        {
            return i;
        }
        
    private:
    	// current Row number of iterator
		unsigned int i;
		// Pointer to Matrix
        const Matrix* parentMatrix;
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
    Matrix<T>& operator*=(T_ x)
    {
        for (RowIterator it = begin(); it != end(); ++it)
            for (typename Row::ColIterator cit = (*it).begin(); cit != (*it).end();++cit)
                *cit *= x;
        return *this;
    }
    
    Matrix<T>& operator+=(const Matrix<T>& x)
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
   
    std::vector<T> solve(std::vector<T> b) const
    {
        Matrix a(entries);
        for (size_t m = 0; m < rows()-1; ++m)
            for (size_t i = m+1; i < rows(); ++i)
            {
                T q = a[i][m]/a[m][m];
                a[i][m] = 0.;
                for (size_t j= m+1; j < rows(); ++j)
                    a[i][j] = a[i][j] - q * a[m][j];
                b[i] -= q*b[m];
            }
        std::vector<T> x(b);
        x.back() /= a[rows()-1][rows()-1];
        for (int i = rows()-2; i >= 0; --i)
        {
            for (size_t j = i+1; j < rows(); ++j)
                x[i] -= a[i][j] * x[j];
            x[i] /= a[i][i];
        }
        return(x);    
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
        return entries.size();
    }
    size_t cols() const
    {
        return entries[0].size();
    }
    
    Matrix(size_t numRows_, size_t numCols_) : entries(numRows_)
    {
        for (RowIterator it = begin(); it != end(); ++it)
            *it.resize(numCols_);
    }
    
    Matrix(size_t dim) : Matrix(dim,dim)
    {}
    
    Matrix(size_t numRows_, size_t numCols_, T value)
    {
        resize(numRows_,numCols_,value);
    };
    
    Matrix(std::vector<Row > a)
    {
        entries = a;
    }
    
    Matrix(const Matrix<T>& b)
    {
        entries = b.entries;
    }
    
    void crs(std::vector<T>& data, std::vector<unsigned int>& columns, std::vector<unsigned int>& rowOffset) const
    {


    	data.resize(0);
    	columns.resize(0);
    	rowOffset.resize(0);

    	for(RowIteratorConst it = begin(); it != end(); ++it)
		{
			bool rowSaved = false;

			for (ColIteratorConst cit = (*it).begin(); cit != (*it).end(); ++cit)
			{
				if ((*cit) != 0)
				{
					data.push_back((*cit));
					columns.push_back(cit.col());

					if(!rowSaved)
					{
						rowOffset.push_back(data.size()-1);
						rowSaved = true;
					}

				}
			}
		}

    	if (rowOffset.size() < 10)
    	{
    		std::cout << "Convert dense to sparse >>>>>>>>" << std::endl;

			for (unsigned int i = 0; i < data.size(); i++)
			{
				std::cout << data[i] << " ";
			}
			std::cout << std::endl;

			for (unsigned int i = 0; i < columns.size(); i++)
			{
				std::cout << columns[i] << " ";
			}
			std::cout << std::endl;

			for (unsigned int i = 0; i < rowOffset.size(); i++)
			{
				std::cout << rowOffset[i] << " ";
			}
			std::cout << std::endl << data.size() << " " << columns.size() << " " << rowOffset.size() << std::endl;
			std::cout << "<<<<<<<<<<<<<<<<<<" << std::endl;
    	}
    }

  private:
    std::vector<Row> entries;
};

//Template for vector multiplication
template<typename T1, typename T2>
std::vector<T2> operator*(const Matrix<T1>& a, const std::vector<T2>& x)
{
    if (x.size() != unsigned(a.cols()))
    {
        std::cerr << "Dimensions of vector " << x.size();
        std::cerr << " and matrix " << a.cols() << " do not match!";
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    };

    std::vector<T2> y(a.rows());
    for(typename Matrix<T1>::RowIteratorConst it = a.begin(); it != a.end(); ++it)
	{
    	y[it.row()] = 0.;

		for (typename Matrix<T1>::ColIteratorConst cit = (*it).begin(); cit != (*it).end(); ++cit)
		{
			y[it.row()] += (*cit) * x[cit.col()];
		}
	}

    return y;
};

template<typename T, typename T_>
Matrix<T> operator*(const Matrix<T>& a, T_ x)
{
    Matrix<T> output(a);
    output *= x;
    return output;
}

template<typename T, typename T_>
Matrix<T> operator*(T_ x, const Matrix<T>& a)
{
    Matrix<T> output(a);
    output *= x;
    return output;
}

template<typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
    Matrix<T> output(a);
    output += b;
    return output;
}
