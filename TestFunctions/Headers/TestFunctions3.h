#pragma once
#include "OptimizationFunctionTypes.h"



using namespace std;



const size_t NumberOffset3 = 18;
const size_t NumberOfFunctions3 = 8;



double F19(const double[]);
double F20(const double[]);
double F21(const double[]);
double F22(const double[]);
double F23(const double[]);
double F24(const double[]);
double F25(const double[]);
double F26(const double[]);

extern NonlinearFunction functions3[NumberOfFunctions3];

extern size_t dims3[NumberOfFunctions3];
extern size_t startsNumbers3[NumberOfFunctions3];
extern double **starts3[NumberOfFunctions3];
extern double *mins3[NumberOfFunctions3];
extern double epss3[NumberOfFunctions3];
