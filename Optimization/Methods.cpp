#include "Methods.h"
#include <algorithm>
#include "Utilities.h"



void Invert(double v[], size_t size)
{
	for (size_t i = 0; i < size; i++)
		v[i] = -v[i];
}

double Length(const double v[], size_t size)
{
	auto result = .0;

	for (size_t i = 0; i < size; i++)
		result += v[i] * v[i];

	return sqrt(result);
}

void Substract(double left[], const double right[], size_t size)
{
	for (size_t i = 0; i < size; i++)
		left[i] -= right[i];
}

void Sven(LinearFunction function, double start, double step, double& intervalStart, double& intervalEnd, unsigned int limit, unsigned int& operations)
{
	double prev;
	auto cur = start;
	auto next = cur + step;
	auto swapped = false;
	auto fNext = function(next);
	auto fCur = function(cur);

	operations = 1;

	if (fNext > fCur)
	{
		swapped = true;
		step = -step;
		next = cur + step;
		fNext = function(next);
	}

	do
	{
		if (++operations > limit)
			throw - 1;

		step = step * 2;

		prev = cur;
		cur = next;
		next = cur + step;
		fCur = fNext;
		fNext = function(next);
	} while (fNext < fCur);

	if (swapped)
	{
		intervalStart = next;
		intervalEnd = prev;
	}
	else
	{
		intervalStart = prev;
		intervalEnd = next;
	}
}

double Fibonachi(LinearFunction function, double start, double end, double eps, unsigned int limit, unsigned int& operations)
{
	double fibs[100];
	auto n = 1;
	auto fibLim = (end - start) / eps;

	operations = 0;

	fibs[0] = fibs[1] = 1;
	while (fibs[n++] < fibLim)
		fibs[n] = fibs[n - 1] + fibs[n - 2];

	auto d = (end - start) * fibs[n - 3] / fibs[n - 1];
	auto x1 = start + d;
	auto x2 = end - d;
	auto y1 = function(x1);
	auto y2 = function(x2);

	while (n-- > 2)
	{
		if (++operations > limit)
			throw - 1;

		if (y1 < y2)
		{
			end = x2;
			x2 = x1;
			x1 = start + (end - x2);

			y2 = y1;
			y1 = function(x1);
		}
		else
		{
			start = x1;
			x1 = x2;
			x2 = end - (x1 - start);

			y1 = y2;
			y2 = function(x2);
		}
	}

	return (start + end) / 2;
}

double Dichotomia(LinearFunction function, double start, double end, double eps, unsigned int limit, unsigned int &operations)
{
	auto mid = (start + end) / 2;

	operations = 0;

	while (end - start > eps)
	{
		if (++operations > limit)
			throw - 1;

		auto mida = (start + mid) / 2;
		auto midb = (end + mid) / 2;
		auto ymida = function(mida);
		auto ymidb = function(midb);

		if (ymida < ymidb)
		{
			end = mid;
			mid = mida;
		}
		else
		{
			start = mid;
			mid = midb;
		}
	}

	return (start + end) / 2;
}

double PauelDivisor(double fA, double fB, double fC, double a, double b, double c)
{
	return 2 * (fA * (b - c) + fB * (c - a) + fC * (a - b));
}

double Pauel(LinearFunction function, double start, double end, double eps, unsigned int limit, unsigned int &operations)
{
	auto mid = (start + end) / 2;
	auto fStart = function(start);
	auto fEnd = function(end);
	auto fMid = function(mid);
	auto aprox = PauelDivisor(fStart, fMid, fEnd, start * start, mid * mid, end * end) / PauelDivisor(fStart, fMid, fEnd, start, mid, end);
	auto fAprox = function(aprox);

	operations = 1;

	while (abs((aprox - mid) / mid) > eps || abs((fAprox - fMid) / fMid) > eps)
	{
		if (fMid < fAprox)
		{
			(mid < aprox ? end : start) = aprox;
		}
		else
		{
			(mid < aprox ? start : end) = mid;
			mid = aprox;
		}

		fStart = function(start);
		fEnd = function(end);
		fMid = function(mid);

		aprox = (fStart - fMid) * (mid - end) * (end - start)
			/ PauelDivisor(fStart, fMid, fEnd, start, mid, end)
			+ (start + mid) / 2;

		fAprox = function(aprox);

		if (operations++ > limit)
			throw - 1;
	}

	return (mid + aprox) / 2;
}

double Bolcano(LinearFunction function, double start, double end, double eps, unsigned int limit, unsigned int& operations)
{
	auto dFunction = DerivateFunction(function, eps);
	auto mid = (start + end) / 2;
	auto dMid = dFunction(mid);

	operations = 0;

	while (abs(dMid) > eps || abs(end - start) > eps)
	{
		if (dMid > 0)
			end = mid;
		else
			start = mid;

		mid = (start + end) / 2;
		dMid = dFunction(mid);

		if (operations++ > limit)
			throw - 1;
	}

	return mid;
}

double Davidon(LinearFunction function, double start, double end, double eps, unsigned int limit, unsigned int& operations)
{
	double d, y;
	auto dFunction = DerivateFunction(function, eps);

	operations = 0;

	do
	{
		auto z = dFunction(start) + dFunction(end) + 3 * (function(start) - function(end)) / (end - start);
		auto w = sqrt(z*z - dFunction(start)*dFunction(end));
		y = (z - dFunction(start) + w) / (dFunction(end) - dFunction(start) + 2 * w);

		if (y < 0)
			d = start;
		else
			if (y > 1)
				d = end;
			else
				d = start + y*(end - start);

		if (dFunction(d) < 0)
			start = d;
		else
			end = d;

		if (operations++ > limit)
			throw - 1;
	} while (abs(dFunction((start + end) / 2)) > eps || abs(end - start) > eps && abs(dFunction(y)) > eps);

	return d;
}

vector<double> ParallelTangents(LinearMinimizationMethod linearMinimization, NonlinearFunction function, const double start[], double eps, size_t size, unsigned int limit, unsigned int& operations)
{
	unsigned int subOps;
	vector<double> x1(size);

	operations = 0;

	for (size_t i = 0; i < size; i++)
		x1[i] = start[i];


	auto x2 = MinimizeLine(linearMinimization, function, x1.data(), InvGradient(function, eps, x1.data(), size).data(), size, eps, subOps, subOps, 1000, 1000);
	
	while (true)
	{
		if (++operations > limit)
			throw - 1;

		auto x3 = MinimizeLine(linearMinimization, function, x2.data(), InvGradient(function, eps, x2.data(), size).data(), size, eps, subOps, subOps, 1000, 1000);
		auto d = x3;
		
		Substract(d.data(), x1.data(), size);

		auto x4 = MinimizeLine(linearMinimization, function, x2.data(), d.data(), size, eps, subOps, subOps, 1000, 1000);

		if (Length(d.data(), size) < eps)
			return x4;

		x1 = x2;
		x2 = x4;
	}
}

MinimizationMethod PrepareParallelTangents(LinearMinimizationMethod linerarMinimization)
{
	return [linerarMinimization](NonlinearFunction function, const double start[], double eps, size_t size, unsigned int limit, unsigned int& operations)
	{
		return ParallelTangents(linerarMinimization, function, start, eps, size, limit, operations);
	};
}
