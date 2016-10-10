#include "TestFunctions2.h"
#include "Utilities.h"
#include "Counters.h"



double F10(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];

	return x1 * x1 + 3 * x2 * x2 + 2 * x1 * x2;
}

double F11(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto t1 = x2 - x1*x1;
	auto t2 = 1 - x1;

	return 100 * t1 * t1 + t2 * t2;
}

double F12(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];

	return -12 * x2 + 4 * x1 * x1 + 4 * x2 * x2 - 4 * x1 * x2;
}

double F13(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto t1 = x1 - 2;
	auto t2 = x1 - 2 * x2;

	return t1 * t1 * t1 * t1 + t2 * t2;
}

double F14(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto t1 = x1 - 5;
	auto t2 = x2 - 6;

	return 4 * t1 * t1 + t2 * t2;
}

double F15(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto t1 = x1 - 2;
	auto t2 = x1 - 2 * x2;

	return t1 * t1 * t1 * t1 + t2 * t2;
}

double F16(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto x2_2 = x2*x2;

	return 2 * x1 * x1 * x1 + 4 * x1 * x2_2 * x2 - 10 * x1 * x2 + x2_2;
}

double F17(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];

	return 8 * x1 * x1 + 4 * x1 * x2 + 5 * x2 * x2;
}

double F18(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto t1 = x1 - 5;
	auto t2 = x2 - 6;

	return 4 * t1 * t1 + t2 * t2;
}



NonlinearFunction functions2[] =
{
	F10,
	F11,
	F12,

	F13,
	F14,
	F15,

	F16,
	F17,
	F18,
};

double starts2[NumberOfFunctions2][Dims2] =
{
	{ 1, 1 },
	{ -1, 0 },
	{ -0.5, 1 },

	{ 0, 3 },
	{ 8, 9 },
	{ 0, 3 },

	{ 5, 2 },
	{ 10, 16 },
	{ 8, 9 },
};

double epss2[NumberOfFunctions2] =
{
	pow(10, -4),
	pow(10, -4),
	pow(10, -4),

	pow(10, -4),
	pow(10, -4),
	pow(10, -4),

	pow(10, -4),
	pow(10, -4),
	pow(10, -4),
};

double directions2[NumberOfFunctions2][Dims2] =
{
	{ 2, 3 },
	{ 5, 1 },
	{ 1, 0 },

	{ 1, 0 },
	{ 1, 0 },
	{ 44, -24.1 },

	{ 0, 1 },
	{ Gradient(functions2[7], epss2[7], starts2[7], Dims2)[0], Gradient(functions2[7], epss2[7], starts2[7], Dims2)[1] },
	{ 0, 1 },
};

double mins2[NumberOfFunctions2][Dims2] =
{
	{ 0.2558, -0.1163 },
	{ -0.3413, 0.13172 },
	{ 0.5, 1 },

	{ 3.13, 3.00 },
	{ 5, 9 },
	{ 2.7, 1.51 },

	{ 5, 0.896356 },
	{ -2.938, 4.4479 },
	{ 8, 6 },
};
