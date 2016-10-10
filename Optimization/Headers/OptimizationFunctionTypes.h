#pragma once
#include <functional>



using namespace std;



using LinearFunction = function<double(double)>;
using NonlinearFunction = function<double(const double[])>;