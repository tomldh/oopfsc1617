#include <vector>
#include <iostream>
#include <memory>
#include <string>


template <typename T>
class Norm
{
public:

	virtual double operator() (typename T::iterator first, typename T::iterator last) = 0;

	~Norm()=default;
};

template <typename T>
class L1norm : public Norm<T>
{
public:
	L1norm(){};

	virtual double operator() (typename T::iterator first, typename T::iterator last) override
	{
		return 1.0;
	}

	~L1norm() {};
};

template <>
class L1norm<std::vector<int>> : public Norm<std::vector<int>>
{
public:
	L1norm(){};

	virtual double operator() (std::vector<int>::iterator first, std::vector<int>::iterator last) override
	{
		return 10.0;
	}

	~L1norm() {};
};


int main()
{

	L1norm<std::vector<int> > norm1;

	std::vector<int> v{1,2,3,4,5};

	std::vector<double> v2{1.2,2,3,4,5};

	std::cout << norm1(v.begin(), v.end()) << std::endl;

	Norm<std::vector<int> >& nb = norm1;

	L1norm<std::vector<int> >* p = dynamic_cast<L1norm<std::vector<int> >*> (&nb);

	if (p==0)
		std::cout << "cannot cast" << std::endl;
	else
		std::cout << "cast successfully" <<std::endl;

	L1norm<std::vector<double> > norm2;

	std::cout << norm2(v2.begin(), v2.end()) << std::endl;


	std::shared_ptr<std::string> p1;
	auto p6 = std::make_shared<std::string>();

	if (p1 == p6)
		std::cout << "same pointer" << std::endl;
	else
		std::cout << "different" <<std::endl;


	return 0;
}

