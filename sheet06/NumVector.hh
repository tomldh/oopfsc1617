#ifndef NUMVECTOR_HH_
#define NUMVECTOR_HH_

#include <vector>
#include <cmath>
#include "exceptions.hh"


class NumVector
{

public:
	NumVector( size_t size_ );
	~NumVector();

    double& operator [] ( size_t i );
    double operator [] ( size_t i ) const;
	double norm() const;
	size_t getSize() const;

private:
	std::vector<double> entries;

};

double operator * (const NumVector& lhs, const NumVector& rhs);

NumVector::NumVector( size_t size_ ) : entries(size_)
{

}

NumVector::~NumVector()
{
    entries.clear();
}

double& NumVector::operator [] ( size_t i )
{
	if ( i < 0 || i >= entries.size())
	{
		throw OutOfBoundsException("Index out of bounds!");
	}

    return entries[i];
}

double NumVector::operator [] ( size_t i ) const
{
	if ( i < 0 || i >= entries.size())
	{
			throw OutOfBoundsException("Index out of bounds!");
	}

	return entries[i];
}

double NumVector::norm() const
{
    double sum = 0.0;

    for (unsigned int i = 0; i < entries.size(); i++)
    {
        sum += (entries[i] * entries[i]);
    }

    return sqrt(sum);
}

size_t NumVector::getSize() const
{
	return entries.size();
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

#endif /* NUMVECTOR_HH_ */
