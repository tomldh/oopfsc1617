#include "NumVector.hh"

#ifdef INHERIT

NumVector::NumVector( int size_ )
{
	m_size = size_;
	entries = new double[size_];
}

NumVector::~NumVector()
{
	if (!entries)
	{
		delete [] entries;
	}
}

double& NumVector::operator [](int i)
{
	return entries[i];
}

double NumVector::operator [] (int i) const
{
	return entries[i];
}

double NumVector::norm() const
{
	double sum = 0.0;

	for (int i = 0; i < m_size; i++)
	{
		sum += (entries[i] * entries[i]);
	}

	return sqrt(sum);
}


#else

NumVector::NumVector( int size_ )
{
	m_size = size_;
	entries = new double[size_];
}

NumVector::~NumVector()
{
	if (!entries)
	{
		delete [] entries;
	}
}

double& NumVector::operator [](int i)
{
	return entries[i];
}

double NumVector::operator [] (int i) const
{
	return entries[i];
}

double NumVector::norm() const
{
	double sum = 0.0;

	for (int i = 0; i < m_size; i++)
	{
		sum += (entries[i] * entries[i]);
	}

	return sqrt(sum);
}

#endif
