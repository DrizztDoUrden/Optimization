#include <algorithm>
#include <iostream>
#include "Utilities.h"



void ValidateResult(LinearFunction function, double result, double test, double eps)
{
	auto delta = function(result) - function(test);
	auto cDelta = result - test;

	if (abs(cDelta) < eps || abs(delta) < eps)
		cout << "  Valid";
	else
		cout << ">>Error<<\td/eps=" << delta / eps << ", cd/eps=" << cDelta / eps;
}

void ValidateResult(NonlinearFunction function, const double result[], const double test[], double eps, size_t size)
{
	auto coordinatesEqual = true;
	auto delta = function(result) - function(test);
	auto cDelta = .0;

	for (size_t coordinate = 0; coordinatesEqual && coordinate < size; coordinate++)
	{
		auto ciDelta = abs(result[coordinate] - test[coordinate]);

		coordinatesEqual &= ciDelta < eps;
		cDelta += ciDelta;
	}

	if (abs(delta) < eps || coordinatesEqual)
		cout << "  Valid";
	else
		cout << ">>Error<<\td/eps=" << delta / eps << ", cd/eps=" << cDelta / eps;
}

double Derivate(LinearFunction function, double eps, double point)
{
	return (function(point + eps) - function(point)) / eps;
}

LinearFunction DerivateFunction(LinearFunction function, double eps)
{
	return [function, eps](double point) { return Derivate(function, eps, point); };
}

double PartialDerivate(NonlinearFunction function, double eps, const double point[], size_t coordinate, size_t size)
{
	auto epsPoint = static_cast<double*>(alloca(sizeof(double) * size));

	for (size_t i = 0; i < size; i++)
		epsPoint[i] = point[i];

	epsPoint[coordinate] += eps;

	auto result = (function(epsPoint) - function(point)) / eps;

	return result;
}

function<double(const double [], size_t)> PartialDerivateFunction(NonlinearFunction function, double eps, size_t size)
{
	return [function, eps, size](const double point[], size_t coordinate) { return PartialDerivate(function, eps, point, coordinate, size); };
}

vector<double> Gradient(NonlinearFunction function, double eps, const double point[], size_t size)
{
	vector<double> grad(size);

	for (size_t coordinate = 0; coordinate < size; coordinate++)
		grad[coordinate] = PartialDerivate(function, eps, point, coordinate, size);

	return grad;
}

function<vector<double>(const double [])> GradientFunction(NonlinearFunction function, double eps, size_t size)
{
	return [function, eps, size](const double point[]) { return Gradient(function, eps, point, size); };
}

vector<double> InvGradient(NonlinearFunction function, double eps, const double point[], size_t size)
{
	vector<double> grad(size);

	for (size_t coordinate = 0; coordinate < size; coordinate++)
		grad[coordinate] = -PartialDerivate(function, eps, point, coordinate, size);

	return grad;
}

function<vector<double>(const double[])> InvGradientFunction(NonlinearFunction function, double eps, size_t size)
{
	return [function, eps, size](const double point[]) { return InvGradient(function, eps, point, size); };
}

vector<double> DelinearizeCoordinate(const double start[], const double direction[], size_t size, double point)
{
	vector<double> x(size);

	for (size_t coordinate = 0; coordinate < size; coordinate++)
		x[coordinate] = start[coordinate] + direction[coordinate] * point;

	return x;
}

function<vector<double>(double)> DelinearizeCoordinateFunction(const double start[], const double direction[], size_t size)
{
	return [start, direction, size](double point) { return DelinearizeCoordinate(start, direction, size, point); };
}

LinearFunction LinearizeFunction(NonlinearFunction original, const double start[], const double direction[], size_t size)
{
	return [original, start, direction, size](double point)
	{
		auto x = DelinearizeCoordinate(start, direction, size, point);

		return original(x.data());
	};
}

double MinimizeLinearFunction(LinearMinimizationMethod linearMinimization, LinearFunction function, size_t size, double eps, unsigned int& svenOps, unsigned int& minOps, unsigned int svenLimit, unsigned int minLimit)
{
	double intStart, intEnd;

	Sven(function, 0, eps, intStart, intEnd, svenLimit, svenOps);
	return linearMinimization(function, intStart, intEnd, eps, minLimit, minOps);
}

vector<double> MapCoordinates(const double start[], double** basis, size_t size, size_t newSize, const double point[])
{
	vector<double> x(size);

	for (size_t i = 0; i < size; i++)
	{
		x[i] = start[i];

		for (size_t j = 0; j < newSize; j++)
			x[i] += basis[j][i] * point[j];
	}

	return x;
}

NonlinearFunction MapFunction(NonlinearFunction original, const double start[], double** basis, size_t size, size_t newSize)
{
	return [original, start, basis, size, newSize](const double point[])
	{
		auto x = MapCoordinates(start, basis, size, newSize, point);

		return original(x.data());
	};
}

vector<double> MinimizeLine(LinearMinimizationMethod linearMinimization, NonlinearFunction original, const double start[], const double direction[], size_t size, double eps, unsigned& svenOps, unsigned& minOps, unsigned svenLimit, unsigned minLimit)
{
	auto function1d = LinearizeFunction(original, start, direction, size);
	auto linResult = MinimizeLinearFunction(linearMinimization, function1d, size, eps, svenOps, minOps, svenLimit, minLimit);

	return DelinearizeCoordinate(start, direction, size, linResult);
}
