#ifndef NUMVECTORINHERIT_HH_
#define NUMVECTORINHERIT_HH_

#include <vector>
#include <cmath>

class NumVector : private std::vector<double>
{

public:
	NumVector( int size_ );

    double& operator [] ( int i );
    double operator [] ( int i ) const;
	double norm() const;

};

NumVector::NumVector( int size_ ) : std::vector<double> (size_)
{

}

double& NumVector::operator [] ( int i )
{
    return std::vector<double>::operator[](i);
}

double NumVector::operator [] ( int i ) const
{
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

#endif /* NUMVECTORINHERIT_HH_ */

