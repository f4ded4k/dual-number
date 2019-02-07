#pragma once

#include <iostream>
#include <iomanip>
#include "Dual.h"

using namespace std;

int main()
{
	cout << setprecision(6) << fixed;

	Dual<> x = { 5, 1 }, y = 14.9; // with respect to the variable 'x'

	auto z = x * y + sin(x) - pow(15.78,x) / sqr(y) + log(x*y, 12);

	cout << z.getDx() << endl;

	return 0;
}