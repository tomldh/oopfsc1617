#include <stdio.h>
#include <vector>
#include "Rational.h"

void print(Rational &m_rational)
{
	printf("%d/%d\n", m_rational.numerator(), m_rational.denominator());
}

void printFarey(int n, std::vector<Rational> &seq)
{
	printf("F%d = ( ", n);

	for (unsigned int i = 0; i < seq.size(); i++)
	{
		printf("%d/%d ", seq[i].numerator(), seq[i].denominator());
	}

	printf(")\n");
}

std::vector<Rational> Farey(int N)
{
	std::vector<Rational> seq; //to store sequence from the previous
	std::vector<Rational> seq_new; //to store the to-be-generated sequence

	//initialization
	seq.resize(0);
	seq_new.resize(0);

	//base case
	if (N == 0)
		return seq;

	if (N == 1)
	{
		seq_new.push_back(Rational(0,1));
		seq_new.push_back(Rational(1,1));

		printFarey(N, seq_new);

		return seq_new;
	}

	// retrieve last sequence
	seq = Farey(N-1);

	// add new elements
	for (unsigned int i = 0; i < seq.size()-1; i++)
	{
		Rational lhs = seq[i];
		Rational rhs = seq[i+1];

		seq_new.push_back(seq[i]);

		if ((lhs.denominator()+rhs.denominator()) == N)
		{
			seq_new.push_back(Rational(lhs.numerator()+rhs.numerator(), N));
		}
	}

	seq_new.push_back(seq[seq.size()-1]);

	printFarey(N, seq_new);

	return seq_new;

}

int main(int argc, char* argv[])
{
	Rational f1(0, 1);
	Rational f2(0, 1);

	print(f1);
	print(f2);

	Rational f = f1 + 6;

	print(f);

	printf("%d\n", gcd(2, 18));

	Farey(6);

	return 0;

}



