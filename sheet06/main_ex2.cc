#include <vector>
#include <iostream>
#include <cmath>
#include <exception>

#define COMPILE
//#define USE_INHERIT

#ifdef USE_INHERIT
#include "NumVectorInherit.hh"
#else
#include "NumVector.hh"
#endif


#ifndef COMPILE

void vectorTest(std::vector<double>& v){}

#endif

int main(){



#ifdef COMPILE
	try
	{
		NumVector v(3);
		v[0]=1; v[1]=3, v[2]=4;
		const NumVector& w=v;
		std::cout<<"norm is " << w.norm() << std::endl;
		std::cout<<"vector is ["<<w[0]<<", "<<w[1]<<", "<<w[2]<<"]"<< std::endl;

		v[3] = 5;

	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		NumVector v1(3);
		NumVector v2(3);
		NumVector v3(2);
		v1[0]=1; v1[1]=3, v1[2]=4;
		v2[0]=1; v2[1]=3, v2[2]=4;
		v3[0]=1; v3[1]=3;

		std::cout << "Scalar Product of v1 and v2 is " << v1*v2 << std::endl;
		std::cout << "Scalar product of v1 and v3 is " << v1*v3 << std::endl;

	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

#else

	NumVector v(3);
	v.resize(2); // must be hidden, just like other methods of std::vector!
	vectorTest(v); // this should also lead to a compiler error!

#endif



}
