#pragma once
#include "Vector.h"
#include "Function.h"



using namespace Optimization::FunctionClasses;



namespace Optimization
{
	namespace OptimizationClasses
	{
		class MinimizationMethod abstract
		{
		public:
			unsigned int OperationsLimit;

			virtual ~MinimizationMethod()
			{
			}

			virtual Vector FindMinimum(const Function<double>& function, Vector start, double eps, unsigned int* operations) abstract;
		};
	}
}
