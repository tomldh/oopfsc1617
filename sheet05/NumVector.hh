#ifndef NUMVECTOR_HH_
#define NUMVECTOR_HH_

#include <vector>
#include <cmath>

#define INHERIT

#ifdef INHERIT

class NumVector : private std::vector<double>
{
public:
	NumVector( int size_ );
	~NumVector();

	double& operator [](int i);
	double operator [] (int i) const;
	double norm() const;

private:
	int m_size;
	double* entries;
};

#else

class NumVector
{

public:
	NumVector( int size_ );
	~NumVector();

	double& operator [](int i);
	double operator [] (int i) const;
	double norm() const;

private:
	int m_size;
	double* entries;

};

#endif

#endif /* NUMVECTOR_HH_ */
