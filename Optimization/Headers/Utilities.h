#pragma once
#include <functional>
#include <vector>
#include "OptimizationFunctionTypes.h"
#include "Methods.h"


void ValidateResult(LinearFunction function, double result, double test, double eps);

void ValidateResult(NonlinearFunction function, const double result[], const double test[], double eps, size_t size);

double Derivate(LinearFunction function, double h, double point);

LinearFunction DerivateFunction(LinearFunction function, double h);

double PartialDerivate(NonlinearFunction function, double h, const double point[], size_t coordinate, size_t size);

function<double(const double [], size_t)> PartialDerivateFunction(NonlinearFunction function, double h, size_t size);

vector<double> Gradient(NonlinearFunction function, double eps, const double point[], size_t size);

function<vector<double>(const double [])> GradientFunction(NonlinearFunction function, double eps, size_t size);

vector<double> InvGradient(NonlinearFunction function, double eps, const double point[], size_t size);

function<vector<double>(const double[])> InvGradientFunction(NonlinearFunction function, double eps, size_t size);

vector<double> DelinearizeCoordinate(const double start[], const double direction[], size_t size, double point);

function<vector<double>(double)> DelinearizeCoordinateFunction(const double start[], const double direction[], size_t size);

LinearFunction LinearizeFunction(NonlinearFunction original, const double start[], const double direction[], size_t size);

double MinimizeLinearFunction(LinearMinimizationMethod linearMinimization, LinearFunction function, size_t size, double eps, unsigned int& svenOps, unsigned int& minOps, unsigned int svenLimit, unsigned int minLimit);

vector<double> MapCoordinates(const double start[], double** basis, size_t size, size_t newSize, const double point[]);

NonlinearFunction MapFunction(NonlinearFunction original, const double start[], double** basis, size_t size, size_t newSize);

vector<double> MinimizeLine(LinearMinimizationMethod linearMinimization, NonlinearFunction original, const double start[], const double direction[], size_t size, double eps, unsigned& svenOps, unsigned& minOps, unsigned svenLimit, unsigned minLimit);
