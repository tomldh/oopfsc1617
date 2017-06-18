#ifndef RATIONAL_HH_
#define RATIONAL_HH_

#include <cmath>
#include <iostream>

// class complete but immplementation standard ( C++17 ) greatest common divisor
// Just wanted to check if I can push stuff!
class Rational
{
    private:

        int denom;
        int num;

    public:

        Rational (int denom_, int num_): denom(denom_), num(num_)
        {
            if (denom == 0)
                throw std::string ("invalid denominator");

            if (denom < 0)
            {
                num = -num;
                denom = -denom;
            }

            reduce (); // is declared in private before gcd
        }

        int numerator() const
        {
            return num;
        }

        int denominator() const
        {
            return denom;
        }

        //Default
        Rational (): denom(1), num(1)
        {}

        //Whole
        Rational (int num_): denom(1) , num(num_)
        {}

        Rational& operator*= (const Rational& x)
        {
            num = num * x.num;
            denom = denom * x.denom;

            reduce ();
            return *this; // means content from this just stupid
        }

        Rational& operator+= (const Rational& x)
        {
            num = num * x.denom + x.num * denom;
            denom = x.denom * denom; //levels the denominator

            reduce ();
            return *this; // stupid again no container from container but content
        }

        Rational& operator-= (const Rational& x)
        {
            num = num * x.denom - x.num * denom;
            denom = x.denom * denom;

            reduce ();
            return *this; // again get use to it
        }

        Rational& operator/= (const Rational& x)
        {
            Rational xx (x.num,x.denom);
            *this *= xx;

            reduce ();
            return *this;
        }

        bool operator== (const Rational& x)
        {
            if (x.num*denom == x.denom*num)
                return 1;

            if (x.num == num && x.denom == denom)
                return 1;

            else
                return 0;
        }

    private:

        void reduce ()
        {
            int common = gcd (denom , num);

            num /= common;
            denom /= common;
        }


        int gcd (int o, int a) const
        {
            // checking none of them is 0 or negativ

            if (a == 0 || o == 0)
                return 1;

            a = std::abs(a);
            o = std::abs(o);

            int d = 0;

            while (a%2 == 0 && o%2 == 0)
            {
                o = o/2;
                a = a/2;
                d += 1;
            }

            while (o != a)
            {
                if (o%2 == 0)
                    o /= 2;

                else if (a%2 == 0)
                    a /= 2;

                else if (o > a)
                    o = (o - a)/2;

                else
                    a = (a - o)/2;
            }

            return o * std::pow (2,d);
        }
};

std::ostream& operator<< (std::ostream& str, const Rational& r)
{
	str << r.numerator() << "/" << r.denominator();
	return str;
}

// free operator

Rational operator* (const  Rational& r , const Rational& s)
{
    Rational t = r;
    t *= s;

    return t;
}

Rational operator+ (const Rational& r , const Rational& s)
{
    Rational t = r;
    t += s;

    return t;
}

Rational operator- (const Rational& r , const Rational& s)
{
    Rational t = r;
    t -= s;

    return t;
}

Rational operator/ (const Rational& r , const Rational& s)
{
    Rational t = r;
    t /= s;
    return t;
}


#endif /* RATIONAL_HH_ */
