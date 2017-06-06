#ifndef NUMVECTORINHERIT_HH_
#define NUMVECTORINHERIT_HH_

#include <vector>
#include <cmath>

class NumVector : private std::vector<double>
{

public:
	NumVector( size_t size_ );

    double& operator [] ( size_t i );
    double operator [] ( size_t i ) const;
	double norm() const;
	size_t NumVector::getSize() const;

};

double operator * (const NumVector& lhs, const NumVector& rhs);

NumVector::NumVector( size_t size_ ) : std::vector<double> (size_)
{

}

double& NumVector::operator [] ( size_t i )
{
	if ( i < 0 || i >= size())
	{
		throw OutOfBoundsException("Index out of bounds!");
	}

	return std::vector<double>::operator[](i);

}

double NumVector::operator [] ( size_t i ) const
{
	if ( i < 0 || i >= size())
	{
		throw OutOfBoundsException("Index out of bounds!");
	}

    return std::vector<double>::operator[](i);
}

double NumVector::norm() const
{
    double sum = 0.0;

    for (unsigned int i = 0; i < size(); i++)
    {
        sum += ((*this)[i] * (*this)[i]);
    }

    return sqrt(sum);
}

size_t NumVector::getSize() const
{
	return std::vector<double>::size();
}

double operator * (const NumVector& lhs, const NumVector& rhs)
{
	if (lhs.getSize() != rhs.getSize())
	{
		throw IncompatibleDimensionException("Incompatible dimension!");
	}

	double sum = 0.0;

	for (unsigned int i = 0; i < lhs.getSize(); i++)
	{
		sum += (lhs[i] * rhs[i]);
	}

	return sum;
}


#endif /* NUMVECTORINHERIT_HH_ */

