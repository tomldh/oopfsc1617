#include <vector>
#include <iostream>
#include <cmath>

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

	NumVector v(3);
	v[0]=1; v[1]=3, v[2]=4;
	const NumVector& w=v;
	std::cout<<"norm is " << w.norm() << std::endl;
	std::cout<<"vector is ["<<w[0]<<", "<<w[1]<<", "<<w[2]<<"]"<< std::endl;

#else

	NumVector v(3);
	v.resize(2); // must be hidden, just like other methods of std::vector!
	vectorTest(v); // this should also lead to a compiler error!

#endif

}
