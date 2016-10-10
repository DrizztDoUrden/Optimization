#pragma once
#include "OptimizationFunctionTypes.h"



using namespace std;



const size_t NumberOffset2 = 9;
const size_t NumberOfFunctions2 = 9;
const size_t Dims2 = 2;



double F10(const double[]);
double F11(const double[]);
double F12(const double[]);
double F13(const double[]);
double F14(const double[]);
double F15(const double[]);
double F16(const double[]);
double F17(const double[]);
double F18(const double[]);

extern NonlinearFunction functions2[NumberOfFunctions2];

extern double starts2[NumberOfFunctions2][Dims2];
extern double directions2[NumberOfFunctions2][Dims2];
extern double mins2[NumberOfFunctions2][Dims2];
extern double epss2[NumberOfFunctions2];
