#include "TestFunctions3.h"
#include "Utilities.h"
#include "Counters.h"



double F19(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto t1 = x2 - x1 * x1;
	auto t2 = 1 - x1;

	return 100 * t1 * t1 + t2 * t2;
}

double F20(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto x3 = x[2];
	auto t1 = x1 - 1;
	auto t2 = x2 - 3;
	auto t3 = x3 + 5;

	return t1 * t1 + t2 * t2 + 4 * t3 * t3;
}

double F21(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];

	return 8 * x1 * x1 + 4 * x1 * x2 + 5 * x2 * x2;
}

double F22(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto t1 = x1 - 5;
	auto t2 = x2 - 6;

	return 4 * t1 * t1 + t2 * t2;
}

double F23(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto t1 = x2 - x1 * x1;
	auto t2 = 1 - x1;

	return t1 * t1 + t2 * t2;
}

double F24(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto t1 = x2 - x1 * x1;
	auto t2 = 1 - x1 * x1;

	return t1 * t1 + 100 * t2 * t2;
}

double F25(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];
	auto x3 = x[2];
	auto t1 = x1 - 4;
	auto t2 = x2 + 3;
	auto t3 = 2 * x3 + 1;

	return 3 * t1 * t1 + 5 * t2 * t2 + 7 * t3 * t3;
}

double F26(const double x[])
{
	FunctionCalled();
	auto x1 = x[0];
	auto x2 = x[1];

	return x1 * x1 * x1 + x2 * x2 - 3 * x1 - 2 * x2 + 2;
}



NonlinearFunction functions3[NumberOfFunctions3] =
{
	F19,
	F20,
	F21,
	F22,
	F23,
	F24,
	F25,
	F26,
};

size_t dims3[NumberOfFunctions3]
{
	2,
	3,
	2,
	2,

	2,
	2,
	3,
	2,
};

size_t startsNumbers3[NumberOfFunctions3] =
{
	3,
	1,
	1,
	2,

	3,
	2,
	2,
	2,
};

double epss3[NumberOfFunctions3] =
{
	pow(10, -4),
	pow(10, -4),
	pow(10, -4),
	pow(10, -4),

	pow(10, -4),
	pow(10, -4),
	pow(10, -4),
	pow(10, -4),
};

double *mins3[NumberOfFunctions3] =
{
	new double[dims3[0]] {1, 1},
	new double[dims3[1]] {1, 3, -5},
	new double[dims3[2]] {0, 0},
	new double[dims3[3]] {5, 6},

	new double[dims3[4]] {1, 1},
	new double[dims3[5]] {1, 1},
	new double[dims3[6]] {4, -3, -0.5},
	new double[dims3[7]] {1, 1},
};

double **starts3[NumberOfFunctions3]
{
	new double*[startsNumbers3[0]]
	{
		new double[dims3[0]]{ -1.2, 1 },
		new double[dims3[0]]{ 1.5, 2 },
		new double[dims3[0]]{ -2, -2 },
	},

	new double*[startsNumbers3[1]]
	{
		new double[dims3[1]]{ 4, -1, 2 },
	},

	new double*[startsNumbers3[2]]
	{
		new double[dims3[2]]{ 10, 10 },
	},

	new double*[startsNumbers3[3]]
	{
		new double[dims3[3]]{ 8, 9 },
		new double[dims3[3]]{ 0, 0 },
	},

	new double*[startsNumbers3[4]]
	{
		new double[dims3[4]]{ 1.5, 2 },
		new double[dims3[4]]{ 0, 0 },
		new double[dims3[4]]{ -1.2, 1 },
	},

	new double*[startsNumbers3[5]]
	{
		new double[dims3[5]]{ 1.5, 2 },
		new double[dims3[5]]{ 1, 2 },
	},

	new double*[startsNumbers3[6]]
	{
		new double[dims3[6]]{ 2, -2, -2 },
		new double[dims3[6]]{ 0, 0, 0 },
	},

	new double*[startsNumbers3[7]]
	{
		new double[dims3[7]]{ 0, 0 },
		new double[dims3[7]]{ -1, -1 },
	},
};
