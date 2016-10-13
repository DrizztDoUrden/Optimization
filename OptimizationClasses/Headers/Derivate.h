#pragma once
#include "Function.h"



using namespace Optimization::FunctionClasses;



namespace Optimization
{
	namespace OptimizationClasses
	{
		class Derivate : public Function<double>
		{
			const Function<double>& _func;
			const size_t _coord;
			const size_t _size;
			const double _h;

		public:
			Derivate(const Function<double>& func, size_t coord, size_t size, double h);

			double Calculate(const double*) const override sealed;
		};
	}
}
