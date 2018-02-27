//============================================================================
// Name        : cpptest1.cpp
// Author      : Felix Natter
// Version     :
// Copyright   : GPL-3+...
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <memory>
#include <sstream>
#include "RationalNumber.h"

using namespace std;

namespace felix {
	enum Operator { plus, minus, multiply, divide };
}

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		cout << "Syntax: <rational> <operator> <rational>" << endl;
		return 1;
	}

	istringstream input;

	RationalNumber r1;
	input.str(argv[1]);
	input >> r1;

	felix::Operator op;
	string opString = string(argv[2]);
	if (opString == "+" || opString == "plus")
	{
		op = felix::plus;
	}
	else if (opString == "-" || opString == "minus")
	{
		op = felix::minus;
	}
	else if (opString == "*" || opString == "multiply")
	{
		op = felix::multiply;
	}
	else if (opString == "/" || opString == "divide")
	{
		op = felix::divide;
	}

	RationalNumber r2;
	input.clear();
	input.str(argv[3]);
	input >> r2;

	RationalNumber result;
	cout << r1 << " " << opString << " " << r2 << " = ";

	switch(op)
	{
	case felix::plus:
		result = r1 + r2;
		break;
	case felix::minus:
		result = r1 - r2;
		break;
	case felix::multiply:
		result = r1 * r2;
		break;
	case felix::divide:
		result = r1 / r2;
		break;
	}
	cout << result << endl;

	return 0;
}
