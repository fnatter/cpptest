/*
 * RationalNumber.h
 *
 *  Created on: 30.12.2017
 *      Author: felix
 */

#ifndef RATIONALNUMBER_H_
#define RATIONALNUMBER_H_

#include <ostream>
#include <istream>

class RationalNumber
{
private:
	long num;
	long den;

	static long _ggt(long a, long b);

public:
	void normalize();
	void print(std::ostream& out) const;

	RationalNumber operator+(const RationalNumber& b) const;
	RationalNumber operator-(const RationalNumber& b) const;
	RationalNumber operator*(const RationalNumber& b) const;
	RationalNumber operator/(const RationalNumber& b) const;

	RationalNumber(long num, long den);
	RationalNumber();
	virtual ~RationalNumber();
};

inline std::ostream& operator<<(std::ostream& out, const RationalNumber& n)
{
	n.print(out);
	return out;
}

std::istream& operator>>(std::istream& in, RationalNumber& n);

#endif /* RATIONALNUMBER_H_ */
