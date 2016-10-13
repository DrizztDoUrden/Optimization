#pragma once
#include "Function.h"
#include "Vector.h"
#include "Derivate.h"



using namespace Optimization::FunctionClasses;



namespace Optimization
{
	namespace OptimizationClasses
	{
		class Gradient : public Function<Vector>
		{
			vector<Derivate> _derivates;

		public:
			Gradient(const Function<double>& func, size_t size, double h);

			Vector Calculate(const double*) const override sealed;
		};
	}
}
