#pragma once
#include <functional>
#include <vector>
#include "OptimizationFunctionTypes.h"



using namespace std;



using LinearMinimizationMethod = function<double(LinearFunction function, double start, double end, double eps, unsigned int limit, unsigned int& operations)>;
using MinimizationMethod = function<vector<double>(NonlinearFunction function, const double start[], double eps, size_t size, unsigned int limit, unsigned int& operations)>;

void Sven(LinearFunction function, double start, double step, double& intervalStart, double& intervalEnd, unsigned int limit, unsigned int& operations);

double Fibonachi(LinearFunction function, double start, double end, double eps, unsigned int limit, unsigned int& operations);

double Dichotomia(LinearFunction function, double start, double end, double eps, unsigned int limit, unsigned int& operations);

double Pauel(LinearFunction function, double start, double end, double eps, unsigned int limit, unsigned int& operations);

double Bolcano(LinearFunction function, double start, double end, double eps, unsigned int limit, unsigned int& operations);

double Davidon(LinearFunction function, double start, double end, double eps, unsigned int limit, unsigned int& operations);

vector<double> ParallelTangents(LinearMinimizationMethod linearMinimization, NonlinearFunction function, const double x0[], double eps, size_t size, unsigned int limit, unsigned int& operations);

MinimizationMethod PrepareParallelTangents(LinearMinimizationMethod linerarMinimization);
