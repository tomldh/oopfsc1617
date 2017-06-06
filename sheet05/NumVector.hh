#ifndef NUMVECTOR_HH_
#define NUMVECTOR_HH_

#include <vector>
#include <cmath>


class NumVector
{

public:
	NumVector( int size_ );
	~NumVector();

    double& operator [] ( int i );
    double operator [] ( int i ) const;
	double norm() const;

private:
	std::vector<double> entries;

};

NumVector::NumVector( int size_ ) : entries(size_)
{

}

NumVector::~NumVector()
{
    entries.clear();
}

double& NumVector::operator [] ( int i )
{
    return entries[i];
}

double NumVector::operator [] ( int i ) const
{
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

#endif /* NUMVECTOR_HH_ */
