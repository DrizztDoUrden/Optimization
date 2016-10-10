#include "TestFunctions1.h"
#include <algorithm>
#include "Counters.h"



double F1(double x)
{
	FunctionCalled();
	return 2 * x*x + 3 * exp(-x);
}

double F2(double x)
{
	FunctionCalled();
	return -exp(-x)*log(x);
}

double F3(double x)
{
	FunctionCalled();
	return 2 * x*x - exp(x);
}

double F4(double x)
{
	FunctionCalled();
	auto x2 = x*x;
	auto x3 = x2*x;
	auto x4 = x3*x;

	return x4 - 14 * x3 + 60 * x2 - 70 * x;
}

double F5(double x)
{
	FunctionCalled();
	auto x3 = x*x*x;
	auto x4 = x3*x;

	if (x < 0)
	{
		return 4 * x3 + 3 * x4;
	}

	return 4 * x3 - 3 * x4;
}

double F6(double x)
{
	FunctionCalled();
	return x*x + 2 * x;
}

double F7(double x)
{
	FunctionCalled();
	return 2 * x*x + 16 / x;
}

double F8(double x)
{
	FunctionCalled();
	auto x2 = x*x;
	auto x3 = x2*x;
	auto t = 10 * x3 + 3 * x2 + x + 5;

	return t * t;
}

double F9(double x)
{
	FunctionCalled();
	auto x2 = x*x;
	auto x3 = x2*x;

	return 3 * x2 + 12 / x3 - 5;
}



LinearFunction functions1[] =
{
	F1,
	F2,
	F3,

	F4,
	F5,
	F6,
	
	F7,
	F8,
	F9,
};

double starts1[] =
{
	1,
	0,
	1,

	2,
	0.4,
	4,

	1,
	2,
	0.5,
};

double epsPows1[] =
{
	3,
	4,
	3,

	2,
	3,
	2,

	2,
	2,
	2,
};

double epss1[] =
{
	pow(10, -epsPows1[0]),
	pow(10, -epsPows1[1]),
	pow(10, -epsPows1[2]),

	pow(10, -epsPows1[3]),
	pow(10, -epsPows1[4]),
	pow(10, -epsPows1[5]),

	pow(10, -epsPows1[6]),
	pow(10, -epsPows1[7]),
	pow(10, -epsPows1[8]),
};

double mins1[] =
{
	0.469150,
	1.763223,
	0.357403,

	0.780884,
	-1.000000,
	-1.000000,

	1.587401,
	-0.859902,
	1.430969,
};
