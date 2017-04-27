#include "Utility.h"

// find greatest common divisor
int gcd(int a, int b)
{
	if (a==0 || a==b)
		return b;

	if (b==0)
		return a;

	if (a > b)
	{
		return gcd(a-b, b);
	}
	else
	{
		return gcd(a, b-a);
	}

}

// absolute value of int type
int iabs(int a)
{
	return (a>0) ? a : -a;
}


