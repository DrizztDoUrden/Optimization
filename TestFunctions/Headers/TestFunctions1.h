#pragma once
#include "OptimizationFunctionTypes.h"



using namespace std;



const size_t NumberOffset1 = 0;
const size_t NumberOfFunctions1 = 9;



double F1(double);
double F2(double);
double F3(double);
double F4(double);
double F5(double);
double F6(double);
double F7(double);
double F8(double);
double F9(double);

extern LinearFunction functions1[NumberOfFunctions1];

extern double starts1[NumberOfFunctions1];
extern double epsPows1[NumberOfFunctions1];
extern double epss1[NumberOfFunctions1];
extern double mins1[NumberOfFunctions1];
