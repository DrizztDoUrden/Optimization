#pragma once
#include "MinimizationMethod.h"



namespace Optimization
{
	namespace OptimizationClasses
	{
		class Partan : public MinimizationMethod
		{
		public:
			Vector FindMinimum(const Function<double>& function, Vector start, double eps, unsigned int* operations) sealed override;
		};
	}
}
