#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>


template <class T>
class plusabs
{
public:
	const T operator()(const T& lhs, const T& rhs)
	{
		return std::plus<T>()(std::abs(lhs), std::abs(rhs));
	}
};

template <class T>
struct cmpabs
{
	bool operator()(const T& lhs, const T& rhs)
	{
		return std::less<T>()(std::abs(lhs), std::abs(rhs));
	}
};

template <class T>
struct elemabs
{
	void operator()(T& val)
	{
		val = std::abs(val);
	}
};

template <typename T>
class Norm
{
public:
	virtual double operator() (typename T::iterator first, typename T::iterator last) = 0;
	~Norm(){};
};

template <typename T>
class L1Norm : public Norm<T>
{
public:
	L1Norm(){};
	~L1Norm() {};

	virtual double operator() (typename T::iterator first, typename T::iterator last) override
	{
		//TODO: calculate L1 norm
		//return 0.0;
		return std::accumulate(first, last, 0.0, plusabs<typename T::value_type>());
	}

};


template <>
class L1Norm<std::vector<unsigned int>> : public Norm<std::vector<unsigned int>>
{
public:
	L1Norm(){};
	~L1Norm() {};

	virtual double operator() (std::vector<unsigned int>::iterator first, std::vector<unsigned int>::iterator last) override
	{
		//TODO: calculate L1 norm for "unsigned int"
		//return 0.0;
		return std::accumulate(first, last, 0.0);
	}


};

template <typename T>
class L2Norm : public Norm<T>
{
public:
	L2Norm(){};
	~L2Norm() {};

	virtual double operator() (typename T::iterator first, typename T::iterator last) override
	{
		//TODO: calculate L2 Norm
		//return 0.0;
		return std::inner_product(first, last, first, 0.0);
	}

};

template <typename T>
class InfNorm : public Norm<T>
{
public:
	InfNorm(){};
	~InfNorm() {};

	virtual double operator() (typename T::iterator first, typename T::iterator last) override
	{
		//TODO: calculate infinity Norm
		//return 0.0;
		typename T::iterator iter = std::max_element(first, last, cmpabs<typename T::value_type>());
		return (*iter);
	}

};



template <class M>
double frobeniusnorm(const M& matrix)
{
	double sum = 0.0;

	for (typename M::RowIteratorConst i = matrix.begin(); i != matrix.end(); i++)
	{
		for (typename M::ColIteratorConst j = (*i).begin(); j!= (*i).end(); j++)
		{
			sum += (*j) * (*j);
		}
	}

	return std::sqrt(sum);
}

int main()
{

	//TODO: Test implementation

	// vector data
	std::vector<unsigned int> v{3, 4};

	std::cout << "Test vector x=[3, 4]" << std::endl;

	// L2 norm
	L2Norm<std::vector<unsigned int>> l2norm;
	double l2Res = l2norm(v.begin(), v.end());
	std::cout << "\tResult of L2 norm is: " << l2Res << std::endl;

	// L1 norm
	L1Norm<std::vector<unsigned int>> l1norm;
	double l1Res = l1norm(v.begin(), v.end());
	std::cout << "\tResult of L1 norm is: " << l1Res << std::endl;

	// Infinity norm
	InfNorm<std::vector<unsigned int>> infnorm;
	double infRes = infnorm(v.begin(), v.end());
	std::cout << "\tResult of infinity norm is: " << infRes << std::endl;


	// vector data
	std::vector<int> v1{-3, 4};

	std::cout << "Test vector x=[-3, 4]" << std::endl;

	// L2 norm
	L2Norm<std::vector<int>> l2norm1;
	double l2Res1 = l2norm1(v1.begin(), v1.end());
	std::cout << "\tResult of L2 norm is: " << l2Res1 << std::endl;

	// L1 norm
	L1Norm<std::vector<int>> l1norm1;
	double l1Res1 = l1norm1(v1.begin(), v1.end());
	std::cout << "\tResult of L1 norm is: " << l1Res1 << std::endl;

	// Infinity norm
	InfNorm<std::vector<int>> infnorm1;
	double infRes1 = infnorm1(v1.begin(), v1.end());
	std::cout << "\tResult of infinity norm is: " << infRes1 << std::endl;

	/*

	std::vector<double> v1{1.0, 2.0, -3.0};
	std::vector<unsigned int> v2 {1, 2, 3};



	//L2 norm
	double l2 = std::inner_product(v1.begin(), v1.end(), v1.begin(), 0.0);
	std::cout << "L2 norm is: " << l2 << std::endl;

	L1Norm<std::vector<unsigned int>> l1norm;

	std::cout <<"L1 norm object: " << l1norm(v2.begin(), v2.end()) << "\n";


	//L1 norm
	double l1 = std::accumulate(v1.begin(), v1.end(), 0.0, plusabs<double>());
	std::cout << "L1 norm is: " << l1 << std::endl;

	//Infinity norm
	std::vector<double>::iterator linf = std::max_element(v1.begin(), v1.end(), cmpabs<double>());
	std::cout << "Infinity norm is " << std::abs(*linf) << std::endl;

	// container modified
	std::for_each(v1.begin(), v1.end(), elemabs<double>());



	std::sort(v1.begin(), v1.end());
	std::cout << "Infinity norm is " << std::abs(*(--v1.end())) << std::endl;
	std::cout << (*i) << " ";

	*/
	return 0;
}
