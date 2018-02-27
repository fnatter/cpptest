/*
 * RationalNumber.cpp
 *
 *  Created on: 30.12.2017
 *      Author: felix
 */

#include "RationalNumber.h"

using namespace std;

long RationalNumber::_ggt(long a, long b)
{
	if (a == 0)
	{
		return b;
	}
	else
	{
		while (b != 0)
		{
			if (a > b)
			{
				a = a - b;
			}
			else
			{
				b = b - a;
			}
		}
		return a;
	}
}

void RationalNumber::print(ostream& out) const
{
  out << num << "/" << den;
}

void RationalNumber::normalize()
{
	long ggt = _ggt(num, den);
	num /= ggt;
	den /= ggt;
}

RationalNumber RationalNumber::operator+(const RationalNumber& b) const
{
	RationalNumber result = RationalNumber(num * b.den + b.num * den, den * b.den);
	result.normalize();
	return result;
}

RationalNumber RationalNumber::operator-(const RationalNumber& b) const
{
	RationalNumber result = RationalNumber(num * b.den - b.num * den, den * b.den);
	result.normalize();
	return result;
}

RationalNumber RationalNumber::operator*(const RationalNumber& b) const
{
	RationalNumber result = RationalNumber(num * b.num, den * b.den);
	result.normalize();
	return result;
}

RationalNumber RationalNumber::operator/(const RationalNumber& b) const
{
	RationalNumber result = RationalNumber(num * b.den, den * b.num);
	result.normalize();
	return result;
}

RationalNumber::RationalNumber(long _num, long _den)
	:num(_num), den(_den)
{
}

RationalNumber::RationalNumber() : num(0L), den(0L)
{
}

RationalNumber::~RationalNumber()
{
}

istream& operator>>(istream& in, RationalNumber& n)
{
	int numerator;
	int denominator = 1;

	in >> numerator;

	char slash;
	in.get(slash);

	if (!in.eof())
	{
		if (slash == '/')
			in >> denominator;
		else
			in.putback(slash);
	}

	n = RationalNumber(numerator, denominator);

	return in;
}
