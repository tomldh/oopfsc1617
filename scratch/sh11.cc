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

/*
template<class M, class T>
void gaussSeidel(const M& A, const std::vector<T>& b, std::vector<T>& x, int maxIter)
{
    // initialize x with zero values
    std::fill(x.begin(), x.end(), 0);
    
    while(maxIter--)
    {
        for (typename M::RowIteratorConst riter = A.begin(); riter != A.end(); ++riter)
        {
            unsigned int k = riter.row();
            T sum = 0;
            T a_kk = 1;
            for (typename M::ColIteratorConst citer = (*riter).begin(); citer != (*riter).end(); ++citer)
            {
                unsigned int i = citer.col();
                if (k == i)
                {
                    a_kk = (*citer);    
                }
                else
                {
                    sum += (*citer) * x[i];
                }
            }
            x[k] = (b[k] - sum) / a_kk;
        }
        
        //std::cout << "iteration " << m << " " << x[0] << " " << x[1] << " " << x[2] << std::endl;
    }

}
*/
	
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
	
	/*
	Matrix<double> A(3,3,0.);
	
	A[0][0] = 2; A[0][1] = 1; A[0][2] = 0;
	A[1][0] = 1; A[1][1] = 3; A[1][2] = 2;
	A[2][0] = 0; A[2][1] = 1; A[2][2] = -4;
	
	std::vector<double> x{1,1,1};
	std::vector<double> b{1,2,3};
	
	gaussSeidel<Matrix<double>, double>(A, b, x, 2);
	
	std::cout << x[0] << " " << x[1] << " " << x[2] << std::endl;
	*/

	return 0;
}

